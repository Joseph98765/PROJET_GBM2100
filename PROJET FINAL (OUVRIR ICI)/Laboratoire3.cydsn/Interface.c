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
#include "Commun.h"
#include "Communication.h"
#include <arm_math.h>
#include <core_cm4.h>


//Veceur obtenu avec le capteur à lier avec les valeurs que Yousef traite
//float vectorR[]={205973,207305,206168,208001,206188,208050,206371,208225,206544,208577,206719,208501,206990,208473,207183,208417,207367,208379,207724,208151,207986,207993,208303,207802,208682,207622,208730,207587,209365,207455,209209,207541,209337,207549,209635,207806,209501,207957,209461,207996,209317,208103,209140,208491,209000,208672,208748,209006,208491,209357,208350,209326,208242,209947,208089,209826,208216,210028,208306,210395,208429,210203,208596,210292,208686,210169,208954,210055,209354,209987,209644,209821,210027,209660,210440,209483,210556,209554,211304,209484,211253,209696,211585,209817,211970,210011,211842,210178,211772,209972,211207,209606,210230,208954,209085,208043,207710,207263,206266,206439,205001,205392,203820,204970,202756,203955,202073,203512,201459,203377,201194,202759,200993,202713,201002,202459,201198,202302,201513,202188,201835,202108,202327,202081,202824,201965,203003,202176,203932,202267,203918,202500,204436,202777,204921,203032,204880,203312,205157,203520,205057,203810,205034,204221,204997,204527,204912,204994,204917,205416,204837,205671,204732,206338,204657,206251,204614,206460,204591,206662,204581,206367,204586,206402,204548,205967,204548,205683,204576,205312,204550,204995,204844,204647,205035,204328,205121,204143,205709,203943,205474,203995,205910,204074,206112,204207,205943,204379,206337,204543,206193,204879,206211,205289,206165,205581,206150,206104,206141,206566,206010,206910,206113,207618,206076,207602,206252,208240,206424,208563,206665,208406,206886,208919,207081,208835,207367,208762,207638,208729,207896,208526,208348,208387,208732,208203,209019,208070,209391,207916,209311,207900,209782,207913,209978,208038,209863,208165,210137,208232,209963,208477,209827,208599,209678,208829,209472,209224,209399,209521,209079,209731,208932,210161,208772,210177,208810,210728,208819,210815,208995,210858,209138,211288,209319,211079,209575,211060,209773,210901,209995,210738,210439,210645,210706,210529,211089,210404,211618,210365,211667,210429,212263,210423,212435,210609,212498,210811,212917,210990,212716,211242,212775,211454,212706,211741,212553,212006,212075,211822,211394,211512,210369,211017,209260,210003,208265,209523,207043,208474,206230,207583,205368,207020,204742,206069,204125,205441,203797,204749,203574,204319,203623,203937,203726,203711,204060,203522,204535,203455,204648,203514,205413,203600,205487,203925,205838,204139,206355,204422,206331,204765,206340,204905,206310,205237,206250,205671,206162,205966,205968,206378,205974,206914,205810,207094,205989,207848,206030,207872,206243,208126,206361,208540,206469,208161,206571,208104,206495,207865,206553,207469,206683,207157,206675,206745,206985,206432,207161,205979,207035,205823,207540,205630,207319,205637,207490,205725,207795,205872,207640,206063,207704,206191,207660,206451,207570,206852,207480,207082,207399,207523,207226,207973,207110,208152,207223,208946,207143,208810,207353,209287,207568,209686,207753,209513,208047,209837,208178,209768,208528,209740,208807,209638,209102,209523,209624,209366,210012,209201,210201,209221,210869,209090,210717,209231,211127,209364,211505,209471,211253,209641,211502,209749,211284,210005,211154,210212,210911,210296,210704,210713,210535,211061,210301,211173,210189,211774,210039,211600,210189,212038,210190,212362,210297,212096,210407,212316,210475,212075,210711,211948,210956,211803,211212,211653,211541,211458,211950,211297,212162,211147,212676,211065,212538,211107,213028,211128,213309,211291,213136,211550,213521,211655,213358,211962,213213,212192,213126,212324,212892,212745,212641,212897,212237,212817,211647,212736,210700,211734,209874,211225,208833,210424,207895,209190,207005,208490,206174,207482,205680,206645,205094,205800,204742,205171,204714,204613,204625,204101,204717,203793,205149,203572,205005,203696,205554,203726,205828,203942,205803,204307,206380,204622,206388,205060,206559,205421,206533,205667,206535,206180,206481,206490,206292,206883,206160,207464,206115,207521,206292,208305,206402,208474,206687,208511,206872,208939,206992,208721,207152,208503,207163,208264,207233,207947,207416,207560,207525,207132,207592,206828,207877,206444,207676,206334,208139,206136,207901,206112,207857,206140,208169,206238,207931,206358,207820,206447,207713,206638,207466,206977,207303,207277,207192,207706,207081,208103,206973,208188,207054,208950,207122,209005,207357,209176,207559,209677,207752,209623,208115,209711,208280,209649,208588,209549,208922,209296,209159,209208,209510,209029,209986,208906,210092,208903,210711,208890,210682,209036,210928,209164,211335,209311,211094,211720,211030,209525,210907,209785,210764,210028,210524,210284,210345,210516,210097,210907,209864,211006,209891,211597,209748,211450,209870,211707,209890,212048,209987,211765,210127,211854,210201,211623,210469,211470,210733,211316,210888,211118,211196,210930,211603,210667,211690,210606,212342,210484,212189,210579,212483,210694,212799,210842,212573,211019,212804,211122,212648,211327,212545,211738,212381,211884,212207,212313,211997,212555,211697,212417,211130,212474,210392,211663,209582,210986,208536,210186,207596,208845,206687,208006,205810,206859,205077,205887,204565,204967,204035,204126,203888,203512,203845,202960,203738,202628,204118,202439,203935,202488,204343,202575,204707,202795,204640,203013,205052,203336,204937,203668,204977,204040,204969,204330,204876,204830,204776,205237,204682,205516,204642,206110,204556,206120,204730,206553,204767,206984,205086,206843,205306,207283,205514,207187,205758,207073,206036,206817,205965,206536,206288,206252,206480,205757,206476,205521,206800,205189,206481,205014,206753,204868,206842,204892,206576,204847,206794,204864,206512,204991,206368,205193,206259,205479,206067,205917,206011,206185,205832,206505,205736,207049,205641,207054,205744,207677,205808,207841,205975,207873,206220,208307,206433,208201,206816,208156,206957,208166,207280,207951,207650,207851,207951,207751,208318,207524,208751,207360,208732,207447,209377,207486,209448,207647,209547,207845,209949,208064,209884,208361,209769,208443,209677,208653,209502,209006,209346,209267,209108,209543,208882,209991,208717,209936,208778,210564,208710,210582,208885,210665,208980,211015,209119,210898,209304,210890,209478,210768,209613,210563,209998,210388,210286,210144,210565,210008,210988,209826,210946,209720,211636,209803,211609,209905,211789,210059,212260,210340,212156,210567,212254,210845,212192,211165,212252,211804,212405,212285,212545,212971,212673,213594,212600,213848,212870,214737,212927,214762,213232,215114,213355,215520,213428,214996,213115,214297,212290,213075,211348,211815,210476,210447,209470,209150,208748,207828,208024,206645,207233,205750,207023,204975,206291,204508,206021,204099,205998,204007,205585,204018,205645,204029,205451,204382,205460,204681,205400,205052,205435,205558,205352,206132,205385,206300,205392,207043,205377,206977,205572,207429,205698,207808,205855,207670,206112,207954,206217,207802,206579,207710,206838,207691,207156,207571,207659,207520,208121,207396,208164,207266,208831,207087,208549,207031,208881,206937,209011,206953,208672,206911};
//float vectorIR[]={99513,98160,99413,98419,99319,98729,99145,99050,98949,99419,98798,99851,98679,99846,98657,100433,98597,100453,98713,100550,98880,100921,98942,100758,99148,100637,99243,100496,99426,100316,99677,100090,99871,99833,100155,99657,100544,99416,100533,99350,101127,99266,100986,99359,101151,99370,101493,99586,101282,99597,101251,99713,101027,99896,100926,100109,100625,100345,100369,100625,100180,100986,99983,101152,99930,101751,99809,101581,99950,101877,100112,102210,100251,102006,100391,102068,100506,101956,100783,101872,101092,101692,101296,101532,101733,101311,102054,101081,101967,100723,102263,100171,101478,99530,101051,98881,100564,98080,99478,97452,98752,96709,97796,96168,97009,95842,96177,95534,95551,95512,95055,95623,94635,95492,94373,96057,94212,95856,94325,96206,94439,96594,94606,96428,94889,96724,95093,96645,95436,96622,95818,96520,96042,96387,96551,96312,96959,96200,97075,96116,97747,96027,97625,96166,98102,96258,98464,96444,98339,96751,98615,96864,98429,97113,98280,97281,98005,97386,97811,97731,97436,97948,97145,97891,96849,98402,96607,98112,96544,98337,96419,98565,96500,98246,96486,98393,96524,98100,96726,97962,96902,97688,97033,97499,97468,97311,97709,97142,97975,97062,98518,96929,98493,97060,98982,97142,99388,97406,99269,97602,99597,97792,99457,98096,99419,98376,99307,98614,99245,99053,99051,99352,98867,99665,98764,100215,98688,100144,98743,100627,98752,100923,99032,100799,99094,101111,99244,100868,99403,100797,99621,100589,99763,100377,100100,100140,100269,99873,100563,99674,101021,99524,100969,99551,101462,99564,101645,99692,101446,99770,101803,99901,101652,100125,101504,100279,101331,100457,101110,100778,100915,101007,100671,101289,100594,101818,100354,101721,100377,102270,100321,102378,100537,102362,100684,102799,100805,102585,101090,102610,101267,102405,101459,102259,101910,102105,102156,101966,102442,101795,102953,101616,102905,101644,103542,101586,103483,101618,103314,101416,103288,101016,102513,100613,101743,99933,100761,99438,99818,98908,98895,98425,97997,98168,97200,98008,96533,97569,96158,97837,95820,97544,95761,97496,95758,97826,95863,97578,96039,97544,96209,97493,96416,97421,96883,97340,97182,97235,97562,97114,98095,96945,98143,96973,98853,96974,98857,97165,98978,97281,99411,97496,99321,97713,99313,97941,99350,98204,99231,98616,99012,98810,98849,99134,98638,99428,98363,99388,98216,99901,98003,99655,97962,99784,97948,99986,97911,99593,97960,99546,97939,99346,98064,99033,98266,98767,98423,98492,98790,98286,99049,98060,99135,98070,99760,97914,99640,98075,99966,98171,100331,98381,100160,98601,100328,98727,100235,99008,100150,99380,100052,99587,99866,99999,99681,100388,99521,100534,99535,101232,99437,101096,99553,101549,99678,101880,99849,101663,99997,101840,100117,101669,100358,101584,100661,101355,100847,101152,101279,100994,101606,100701,101727,100661,102257,100528,102111,100565,102442,100591,102682,100713,102452,100867,102660,100910,102439,101096,102297,101381,102126,101522,101913,101866,101702,102110,101474,102269,101232,102835,101144,102648,101153,103101,101198,103388,101404,103117,101489,103464,101591,103194,101805,103113,102042,102864,102200,102734,102590,102568,102887,102306,103113,102215,103662,102059,103543,102114,104015,102120,104256,102225,104045,102277,104156,102136,103574,101862,102947,101460,102046,100931,101066,100578,100157,100099,99211,99599,98448,99493,97657,98822,97202,98869,96803,98729,96627,98274,96483,98387,96413,98019,96627,97867,96705,97693,96918,97569,97361,97458,97688,97321,97990,97306,98588,97221,98684,97381,99330,97427,99492,97609,99450,97792,99808,97969,99740,98258,99660,98447,99583,98721,99526,99143,99402,99453,99175,99728,99006,100126,98758,100009,98681,100577,98530,100456,98552,100286,98493,100535,98475,100160,98571,99984,98623,99718,98645,99416,98885,99089,99001,98805,99246,98542,99592,98317,99538,98247,100102,98237,100083,98335,100150,98422,100539,98591,100384,98835,100372,98999,100288,99222,100149,99602,100040,99969,99851,100286,99750,100700,99585,100777,99593,101437,99550,101359,99661,101543,99773,101933,99951,101728,100164,101782,100267,101628,100494,101441,100780,101297,100990,101068,101362,100900,101679,100687,101784,100632,102358,100470,102224,100521,102395,100604,102649,100688,102500,100863,102489,100962,102295,101082,102160,101407,101901,101577,101678,101890,101420,102240,101237,102216,101126,102821,101008,102727,101077,102969,101091,103267,101272,103033,101397,103130,101441,102903,101683,102784,101920,102619,102118,102339,102494,102205,102859,101992,102968,101852,103588,101727,103469,101826,103746,101949,104055,102012,103823,102202,103910,101995,103385,101834,102735,101494,101924,100942,100911,100592,99908,100058,98927,99451,98085,99407,97319,98581,96835,98397,96336,98289,96099,97765,95970,97675,95817,97308,95883,97104,96083,96898,96229,96722,96690,96505,96995,96415,97227,96375,97887,96235,97881,96416,98288,96575,98695,96719,98579,96918,98877,97058,98690,97328,98592,97585,98493,97766,98329,98287,98180,98638,98031,98898,97942,99417,97826,99295,97833,99660,97752,99849,97779,99505,97778,99696,97768,99346,97832,99065,97878,98796,97876,98428,98147,98135,98337,97810,98422,97551,98905,97330,98810,97389,99233,97343,99475,97522,99354,97593,99672,97803,99500,98017,99401,98232,99261,98420,99087,98840,98943,99154,98826,99453,98666,99927,98564,99893,98605,100521,98594,100637,98725,100567,98900,100922,99037,100843,99265,100692,99404,100559,99572,100475,100052,100254,100233,100026,100525,99913,101022,99722,100953,99719,101611,99621,101547,99802,101632,99809,101978,99988,101748,100122,101646,100256,101477,100426,101307,100830,101095,101023,100880,101284,100662,101711,100478,101693,100447,102310,100386,102239,100511,102305,100630,102696,100730,102484,100852,102406,100964,102277,101109,102078,101567,101919,101774,101763,102084,101563,102553,101466,102600,101431,103206,101428,103357,101734,103667,101998,104217,102308,104146,102637,104348,102868,104294,103176,104265,103577,104187,103844,104003,104185,103656,104288,102972,103701,102287,103547,101335,102685,100611,102029,99793,101538,99107,100528,98558,99929,98010,99150,97664,98519,97465,97852,97234,97437,97355,96928,97567,96608,97511,96543,98135,96398,97981,96535,98374,96664,98772,96908,98670,97112,98972,97266,98808,97619,98730,97943,98656,98140,98509,98531,98333,98885,98110,99025,98030,99637,97928,99570,98170,99997,98228,100337,98496,100202,98569,100506,98679,100266,98923,100081,98992,99803,99067,99487,99399,99147,99620,98896};

