/*******************************************************************************
* File name : Communication.c
*
* Function Name : void communication(void)
* Summary : 
*
* Parameters :
*  None
*
* Return :
*  None
*
* Authors : 
* Date : 24 mars 2021
*
********************************************************************************/
#include "project.h"
#include "Communication.h"

void communication(void)
{
    CyDelay(1000);
    UART_1_PutString("YOOOOOO");
}

/* [] END OF FILE */
