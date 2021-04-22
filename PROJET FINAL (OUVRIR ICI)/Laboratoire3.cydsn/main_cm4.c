/*******************************************************************************
* File name : main_cm4.c
*
* Description : 
*
* Authors : 
* Date of creation : 24 mars 2021
*
********************************************************************************/

#include "project.h"

#include "Traitement.h"
#include "Interface.h"
#include "Communication.h"
#include "Commun.h"
#include <arm_math.h>
#include <core_cm4.h>



int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    //Initialize CapSense
    CapSense_Start();
    CapSense_ScanAllWidgets();
    
    //Initialize I2C
    UART_1_Start();
    I2C_1_Start();
    I2C_2_Start();
    
    //Initialize MAX30102
    MAX30102Reset();
    MAX30102Read(REG_INTR_STATUS_1);  //reset interrupt
    MAX30102Config();
    
    //Interface Setup
    interfaceSetup();
    
    //Creation du semaphore Bouton
    bouton_semph = xSemaphoreCreateBinary();
    
    // Initialize emWin Graphics 
    GUI_Init();
    
    // Start the eInk display interface and turn on the display power 
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);

    //Setup GUI
    GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    //PWM : On start le PWM et son clock
    PWM_Start();
    PWM_CLOCK_Enable();
    
    //Initialize Bouton ISR
    Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
    
    //Initialize system clock
    SystemInit();
    SystemCoreClockUpdate(); 
    
    //Taches MAX30102
    xTaskCreate(MAX30102Task, "MAX Task", 500,NULL,1,NULL);
    
    //Taches Traitement
    xTaskCreate(traitement_task, "Traitement", 500, NULL, 2, NULL);
    
    //Tache accelerometre
    xTaskCreate(motionTask, "Motion Task", 200,NULL,2,NULL);   
    
    //Taches Interface
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
    xTaskCreate(DesactiverAlarme_task, "BOUTON", 50, NULL, 3, NULL);
    xTaskCreate(ActiverAlarme_task, "Alarme", 50, NULL, 3, NULL);
    xTaskCreate(Affichage_task, "Affichage", 300, NULL, 5, NULL);
    xTaskCreate(CapSense_task, "CapSense", 100, NULL, 4, NULL);

    vTaskStartScheduler();
}

/* [] END OF FILE */
