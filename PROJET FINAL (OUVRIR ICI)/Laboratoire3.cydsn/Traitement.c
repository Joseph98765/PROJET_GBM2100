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
#include "FreeRTOS.h"
#include "task.h"

#define DATA_LENGTH 500
#define BLOCK_SIZE  500 
#define NUM_COEFF1  41

static float32_t firStateF32_LP[BLOCK_SIZE + NUM_COEFF1 - 1];
const float32_t firCoeffsLPF[NUM_COEFF1] ={0,-0.0004417223,-0.0010613407,-0.0019635183,-0.0031632884,-0.0045386709,-0.0058070275,-0.0065340634,-0.0061785225,-0.0041686769,0,0.0066617486,0.0158903199,0.0274392069,0.0407258249,0.0548664232,0.0687601803,0.081212487,0.0910803485,0.0974184588,0.0996036657,0.0974184588,0.0910803485,0.081212487,0.0687601803,0.0548664232,0.0407258249,0.0274392069,0.0158903199,0.0066617486,0,-0.0041686769,-0.0061785225,-0.0065340634,-0.0058070275,-0.0045386709,-0.0031632884,-0.0019635183,-0.0010613407,-0.0004417223,0};
uint32_t blockSize  = BLOCK_SIZE; 
uint32_t numBlocks  = DATA_LENGTH/BLOCK_SIZE; 
uint32_t dataLength = DATA_LENGTH;
float Fs = 100; 


/* Fonction filtre passe-bas pour avoir la composante DC signal rouge et infrarouge */
void FilterLP(float* buffer, float* filteredSignal){
    //Utilisation du filtre de la librairie CMSIS DSP
	//Fréquence de coupure de 5 Hz et 41 coefficients utilisés
    arm_fir_instance_f32 S; 
    arm_fir_init_f32(&S, NUM_COEFF1, (float32_t *)&firCoeffsLPF[0], &firStateF32_LP[0], blockSize);   
    arm_fir_f32(&S, buffer, filteredSignal, blockSize);  
}

/* Fonction qui sert a centrer le signal pour avoir la composante AC du signal rouge et infrarouge */
void Center(float* buffer, float* filteredSignal){
    float mean = 0;
    //Boucle for pour trouver la moyenne du signal
    for(uint16_t i = 0; i<dataLength; i++){
            mean+=buffer[i];
    }
    mean = mean/dataLength;
    
	//Boucle for pour soustraire la moyenne au signal pour le centrer a 0
    for(uint16_t i = 0; i<dataLength; i++){
        filteredSignal[i] = buffer[i] - mean;
    } 
}

/* Fonction pour calculer le SpO2 prennant en paramètres les quatre signaux nécessaire au calcul*/
uint16_t CalculSpO2(float* signalRedDC, float* signalIRDC, float* signalRedAC, float* signalIRAC) {
    double R = 0;
    double ACred = 0;
    double ACinfrared = 0;
    float32_t DCred = 0;
    float32_t DCinfrared = 0;
    
    float32_t maxSignalRedAC = 0, minSignalRedAC = 0, maxSignalIRAC = 0, minSignalIRAC = 0;
    uint32_t indexMaxSignalRedAC = 0, indexMinSignalRedAC = 0, indexMaxSignalIRAC = 0, indexMinSignalIRAC = 0;
    
	// Fonctions utilisées pour trouver les min et max des signaux
    arm_max_f32(signalRedAC,dataLength,&maxSignalRedAC,&indexMaxSignalRedAC);
    arm_min_f32(signalRedAC,dataLength,&minSignalRedAC,&indexMinSignalRedAC);
    arm_max_f32(signalIRAC,dataLength,&maxSignalIRAC,&indexMaxSignalIRAC);
    arm_min_f32(signalIRAC,dataLength,&minSignalIRAC,&indexMinSignalIRAC);
    
    // Calcul des composantes du ration R
	ACred = maxSignalRedAC - minSignalRedAC;
    ACinfrared = maxSignalIRAC - minSignalIRAC;
    arm_mean_f32(signalRedDC,dataLength,&DCred);
    arm_mean_f32(signalIRDC,dataLength,&DCinfrared);
    
	// Calcul de R et SpO2
    R = (ACred/DCred)/(ACinfrared/DCinfrared);
    SpO2 = round(-22*R*R + 15*R + 98);

	if(SpO2>100){
		SpO2 = 100;
	}
    
    return SpO2;
}

/* Fonction pour le calcul du BPM prennant en paramètre le signal rouge AC */
uint16_t CalculBPM(float* signalRedAC) {
    volatile float indexLastZero = 0;
    volatile float indexFirstZero = 0;
    volatile uint16_t nZeros = 0;
    float difference = 0;
    bool isZero = false;
    
	// Boucle for pour trouver le passage du signal a une certaine valeur pour tous les points
	// Initialement la valeur cherchée était zéro, ce qui explique le nom des variables
    for(uint16_t i=0; i < dataLength-1; i++){         
        if(signalRedAC[i] > 6 && signalRedAC[i+1] < 6) {
            // Boucle pour s'assurer d'une différence significative entre le point d'intéret et les points suivants
			for(uint16_t j = 0; j<20; j++){
                difference = signalRedAC[i] - signalRedAC[i+j]; 
                if(difference > 12){
                    isZero = true;
                }
            }
			// Enregistrement du premier et dernier point d'intérêt du signal
            if(isZero == true){
                nZeros++;
                if (nZeros == 1){
                    indexFirstZero = i;
                }else if (nZeros >=1){                
                    indexLastZero = i;
                }
                isZero = false;
            }
        }
    }
    // Calcul du BPM        
    BPM = round(60*(nZeros-1)/((indexLastZero-indexFirstZero)/Fs));
    return BPM;
}


/*Fonction effectuant le traitement du signal et retournant le signal rouge et
infrarouge filtré, le SpO2 et le BPM.*/
void traitement_task(){
    
       
    for(;;){
        if(flagTraitement){
			//Filtrage du signal DC pour éliminer le bruit
            FilterLP(&buffer_Red[indexLecture], signal_Red_DC);
            FilterLP(&buffer_IR[indexLecture], signal_IR_DC);
            
			//Centrage du signal pour obtenir le signal AC
            Center(buffer_IR, signal_IR_AC);
            Center(buffer_Red, signal_Red_AC);
            
			//Filtrage du signal AC pour éliminer le bruit
            FilterLP(signal_IR_AC, signal_IR_AC);
            FilterLP(signal_Red_AC, signal_Red_AC);
            
			//Calcul du BPM et SpO2
            BPM = CalculBPM(signal_Red_AC);
            SpO2 = CalculSpO2(signal_Red_DC, signal_IR_DC, signal_Red_AC, signal_IR_AC);
            
			//Modification des flags pour arrêter le traitement et commencer l'affichage
            flagAffichage = true;
            flagTraitement = false;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
/* [] END OF FILE */