//Vecteur obtenu normalisé et espacé pour l'affichage
float VecteurEspacerIR[250];
float VecteurEspacerR[250];

/* Image buffer cache */
uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};


void interfaceSetup(){

    NumPage=1;
    
    bouton_semph=0;
    estAppuye = false;
    
    AlarmeOnBPMmin=false;
    AlarmeOnBPMmax=false;
    AlarmeOnSpO2=false;
    AlarmeOnACC=false;
    
    acceleration = 1.05;
    BPM = 150;
    SpO2 = 95;

    SpO2min=80;
    BPMmax=200;
    BPMmin=40;

    IntensiteDELs=100;

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
            AlarmeOnBPMmax=false;
            AlarmeOnBPMmin=false;
            AlarmeOnSpO2=false;
            AlarmeOnACC=false;
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
/*******************************************************************************
* Function Name: void ActiverAlarme_task()
********************************************************************************
*
* Summary: Tâche pour activer l'alarme
*
* Parameters:
*  
*
* Return:
*  None
*
*
*******************************************************************************/

void ActiverAlarme_task()
{
    for (;;)
    {
        if (BPM>BPMmax)
        {
            AlarmeOnBPMmax=true; 
        }
        if (BPM<BPMmin)
        {
            AlarmeOnBPMmin=true; 
        }
        if (SpO2<SpO2min)
        {
            AlarmeOnSpO2=true;   
        }
        if (acceleration<0.9 || acceleration>1.2)
        {
            AlarmeOnACC=true;
        }
        if (AlarmeOnACC || AlarmeOnBPMmax || AlarmeOnBPMmin || AlarmeOnSpO2)
        {
            Cy_GPIO_Write(RedLED_0_PORT, RedLED_0_NUM,0);
            vTaskDelay(pdMS_TO_TICKS(50));
            Cy_GPIO_Write(RedLED_0_PORT, RedLED_0_NUM,1);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        if (!AlarmeOnACC && !AlarmeOnBPMmax && !AlarmeOnBPMmin && !AlarmeOnSpO2)
        {
            Cy_GPIO_Write(RedLED_0_PORT, RedLED_0_NUM,1);
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
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
*   Valeur  int longueurVecteur
*           int espacement
*           int ValeurMin
*           int ValeurMax
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
        VecteurEspacerIR[j]=(signal_IR_AC[i]-ValeurMin)/(ValeurMax-ValeurMin);
        VecteurEspacerR[j]=(signal_Red_AC[i]-ValeurMin)/(ValeurMax-ValeurMin);
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
*   Valeur  float* VecteurNeléments
*           int Nelements
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
            buffer[i] = ((1-vecteurNelements[i]))*75+30;
            //buffer[i + 1] = ((vecteurNelements[i]))*100+600;
        }
        
        GUI_DrawGraph(&buffer[0],250,0,25);
        GUI_SetPenSize(1);
        GUI_SetColor(GUI_BLACK);
        GUI_DrawRect(0,0,263,175);
        GUI_DrawLine(0,24,264,24);
        GUI_DrawLine(0,148,264,148);
        
        
}
/*******************************************************************************
* Function Name: ChangerIntensiteDELs(int VariableRegistreDEL)
********************************************************************************
*
* Summary: Fonction qui va faire varier la variable du registre qui s'occuppe de l'intensité
*           entre 0 et 255. Affiche un pourcentage sur l'écran
* Parameters:
*   int VariableRegistreDEL
*          
*
* Return:
*  None
*
*
*******************************************************************************/
void CapSense_task()
{
    for (;;)
    {
        //Changer les valeurs de 0 à 255 avec le slider
        if(!CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();
            int pos;
            int oldpos=0xFFFF;
            bool Bouton0Peser;
            bool Bouton1Peser;
            pos=CapSense_GetCentroidPos(CapSense_LINEARSLIDER0_WDGT_ID); //identifie la position du milieu du doigt
            Bouton0Peser=CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID);
            Bouton1Peser=CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID);
            
            
            GUI_SetPenSize(1);
            GUI_SetColor(GUI_BLACK);
            GUI_SetBkColor(GUI_WHITE);
            GUI_SetFont(GUI_FONT_16_1);
            
            //SÉLECTION DE PAGE
            if(Bouton0Peser)//si qqun touche bouton0
            {
                if(NumPage<=6 && NumPage!=1)
                    {
                        NumPage--;
                        GUI_Clear();
                        vTaskDelay(pdMS_TO_TICKS(50));
                        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                    }
            }
            vTaskDelay(pdMS_TO_TICKS(10));
            
            if(Bouton0Peser)//si qqun touche bouton0
            {
                if(NumPage==1)
                    {
                        NumPage=6;
                        GUI_Clear();
                        vTaskDelay(pdMS_TO_TICKS(50));
                        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                    }
            }
            vTaskDelay(pdMS_TO_TICKS(10));
            
            if(Bouton1Peser)//si qqun touche bouton1
            {
                if(NumPage>=1 && NumPage!=7)
                    {
                        NumPage++;
                        GUI_Clear();
                        vTaskDelay(pdMS_TO_TICKS(50));
                        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                    }
            }
            vTaskDelay(pdMS_TO_TICKS(10));
            
            if(Bouton1Peser)//si qqun touche bouton1
            {
                if(NumPage==7)
                    {
                        NumPage=1;
                        GUI_Clear();
                        vTaskDelay(pdMS_TO_TICKS(50));
                        UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                    }
            }
            vTaskDelay(pdMS_TO_TICKS(10));

            if(pos!=0xFFFF && oldpos != pos) //si le slider se fait toucher
            {
                if(NumPage==3)
                {
                    IntensiteDELs=pos*2.55;
                    change_RED_LED_amp(IntensiteDELs);
                    oldpos=pos;
                    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                } 
            
                if(NumPage==4) //si le slider se fait toucher
                {
                    SpO2min=SpO2min+(pos-50)/10;
                    
                    oldpos=pos;
                    vTaskDelay(pdMS_TO_TICKS(10));
                    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                }
                if(NumPage==5) //si le slider se fait toucher
                {
                    BPMmin=BPMmin+(pos-50)/10;
                    
                    oldpos=pos;
                    vTaskDelay(pdMS_TO_TICKS(10));
                    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                }
                if(NumPage==6) //si le slider se fait toucher
                {
                    BPMmax=BPMmax+(pos-50)/10;
               
                    oldpos=pos;
                    vTaskDelay(pdMS_TO_TICKS(10));
                    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
                }
            }
            
                
                CapSense_UpdateAllBaselines();
                CapSense_ScanAllWidgets();
        }
        
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

/*******************************************************************************
* Function Name: Affichage_task()
********************************************************************************
*
* Summary: Tâche qui va afficher chaque page
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
        
            
            if (NumPage==1)
            {
            
               GUI_SetColor(GUI_BLACK);
               GUI_SetFont(GUI_FONT_16B_1);
               GUI_Clear();
                
               if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferTR[40] = "Graphique de l'Infrarouge";
                    char bufferP[5] = "1/6";
                    GUI_DispStringAt(bufferTR, 50, 6);
                    GUI_DispStringAt(bufferP, 234, 6);
                }
                
                if (flagAffichage){
    		        float32_t max;
                    uint32_t indexMax;
                    arm_max_f32(signal_IR_AC,500,&max, &indexMax);
                    float32_t min;
                    uint32_t indexMin;
                    arm_min_f32(signal_IR_AC,500,&min, &indexMin);
                    CreationVecteurEspacer(500, 2, min, max);
                    drawGraph(VecteurEspacerIR,250);
                    updateParameters(SpO2,BPM);
                    flagAffichage = false;
                    vTaskDelay(pdMS_TO_TICKS (50));
                }
                vTaskDelay(pdMS_TO_TICKS (50));
            }
            
            else if (NumPage==2)
            {
                
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                GUI_Clear();
                
               if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferTR[40] = "Graphique du Rouge";
                    char bufferP[5] = "2/6";
                    GUI_DispStringAt(bufferP, 234, 6);
                    GUI_DispStringAt(bufferTR, 60, 6);
                }
                if (flagAffichage){
     		        float32_t max;
                    uint32_t indexMax;
                    arm_max_f32(signal_Red_AC,500,&max, &indexMax);
                    float32_t min;
                    uint32_t indexMin;
                    arm_min_f32(signal_Red_AC,500,&min, &indexMin);
                    CreationVecteurEspacer(500, 2, min, max);
                    drawGraph(VecteurEspacerR,250);
                    updateParameters(SpO2, BPM);
                    flagAffichage = false;
                    vTaskDelay(pdMS_TO_TICKS (50));
                }
                vTaskDelay(pdMS_TO_TICKS (50));
            }
            
            else if (NumPage==3)
            {
                
                GUI_DrawRect(0,0,263,175);
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                
                if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferP[5] = "3/6";
                    GUI_DispStringAt(bufferP, 234, 6);
                }
                
                GUI_DrawRect(0,0,263,175);
                char bufferTR1[35] = "Deplacer le slider pour changer";
                char bufferTR2[25] = "l'intensite des DELs";
                char bufferTRP[5] = "%";
                GUI_DispStringAt(bufferTR1, 20, 75);
                GUI_DispStringAt(bufferTR2, 60, 91);
                GUI_DispStringAt(bufferTRP, 120, 115);
                
                uint16_t PourcentageIntensite;
                PourcentageIntensite=IntensiteDELs*100/255;
                char message[10];
                sprintf(message, "%3d\r\n", PourcentageIntensite);
                GUI_DispStringAt(message, 90, 115);
            
                vTaskDelay(pdMS_TO_TICKS(300));
                
            }
                
            else if (NumPage==4)
            {
                
                GUI_DrawRect(0,0,263,175);
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                
               if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferP[5] = "4/6";
                    GUI_DispStringAt(bufferP, 234, 6);
                }
                
                GUI_DrawRect(0,0,263,175);
                char bufferT[100] = "Changer la Valeur min du spO2:";
                char bufferS[20] = "SpO2 Min : ";
                char bufferP[5] = "%";
                GUI_DispStringAt(bufferT, 20, 75);
                GUI_DispStringAt(bufferS, 80, 101);
                GUI_DispStringAt(bufferP, 180, 101);
                
                char message[10];
                sprintf(message, "%3d\r\n", SpO2min);
                GUI_DispStringAt(message, 150,100);
                    
                vTaskDelay(pdMS_TO_TICKS(300));
                
            }
                
            else if (NumPage==5)
            {
                
                GUI_DrawRect(0,0,263,175);
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                
                if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferP[5] = "5/6";
                    GUI_DispStringAt(bufferP, 234, 6);
                }
                
                GUI_DrawRect(0,0,263,175);
                char bufferT[100] = "Changer la Valeur min du BPM:";
                char bufferB[20] = "BPM Min : ";
                GUI_DispStringAt(bufferT, 20, 75);
                GUI_DispStringAt(bufferB, 80, 101);
                
                char message[10];
                sprintf(message, "%3d\r\n", BPMmin);
                GUI_DispStringAt(message, 150,100);
               
                    
                vTaskDelay(pdMS_TO_TICKS(300));
                
            }
              
            else if (NumPage==6)
            {
                
                GUI_DrawRect(0,0,263,175);
                GUI_SetColor(GUI_BLACK);
                GUI_SetFont(GUI_FONT_16B_1);
                
                if (!AlarmeOnBPMmin && !AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop haut";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnBPMmin && !AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: BPM trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (!AlarmeOnBPMmin && AlarmeOnSpO2 && !AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ATTENTION: SpO2 trop bas";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmax && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "! SpO2 trop bas et BPM trop haut !";
                    GUI_DispStringAt(bufferTR, 15, 6);
                }
                else if (AlarmeOnSpO2 && AlarmeOnBPMmin && !AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[50] = "ATTENTION: SpO2 et BPM trop bas";
                    GUI_DispStringAt(bufferTR, 20, 6);
                }
                else if (AlarmeOnACC)
                {
                    GUI_Clear();
                    char bufferTR[40] = "ARRETE DE SHAKE LE GRO";
                    GUI_DispStringAt(bufferTR, 50, 6);
                }
                else
                {
                    GUI_Clear();
                    char bufferP[5] = "6/6";
                    GUI_DispStringAt(bufferP, 234, 6);
                }
                
                GUI_DrawRect(0,0,263,175);
                char bufferTR[100] = "Changer la Valeur max du BPM:";
                char bufferB[20] = "BPM Max : ";
                GUI_DispStringAt(bufferTR, 20, 75);
                GUI_DispStringAt(bufferB, 80, 101);
                
                char message[10];
                sprintf(message, "%3d\r\n", BPMmax);
                GUI_DispStringAt(message, 160,100);
                    
                vTaskDelay(pdMS_TO_TICKS(300));
                
                }
              
        
            vTaskDelay(pdMS_TO_TICKS(50));
    }
    
}

   


/* [] END OF FILE */