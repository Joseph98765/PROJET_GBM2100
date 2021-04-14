/*******************************************************************************
* File name : Traitement.c
*
* Function Name: void traitement(void)
* Summary: 
*
* Parameters:
*  None
*
* Return:
*  None
*
* Authors : 
* Date of Creation : 24 mars 2021
*
********************************************************************************/


#include <project.h>
#include <Traitement.h>
#include <Commun.h>
#include <arm_math.h>
#include <core_cm4.h>

#define DATA_LENGTH 2000 
#define BLOCK_SIZE  500 
#define NUM_COEFF   61

static float32_t firStateF32[BLOCK_SIZE + NUM_COEFF - 1];
const float32_t firCoeffsLPF[NUM_COEFF] = {0,-0.0005335467,-0.0009757422,-0.0011519104,-0.00086374,0,0.0013113764,0.0026138033,0.0032021277,0.0024073679,0,-0.00348266,-0.0067057676,-0.0079302322,-0.0057647886,0,0.0078763005,0.0148342877,0.0172463226,0.0123940257,0,-0.0168833441,-0.0321516098,-0.0382203158,-0.0285052982,0,0.045011896,0.0988527024,0.1501694527,0.1870319682,0.2004346487,0.1870319682,0.1501694527,0.0988527024,0.045011896,0,-0.0285052982,-0.0382203158,-0.0321516098,-0.0168833441,0,0.0123940257,0.0172463226,0.0148342877,0.0078763005,0,-0.0057647886,-0.0079302322,-0.0067057676,-0.00348266,0,0.0024073679,0.0032021277,0.0026138033,0.0013113764,0,-0.00086374,-0.0011519104,-0.0009757422,-0.0005335467,0};
const float32_t firCoeffsHPF[NUM_COEFF] = {-0.0005813984,-0.0006035935,-0.0006627953,-0.0007590446,-0.0008919221,-0.0010605484,-0.0012635909,-0.001499276,-0.0017654071,-0.0020593887,-0.0023782553,-0.0027187057,-0.0030771414,-0.0034497096,-0.0038323495,-0.0042208413,-0.0046108581,-0.0049980191,-0.0053779435,-0.0057463052,-0.006098887,-0.0064316329,-0.0067406996,-0.0070225044,-0.007273771,-0.0074915705,-0.0076733587,-0.0078170084,-0.0079208362,-0.0079836245,0.9925748825,-0.0079836245,-0.0079208362,-0.0078170084,-0.0076733587,-0.0074915705,-0.007273771,-0.0070225044,-0.0067406996,-0.0064316329,-0.006098887,-0.0057463052,-0.0053779435,-0.0049980191,-0.0046108581,-0.0042208413,-0.0038323495,-0.0034497096,-0.0030771414,-0.0027187057,-0.0023782553,-0.0020593887,-0.0017654071,-0.001499276,-0.0012635909,-0.0010605484,-0.0008919221,-0.0007590446,-0.0006627953,-0.0006035935,-0.0005813984};

uint32_t blockSize  = BLOCK_SIZE; 
uint32_t numBlocks  = DATA_LENGTH/BLOCK_SIZE; 
uint32_t dataLength = DATA_LENGTH;
uint32_t Fs = 100;


/* Fonction filtre passe-bas pour avoir la composante DC signal rouge et infrarouge */
void FilterLP(uint32_t* buffer, float* filteredSignal){
    
    uint32_t i; 
    arm_fir_instance_f32 S; 
    arm_fir_init_f32(&S, NUM_COEFF, (float32_t *)&firCoeffsLPF[0], &firStateF32[0], blockSize);   

    for(i=0; i < numBlocks; i++)  
    {    
      arm_fir_f32(&S, (float32_t *)buffer + (i * blockSize), filteredSignal + (i * blockSize), blockSize);  
    } 
}

