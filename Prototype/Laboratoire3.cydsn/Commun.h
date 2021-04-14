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
#ifndef COMMUN_H
#define COMMUN_H
#include <project.h>
    
uint16_t BPM;
uint16_t SpO2;
uint32_t buffer_Red[1000];
uint32_t buffer_IR[1000];
float signal_Red_AC[500];
float signal_IR_AC[500];
float signal_Red_DC[500];
float signal_IR_DC[500];
bool  flagTraitement;
uint16_t indexCommunication;

//Variable pour l'intensité de la DEL (entre 0 et 255 à lier au registre)
volatile int IntensiteDELs;

#endif
/* [] END OF FILE */
