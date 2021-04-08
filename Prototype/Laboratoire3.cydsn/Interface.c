/*******************************************************************************
* File name : Interface.c
*
* Function Name: void interface(void)
* Summary: 
*
* Parameters:
*  None
*
* Return:
*  None
*
* Authors : 
* Date : 24 mars 2021
*
********************************************************************************/
#include "Interface.h"


//Veceur obtenu avec le capteur
float vectorR[]={205973,207305,206168,208001,206188,208050,206371,208225,206544,208577,206719,208501,206990,208473,207183,208417,207367,208379,207724,208151,207986,207993,208303,207802,208682,207622,208730,207587,209365,207455,209209,207541,209337,207549,209635,207806,209501,207957,209461,207996,209317,208103,209140,208491,209000,208672,208748,209006,208491,209357,208350,209326,208242,209947,208089,209826,208216,210028,208306,210395,208429,210203,208596,210292,208686,210169,208954,210055,209354,209987,209644,209821,210027,209660,210440,209483,210556,209554,211304,209484,211253,209696,211585,209817,211970,210011,211842,210178,211772,209972,211207,209606,210230,208954,209085,208043,207710,207263,206266,206439,205001,205392,203820,204970,202756,203955,202073,203512,201459,203377,201194,202759,200993,202713,201002,202459,201198,202302,201513,202188,201835,202108,202327,202081,202824,201965,203003,202176,203932,202267,203918,202500,204436,202777,204921,203032,204880,203312,205157,203520,205057,203810,205034,204221,204997,204527,204912,204994,204917,205416,204837,205671,204732,206338,204657,206251,204614,206460,204591,206662,204581,206367,204586,206402,204548,205967,204548,205683,204576,205312,204550,204995,204844,204647,205035,204328,205121,204143,205709,203943,205474,203995,205910,204074,206112,204207,205943,204379,206337,204543,206193,204879,206211,205289,206165,205581,206150,206104,206141,206566,206010,206910,206113,207618,206076,207602,206252,208240,206424,208563,206665,208406,206886,208919,207081,208835,207367,208762,207638,208729,207896,208526,208348,208387,208732,208203,209019,208070,209391,207916,209311,207900,209782,207913,209978,208038,209863,208165,210137,208232,209963,208477,209827,208599,209678,208829,209472,209224,209399,209521,209079,209731,208932,210161,208772,210177,208810,210728,208819,210815,208995,210858,209138,211288,209319,211079,209575,211060,209773,210901,209995,210738,210439,210645,210706,210529,211089,210404,211618,210365,211667,210429,212263,210423,212435,210609,212498,210811,212917,210990,212716,211242,212775,211454,212706,211741,212553,212006,212075,211822};
float vectorIR[]={0.099833,0.29552,0.47943,0.64422,0.78333,0.89121,0.96356,0.99749,0.99166,0.9463,0.86321,0.74571,0.59847,0.42738,0.23925,0.041581,-0.15775,-0.35078,-0.52984,-0.68777,-0.81828,-0.91617,-0.97753,-0.99992,-0.98245,-0.92581,-0.83227,-0.70554,-0.55069,-0.37388,-0.18216,0.016814,0.21512,0.40485,0.57844,0.72897,0.85044,0.938,0.98817,0.99894,0.96989,0.90217,0.79849,0.66297,0.50102,0.3191,0.12445,-0.075151,-0.27176,-0.45754,-0.62507,-0.76769,-0.8797,-0.95664,-0.99544,-0.99455,-0.95402,-0.87545,-0.76198,-0.61814,-0.44965,-0.26323,-0.066322,0.13323,0.32747,0.50866,0.66957,0.80378,0.90595,0.97201,0.99931,0.98677,0.9349,0.84575,0.72288,0.5712,0.39674,0.20647,0.0079632,-0.19086,-0.38207,-0.55805,-0.71179,-0.83714,-0.92912,-0.98407,-0.99977,-0.97563,-0.91258,-0.81316,-0.68131,-0.52231,-0.34248,-0.149,0.050423,0.24783,0.43537,0.60554,0.75157,0.86764,0.94912,0.99277,0.99683,0.96115,0.88716,0.77779,0.63742,0.47164,0.28705,0.091022,-0.10864,-0.30396,-0.48717,-0.65096,-0.7888,-0.89519,-0.96589,-0.99808,-0.99049,-0.9434,-0.85871,-0.73978,-0.59136,-0.41936,-0.23065};

