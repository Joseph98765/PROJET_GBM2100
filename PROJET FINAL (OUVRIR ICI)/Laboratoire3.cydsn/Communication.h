/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef COMMUNICATION_H_   
#define COMMUNICATION_H_
    
    #include "project.h"
    #include "FreeRTOS.h"
    #include "task.h"
    #include <stdio.h>
    #include <stdlib.h>    
    
    uint32_t buffer_Red_uint[1000];
    uint32_t buffer_IR_uint[1000];
    
//Addresse I2C du capteur MAX30102    
    
    #define MAX30102_I2C_ADDR 0x57

    //Taille du FIFO    
    
    #define FIFO_DEPTH 32
    
    //Addresses du registre du capteur MAX30102   
    
    #define REG_INTR_STATUS_1   0x00
    #define REG_INTR_STATUS_2   0x01
    #define REG_INTR_ENABLE_1   0x02
    #define REG_INTR_ENABLE_2   0x03
    #define REG_FIFO_WR_PTR     0x04
    #define REG_OVF_COUNTER     0x05
    #define REG_FIFO_RD_PTR     0x06
    #define REG_FIFO_DATA       0x07
    #define REG_FIFO_CONFIG     0x08
    #define REG_MODE_CONFIG     0x09
    #define REG_SPO2_CONFIG     0x0A
    #define REG_LED1_PA         0x0C 
    #define REG_LED2_PA         0x0D 
    #define REG_PILOT_PA        0x10
    #define REG_MULTI_LED_CTRL1 0x11
    #define REG_MULTI_LED_CTRL2 0x12
    #define REG_TEMP_INTR       0x1F
    #define REG_TEMP_FRAC       0x20
    #define REG_TEMP_CONFIG     0x21
    #define REG_PROX_INT_THRESH 0x30
    #define REG_REV_ID          0xFE
    #define REG_PART_ID         0xFF

    
    //PARAMÈTRES DES REGISTRES
    // (RM : rightmost) 
    
    //PARAMÈTRES DE REG_INTR_STATUS_1 (0x00), REG_INTR_ENABLE_1 (0x02)
    
/*    
    A_FULL (B7)
    Interruption déclenchée quand le FIFO a un certain nombre d'espaces libres.
    Interruption levée quand lue.
*/  
    #define A_FULL_RM_BIT  7
    
    #define A_FULL_YES     1
    #define A_FULL_NO      0

    
/*    
    PPG_RDY (B6)
    Interruption déclenchée quand il y a un nouveau sample dans le FIFO.
    Interruption levée quand une nouvelle valeur est lue ou REG_INTR_STATUS_1 est lue.
*/    
    #define PPG_RDY_RM_BIT 6
    
    #define PPG_RDY_YES    1
    #define PPG_RDY_NO     0
    
    
/*
    ALC_OVF (B5)    
    Interruption déclenchée quand la lumière ambiante affecte la lecture.
*/
    #define ALC_OVF_RM_BIT  5
    
    #define ALC_OVF_YES     1
    #define ALC_OVF_NO      0
    
    
    //PARAMÈTRES DE REG_INTR_STATUS_2 (0x01) et REG_INTR_ENABLE_2 (0x03)
    
/*
    DIE_TEMP_READY (B2)    
    Interruption déclenchée quand la conversion de la température est terminée.
    Interruption levée quand INT_STATUS_REGISTER_2 est lue.
*/    
    #define DIE_TEMP_READY_RM_BIT 2
    
    #define DIE_TEMP_READY_YES 1
    #define DIE_TEMP_READY_NO  0
    
    //PARAMÈTRES DE REG_FIFO_CONFIG (0x08)
    
/*    
    SMP_AVE (B7-B5)
    Nombre de samples dont la moyenne est prise 
*/  
    #define SMP_AVE_RM_BIT  5
    
    #define SMP_AVE_1       0x00
    #define SMP_AVE_2       0x01 
    #define SMP_AVE_4       0x02
    #define SMP_AVE_8       0x03
    #define SMP_AVE_16      0x04
    #define SMP_AVE_32      0x05

/*
    FIFO_ROLLOVER_EN (B4)
    Contrôle le comportement du FIFO quand celui-ci est remplis. 
    Si 0x01, le FIFO est remplis continuellement en effaçant les anciennes valeurs.
    Si 0x00, le FIFO n'est pas mis à jour tant que les données ne sont pas lues.
*/
    #define FIFO_ROLLOVER_EN_RM_BIT     4
    
    #define FIFO_ROLLOVER_EN_0          0x00
    #define FIFO_ROLLOVER_EN_1          0x01
   
/*
    FIFO_A_FULL (B4-B0)
    Nombre d'échantillons vides qui restent dans le FIFO après un interrupt. 
    Valeurs possibles de 0x0h (0) à 0xFh (15). Seuls 0 et 15 définies ici.
*/
    #define FIFO_A_FULL_RM_BIT 0  
    
    #define FIFO_A_FULL_0      0x00
    #define FIFO_A_FULL_15     0x0F
    
    
    //PARAMÈTRES DE REG_MODE_CONFIG (0x09)

