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
#include "GUI.h"

#include "Communication.c"
#include "Traitement.c"
#include "Interface.c"



int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    bouton_semph = xSemaphoreCreateBinary();
    
    /* Initialize emWin Graphics */
    GUI_Init();

    /* Start the eInk display interface and turn on the display power */
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);

    
    GUI_SetPenSize(1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    
    Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
    
    xTaskCreate(Affichage_task, "Affichage", 500, NULL, 1, NULL);
    xTaskCreate(DesactiverAlarme_task, "BOUTON", 500, NULL, 1, NULL);
    xTaskCreate(SelectionPage_task, "SelectionPage", 500, NULL, 0, NULL);
    vTaskStartScheduler();
    
    
    //PWM : On start le PWM et son clock
    PWM_Start();
    PWM_CLOCK_Enable();
    
    //ADC : On start l'ADC, ses conversions
    ADC_Start();
    ADC_StartConvert();
    
    
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
    
    CapSense_Start();
    CapSense_ScanAllWidgets();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    traitement();
    interface();
    communication();
    for(;;)
    {
        /* Place your application code here. */
        
    }
}

/* [] END OF FILE */
