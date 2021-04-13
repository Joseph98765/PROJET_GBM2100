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
#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include <project.h>
    
void traitement(float* bufferRed, float* bufferIR, float* bufferRedDC, float* bufferIRDC, float* bufferRedAC, float* bufferIRAC);
uint16_t BPM;
uint16_t SpO2;
float buffer_Red[2000];
float buffer_IR[2000];
float signal_Red_AC[1000];
float signal_IR_AC[1000];
float signal_Red_DC[1000];
float signal_IR_DC[1000];
bool  flagTraitement;


/*volatile float buffer_Red[2000]   = {0};
volatile float buffer_IR[2000]    = {0};
volatile float signal_RedAC[1000] = {0};
volatile float signal_IR_AC[1000]  = {0};
volatile float signal_Red_DC[1000] = {0};
volatile float signal_IR_DC[1000]  = {0};
volatile bool  flagTraitement =  false;*/

#endif
/* [] END OF FILE */