/*
    SHDN (B7)
    Si 0x01, alors MAX30102 entre en mode "économie d'énergie".
    Interrupts à 0.
*/
    #define SHDN_RM_BIT 7
    
    #define SHDN_NO      0x00
    #define SHDN_YES     0x01

/*  
    RESET (B6)
    Si 0x01, alors redemarre MAX30102
*/
    #define RESET_RM_BIT 6
    
    #define RESET_NO      0x00
    #define RESET_YES     0x01

/*  
    MODE (B2-B0)
    NOTE: B5-B3 vide.
    Si 0x02, alors seule la LED rouge est allumée. (mode fréquence cardiaque)
    Si 0x03, alors les LEDs rouges et IR sont allumées. (mode SpO2)
    Si 0x07, alors les LEDs rouges et IR sont allumées. (mode multi-LED) 
    
*/      
    #define MODE_RM_BIT         0
    
    #define MODE_FREQ_CARD      0x02
    #define MODE_SPO2           0x03
    #define MODE_MULTI_LED      0x07
    
    
    //PARAMÈTRES DE REG_SPO2_CONFIG (0x0A)
    
/*  
    SPO2_ADC_RGE (B6-B5)
    NOTE: B7 vide.
    Plage de l'ADC (courant en nA)
*/
    #define SPO2_ADC_RGE_RM_BIT  5
    
    #define SPO2_ADC_RGE_2048   0x00
    #define SPO2_ADC_RGE_4096   0x01
    #define SPO2_ADC_RGE_8192   0x02
    #define SPO2_ADC_RGE_16384  0x03
       
/*    
    SPO2_SR (B4:B2)
    Taux d'échantillonnage de SPO2
*/
    #define SPO2_SR_RM_BIT  2
    
    #define SPO2_SR_50      0x00
    #define SPO2_SR_100     0x01
    #define SPO2_SR_200     0x02
    #define SPO2_SR_400     0x03
    #define SPO2_SR_800     0x04
    #define SPO2_SR_1000    0x05
    #define SPO2_SR_1600    0x06
    #define SPO2_SR_3200    0x07
    
/*
    LED_PW (B1-B0)
    Pulse width de la LED (us)
*/
    #define LED_PW_RM_BIT   0
    
    #define LED_PW_69       0x00
    #define LED_PW_118      0x01
    #define LED_PW_215      0x02
    #define LED_PW_411      0x03
    
    
    //PARAMÈTRES DE REG_LED1_PA ET REG_LED2_PA (0x0D)
/*
    Courant dans les LED de 0 à 51mA. Prends des valeurs de 8bit (0-255).
    Exemples: courant de 0mA à 0, courant de 10mA à 50, courant de 51mA à 255.
*/
    
    //PARAMÈTRES DE REG_TEMP_CONFIG (0x21)
/*
    TEMP_EN
    Active la mesure de température
*/
    #define TEMP_EN_RM_BIT 0
    
    #define TEMP_EN_YES    1
    #define TEMP_EN_NO     0
    
    //Taille du buffer contenant les données de RED et IR 
    #define BUFFER_SIZE 1000

    #define I2C_TIMEOUT 100

    #define UN_MIN 0x03FFFF
 
    

    
    
/*
    Fonctions MAX30102   
*/
 
    //Lire de MAX
    uint8_t MAX30102Read (uint8_t address);
    
    //Ecrire dans registre de MAX
    void MAX30102Write(uint8_t address, uint8_t data);
    
    //Lire plusieurs bytes de MAX
    void MAX30102ReadMultipleBytes(uint8_t baseAddress, uint8_t *buffer, uint8_t length);
    
    //Lire du FIFO de MAX
    void MAX30102ReadFIFO32bits(uint32_t *data_red, uint32_t *data_ir);     
    
    //Configurer MAX
    void MAX30102Config();
    
    //Changer amplitude de DEL de MAX
    void change_RED_LED_amp(uint8_t amp);
    
    //Tache de MAX
    void MAX30102Task(void *arg);
    
    //Lire temperature du dye de MAX (non utilise)
    void MAX30102ReadTemperature(uint8_t *buffer);
    
    //Resetter MAX (surprise surprise)
    void MAX30102Reset();
    
    //Tache de MAX
    void MAX30102Task(void *arg);    
    
    
/*
    Fonctions BMI160   
*/
    
    //Configuration de BMI
    void bmi160Init(void);

    //Ecrire dans registre de BMI
    int8_t BMI160BurstWrite(uint8_t dev_addr, uint8_t reg_addr,uint8_t *data, uint16_t len); 
    
    //Lire dans registre de BMI
    int8_t BMI160BurstRead(uint8_t dev_addr, uint8_t reg_addr,uint8_t *data, uint16_t len);
    
    //Configuration de BMI
    void bmi160Init(void);
    
    //Task de BMI
    void motionTask(void *arg);
    

    
    
    #endif
/* [] END OF FILE */