//Veceteur obtenu normalisé et espacé pour l'affichage
float VecteurEspacerIR[250];
float VecteurEspacerR[250];

/* Image buffer cache */
uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};


void interfaceSetup(){

    NumPage=1;
    OldNumPage=1;
    estAppuye = false;
    AlarmeOff=true;

}   
/*******************************************************************************
* Function Name: void UpdateDisplay(void)
********************************************************************************
*
* Summary: This function updates the display with the data in the display 
*			buffer.  The function first transfers the content of the EmWin
*			display buffer to the primary EInk display buffer.  Then it calls
*			the Cy_EINK_ShowFrame function to update the display, and then
*			it copies the EmWin display buffer to the Eink display cache buffer
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  It takes about a second to refresh the display.  This is a blocking function
*  and only returns after the display refresh
*
*******************************************************************************/
void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle)
{
    cy_eink_frame_t* pEmwinBuffer;

    /* Get the pointer to Emwin's display buffer */
    pEmwinBuffer = (cy_eink_frame_t*)LCD_GetDisplayBuffer();

    /* Update the EInk display */
    Cy_EINK_ShowFrame(imageBufferCache, pEmwinBuffer, updateMethod, powerCycle);

    /* Copy the EmWin display buffer to the imageBuffer cache*/
    memcpy(imageBufferCache, pEmwinBuffer, CY_EINK_FRAME_SIZE);
}
/*******************************************************************************
* Function Name: void ClearScreen(void)
********************************************************************************
*
* Summary: This function clears the screen
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ClearScreen(void)
{
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

/*******************************************************************************
* Function Name: isr_bouton(void) et void DesactiverAlarme_task()
********************************************************************************
*
* Summary: Fonction et tâche pour désactiver l'alarme
*
* Parameters:
*  
*
* Return:
*  None
*
*
*******************************************************************************/