/* Fonction filtre passe-haut pour avoir la composante AC signal rouge et infrarouge */
void FilterHP(float* buffer, float* filteredSignal){
    uint32_t i; 
    arm_fir_instance_f32 S; 
    arm_fir_init_f32(&S, NUM_COEFF, (float32_t *)&firCoeffsHPF[0], &firStateF32[0], blockSize);   

    for(i=0; i < numBlocks; i++)  
    {    
      arm_fir_f32(&S, buffer + (i * blockSize), filteredSignal + (i * blockSize), blockSize);  
    } 
}

/* Fonction pour calculer le SpO2 */
uint16_t CalculSpO2(float* signalRedDC, float* signalIRDC, float* signalRedAC, float* signalIRAC) {
    uint16_t  SpO2 = 0;
    float32_t R = 0;
    float32_t ACred = 0;
    float32_t ACinfrared = 0;
    float32_t DCred = 0;
    float32_t DCinfrared = 0;
    
    float32_t maxSignalRedAC = 0, minSignalRedAC = 0, maxSignalIRAC = 0, minSignalIRAC = 0;
    uint32_t indexMaxSignalRedAC = 0, indexMinSignalRedAC = 0, indexMaxSignalIRAC = 0, indexMinSignalIRAC = 0;
    
    arm_max_f32(signalRedAC,1000,&maxSignalRedAC,&indexMaxSignalRedAC);
    arm_min_f32(signalRedAC,1000,&minSignalRedAC,&indexMinSignalRedAC);
    arm_max_f32(signalIRAC,1000,&maxSignalIRAC,&indexMaxSignalIRAC);
    arm_min_f32(signalIRAC,1000,&minSignalIRAC,&indexMinSignalIRAC);
    
    ACred = maxSignalRedAC - minSignalRedAC;
    ACinfrared = maxSignalIRAC - minSignalIRAC;
    
    arm_mean_f32(signalRedDC,1000,&DCred);
    arm_mean_f32(signalIRDC,1000,&DCinfrared);
    
    R = (ACred/DCred)/(ACinfrared/DCinfrared);
    SpO2 = round(-45.060*R*R + 30.354*R + 97.845);
    
    return SpO2;
}

/* Fonction pour calculer le BPM */
uint16_t CalculBPM(float* signalRedAC) {
    uint16_t indexLastPeak = 0;
    uint16_t indexFirstPeak = 0;
    uint16_t nPeak = 0;
    uint16_t BPM = 0;
    
    
    for(uint16_t i=1; i < dataLength; i++){
        if(signalRedAC[i-1]<signalRedAC[i] && signalRedAC[i]<signalRedAC[i+1] && signalRedAC[i]>3000){
            nPeak++;
            if (nPeak == 1){
                indexFirstPeak = i;
            }            
            else if (nPeak >=2){
                indexLastPeak = i;                
            }
        }
    }
    BPM = round(60/((indexLastPeak-indexFirstPeak)/Fs));
    return BPM;
}


/*******************************************************************************
* Function Name: void traitement(void)
********************************************************************************
*
* Summary:  Fonction effectuant le traitement du signal et retournant le signal 
*           rouge et infrarouge filtré, le SpO2 et le BPM.
*
* Parameters:
*  
*  float* bufferRed, float* bufferIR, float* signalRedDC, float* signalIRDC, float* signalRedAC, float* signalIRAC
*
* Return:
*  None
*
*******************************************************************************/
/**/
void traitement_task(void * arg){
    (void) arg;
    BPM = 0;
    SpO2 = 0;
    flagTraitement =  false;
    
    for(;;){
        if(flagTraitement){
            FilterLP(buffer_Red, signal_Red_DC);
            FilterLP(buffer_IR, signal_IR_DC);
            FilterHP(signal_Red_DC,signal_Red_AC);
            FilterHP(signal_IR_DC,signal_IR_AC);
            
            BPM = CalculBPM(signal_Red_AC);
            SpO2 = CalculSpO2(signal_Red_DC, signal_IR_DC, signal_Red_AC, signal_IR_AC);
        }
    }
}
/* [] END OF FILE */
