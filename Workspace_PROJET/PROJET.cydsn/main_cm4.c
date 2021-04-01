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

#include "Communication.c"
#include "Traitement.c"
#include "Interface.c"



int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

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
