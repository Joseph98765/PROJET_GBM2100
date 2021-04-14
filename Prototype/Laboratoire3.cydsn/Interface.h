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
#ifndef INTERFACE_H
#define INTERFACE_H

#include "project.h"
#include "GUI.h"
#include "eInk Library\cy_eink_library.h"
#include "eInk Library\pervasive_eink_hardware_driver.h"
#include "LCDConf.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

//Variables pour chaanger de page
volatile int NumPage;


//Variables à lier avec les données que Youssef va envoyer de SpO2 et de BPM
volatile int VraiValeurSpO2;
volatile int VraiValeurBPM;
volatile float VraiValeurACC;

//Variables que l'utilisateur change via l'interface pour set les seuils pour l'alarme
volatile int SpO2min;
volatile int BPMmax;
volatile int BPMmin;



//Sémaphore pour le bouton qui servira à arrêter les alarmes
volatile SemaphoreHandle_t bouton_semph;

//Variables booléennes pour le bouton
volatile bool estAppuye;
    
//Variables booléennes pour l'alarme
volatile bool AlarmeOnBPMmin;
volatile bool AlarmeOnBPMmax;
volatile bool AlarmeOnSpO2;
volatile bool AlarmeOnACC;

void interfaceSetup();    
void interface(void);
void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle);
void ClearScreen(void);
void isr_bouton(void);
void DesactiverAlarme_task();
void ActiverAlarme_task();
void updateParameters(int spO2, int BPM);
void CreationVecteurEspacer(int longueurVecteur, int espacement, int ValeurMin, int ValeurMax);
void drawGraph(float* vecteurNelements, int Nelements);
void CapSense_task();
void Affichage_task();

float vectorR[6625];
#endif
/* [] END OF FILE */