void isr_bouton(void)
{
    xSemaphoreGiveFromISR(bouton_semph, NULL);
    Cy_GPIO_ClearInterrupt(BOUTON_0_PORT, BOUTON_0_NUM);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
}
void DesactiverAlarme_task()
{
    for (;;)
    {
        if (xSemaphoreTake(bouton_semph,500))
        {
            NumPage++;
            AlarmeOff=true;
        }
    }
}
/*******************************************************************************
* Function Name: updateParameters(int spO2, int BPM)
********************************************************************************
*
* Summary: Fonction qui affiche les spO2 et le BPM en bas de l'écran
*
* Parameters:
*   Valeur int du spO2
*   Valeur int du BPM
*
* Return:
*  None
*
*
*******************************************************************************/
void updateParameters(int spO2, int BPM)
{
    char buffer1[10] = {0}, buffer2[10] = {0}, bufferD[30] = "SpO2 : ", bufferM[30] = "BPM: ";
    sprintf(buffer1, "%d", spO2);
    sprintf(buffer2, "%d", BPM);
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(GUI_FONT_16B_1);
    strcat(strcat(bufferD,buffer1), "%");
    GUI_DispStringAt(bufferD, 5, 155);
    strcat(bufferM,buffer2);
    GUI_DispStringAt(bufferM, 200, 155);
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}
/*******************************************************************************
* Function Name: CreationVecteurEspacer(int longueurVecteur, int espacement, int ValeurMin, int ValeurMax)
********************************************************************************
*
* Summary: Fonction qui crée le vecteur espacé à afficher.
*
* Parameters:
*   Valeur int int longueurVecteur
*           int espacement
*           int ValeurMin
*           int ValeurMax
*  NOTE: La ValeurMin, ValeurMax, ne devrait pas être en paramètre, et il faudrait mettre une valeur fixe dans la formule
*
* Return:
*  None
*
*
*******************************************************************************/
void CreationVecteurEspacer(int longueurVecteur, int espacement, int ValeurMin, int ValeurMax)
{
    int j=0;
    for (int i=0; i<longueurVecteur; i+=espacement)
    {
        VecteurEspacerIR[j]=(vectorIR[i]-ValeurMin)/ValeurMax;
        VecteurEspacerR[j]=(vectorR[i]-ValeurMin)/ValeurMax;
        j++;
    }
}
/*******************************************************************************
* Function Name: drawGraph(float* vecteurNelements, int Nelements)
********************************************************************************
*
* Summary: Dessine le graphique d'un vecteur normalisé à Néléments
*
* Parameters:
*   Valeur int VecteurNeléments
*           int Nelements
*           int ValeurMin
*          
*
* Return:
*  None
*
*
*******************************************************************************/
void drawGraph(float* vecteurNelements, int Nelements)
{
        
        short buffer[250] = {0};
        for (int i = 0; i < Nelements; i++)
        {
            buffer[2*i] = ((vecteurNelements[i])+1)*60;
            buffer[2*i + 1] = ((vecteurNelements[i])+1)*60;
        }
        GUI_DrawGraph(&buffer[0],250,0,25);
        GUI_SetPenSize(1);
        GUI_SetColor(GUI_BLACK);
        GUI_DrawRect(0,0,263,175);
        GUI_DrawLine(0,24,264,24);
        GUI_DrawLine(0,148,264,148);
        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
        
}
/*******************************************************************************
* Function Name: SelectionPage_task()
********************************************************************************
*
* Summary: Tâche qui va changer de page
*
* Parameters:
*  
*          
*
* Return:
*  None
*
*
*******************************************************************************/
/*
void SelectionPage_task()
{
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(50));
        if(!CapSense_IsBusy())
          {      
            CapSense_ProcessAllWidgets();
            if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID))//si qqun touche bouton0
                {
                    NumPage--;
                }
            if(CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID))//si qqun touche bouton1
                {
                    NumPage++;
                    
                }
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        }
    }
}
*/
/*******************************************************************************
* Function Name: Affichage_task()
********************************************************************************
*
* Summary: Tâche qui va afficher qqch de différent dépendament de la page
*
* Parameters:
*  
*          
*
* Return:
*  None
*
*
*******************************************************************************/
void Affichage_task()
{
    for (;;)
    {
        if(OldNumPage!=NumPage)
        {
            if (NumPage==1)
            {
            
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                char bufferTR[40] = "Graphique de l'Infrarouge";
                GUI_DispStringAt(bufferTR, 60, 6);
            
                vTaskDelay(pdMS_TO_TICKS(3000));
                //CreationVecteurEspacerIR(250, 4, int ValeurMin, int ValeurMax)
                //drawGraph(VecteurEspacerIR,250)
                drawGraph(vectorIR,125);
                updateParameters(20,150);
                
                OldNumPage=NumPage;
            
            }
            if (NumPage==2)
            {
                //vTaskDelay(pdMS_TO_TICKS(300));
                //ClearScreen();
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                char bufferTR[40] = "Graphique du Rouge       ";
                GUI_DispStringAt(bufferTR, 60, 6);
            
                vTaskDelay(pdMS_TO_TICKS(3000));
                //CreationVecteurEspacerIR(250, 4, int ValeurMin, int ValeurMax)
                //drawGraph(VecteurEspacerIR,250)
                drawGraph(vectorIR,125);
                updateParameters(30,90);
                
                OldNumPage=NumPage;
            
            }
        }
    }
}

   


/* [] END OF FILE */
