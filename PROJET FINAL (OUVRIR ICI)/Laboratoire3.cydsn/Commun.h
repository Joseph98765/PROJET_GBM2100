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
float buffer_Red[1000];
float buffer_IR[1000];
float signal_Red_AC[500];
float signal_IR_AC[500];
float signal_Red_DC[500];
float signal_IR_DC[500];
bool  flagTraitement;
bool flagAffichage;
bool debut;
uint16_t indexLecture;

//Variable pour l'intensité de la DEL (entre 0 et 255 à lier au registre)
uint8_t IntensiteDELs;
double acceleration;

#endif
/* [] END OF FILE */
