/* Communication

Notes:
Baud rate de l'UART: 115200
Très "inspiré" de l'exemple 3.5 de PSoC 6 101.

Mises-à-jours: 
* Tâche de lecture de l'accéléromètre accomplie

À faire:
* À personaliser avec les fonctionnalités désirées.
* Trouver librairie de MAX
* Lire de MAX
* Connecter MAX

Problèmes:
* le main ne compile pas lol (voir ligne 116).
*/


#include "Communication.h"

struct bmi160_dev bmi160Dev;

int8_t BMI160BurstWrite(uint8_t dev_addr, uint8_t reg_addr,uint8_t *data, uint16_t len)
{  
    Cy_SCB_I2C_MasterSendStart(I2C_1_HW,dev_addr,CY_SCB_I2C_WRITE_XFER,0,&I2C_1_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,reg_addr,0,&I2C_1_context);
    for(int i = 0;i<len; i++)
    { 
        Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,data[i],0,&I2C_1_context);
    }
    
    Cy_SCB_I2C_MasterSendStop(I2C_1_HW,0,&I2C_1_context);
    
    return 0;
}

// This function supports the BMP180 library and read I2C Registers
int8_t BMI160BurstRead(uint8_t dev_addr, uint8_t reg_addr,uint8_t *data, uint16_t len)
{   
    Cy_SCB_I2C_MasterSendStart(I2C_1_HW,dev_addr,CY_SCB_I2C_WRITE_XFER,0,&I2C_1_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_1_HW,reg_addr,0,&I2C_1_context);
    Cy_SCB_I2C_MasterSendReStart(I2C_1_HW,dev_addr,CY_SCB_I2C_READ_XFER,0,&I2C_1_context);
    for(int i = 0;i<len-1; i++)
    {
        Cy_SCB_I2C_MasterReadByte(I2C_1_HW,CY_SCB_I2C_ACK,&data[i],0,&I2C_1_context);
    }
    Cy_SCB_I2C_MasterReadByte(I2C_1_HW,CY_SCB_I2C_NAK,&data[len-1],0,&I2C_1_context);
    
    Cy_SCB_I2C_MasterSendStop(I2C_1_HW,0,&I2C_1_context);

    return 0;
}

void bmi160Init(void)
{

    vTaskDelay(100);

  /* BMI160 */
    bmi160Dev.read = (bmi160_com_fptr_t)BMI160BurstRead;
    bmi160Dev.write = (bmi160_com_fptr_t)BMI160BurstWrite;
    bmi160Dev.delay_ms = (bmi160_delay_fptr_t)vTaskDelay;
    bmi160Dev.id = BMI160_I2C_ADDR;  // I2C device address

    bmi160_init(&bmi160Dev); // initialize the device
  
    bmi160Dev.gyro_cfg.odr = BMI160_GYRO_ODR_800HZ;
    bmi160Dev.gyro_cfg.range = BMI160_GYRO_RANGE_125_DPS;
    bmi160Dev.gyro_cfg.bw = BMI160_GYRO_BW_OSR4_MODE;

      /* Select the power mode of Gyroscope sensor */
    bmi160Dev.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

    bmi160Dev.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
    bmi160Dev.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
    bmi160Dev.accel_cfg.bw = BMI160_ACCEL_BW_OSR4_AVG1;
    bmi160Dev.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;

      /* Set the sensor configuration */
    bmi160_set_sens_conf(&bmi160Dev);
    bmi160Dev.delay_ms(50);
}

// 32768 = 2g
#define MAXACCEL (32768/2)

void motionTask(void *arg)
{
    (void)arg;
    I2C_1_Start();
    bmi160Init();
    struct bmi160_sensor_data acc;
    
    float gx,gy,gz;
    
    while(true)
    {
        bmi160_get_sensor_data(BMI160_ACCEL_ONLY, &acc, NULL, &bmi160Dev);
    
        gx = (float)acc.x/MAXACCEL;
        gy = (float)acc.y/MAXACCEL;
        gz = (float)acc.z/MAXACCEL;
        
        printf("x=%1.2f y=%1.2f z=%1.2f\r\n",gx,gy,gz);
        
        vTaskDelay(200);
    }
}

void communication(void) //en theorie le int main devrait etre ici
{
    __enable_irq(); /* Enable global interrupts. */

    UART_1_Start();
  
    xTaskCreate( motionTask, "Motion Task",400,0,1,0);
    vTaskStartScheduler();

    uint16_t red_LED_buffer [BUFFER_SIZE];
    uint16_t ir_LED_buffer [BUFFER_SIZE];  
    uint8_t temperatureInt[BUFFER_SIZE];
    uint8_t temperatureFrac[BUFFER_SIZE];
    
    I2C_2_Start();
   
    MAX30102Config();
    
    change_RED_LED_amp(10);
    
    for(;;)
    {
        MAX30102ReadFIFO16bits(red_LED_buffer, ir_LED_buffer);
        MAX30102ReadTemperatureInt(temperatureInt);
        MAX30102ReadTemperatureFrac(temperatureFrac);
        for (uint16_t i = 0; i < BUFFER_SIZE ; i++)
        { 
            printf("RED : %u  IR  : %u  TEMP: %u \r\n",red_LED_buffer[i],ir_LED_buffer[i],temperatureInt[i]+temperatureFrac[i]);

            }
            
        }
}

uint8_t MAX30102Read (uint8_t address){

    I2C_2_MasterSendStart(MAX30102_I2C_ADDR,CY_SCB_I2C_WRITE_XFER,I2C_TIMEOUT);
    I2C_2_MasterWriteByte(address,I2C_TIMEOUT);  
    I2C_2_MasterSendReStart(MAX30102_I2C_ADDR,CY_SCB_I2C_READ_XFER,I2C_TIMEOUT);
    
    uint8_t regValue=0;
    
    I2C_2_MasterReadByte(CY_SCB_I2C_MASTER_DATA_NAK,(uint8_t*)&regValue,I2C_TIMEOUT);
    I2C_2_MasterSendStop(I2C_TIMEOUT);  
    
    return regValue;
    
}

void MAX30102Write(uint8_t address, uint8_t data){ 
    
    I2C_2_MasterSendStart(MAX30102_I2C_ADDR,CY_SCB_I2C_WRITE_XFER,I2C_TIMEOUT);
    I2C_2_MasterWriteByte(address,I2C_TIMEOUT);        
    I2C_2_MasterWriteByte(data,I2C_TIMEOUT);         
    I2C_2_MasterSendStop(I2C_TIMEOUT);   
    
} 

void MAX30102ReadMultipleBytes(uint8_t baseAddress, uint8_t *buffer, uint8_t length)
{
    I2C_2_MasterSendStart(MAX30102_I2C_ADDR,CY_SCB_I2C_WRITE_XFER,I2C_TIMEOUT); 
    I2C_2_MasterWriteByte(baseAddress,I2C_TIMEOUT);       
    I2C_2_MasterSendReStart(MAX30102_I2C_ADDR,CY_SCB_I2C_READ_XFER,I2C_TIMEOUT);
    uint8_t idx = 0;
    for(idx=0 ; idx < length-1 ; idx++){ 
    I2C_2_MasterReadByte(CY_SCB_I2C_ACK,(uint8_t*)&buffer[idx],I2C_TIMEOUT);  
    }
    I2C_2_MasterReadByte(CY_SCB_I2C_NAK,(uint8_t*)&buffer[idx],I2C_TIMEOUT);
    I2C_2_MasterSendStop(I2C_TIMEOUT); 
}

void MAX30102ReadFIFO16bits(uint16_t *data_red, uint16_t *data_ir)
{
     
    //max30102 lit 3 bytes pour red et 3 bytes pour ir (24bit chaque)
    
    uint8_t temp_buffer[6]; //contient 3 bytes de red (0,1,2) suivis de 3 bytes de ir (3,4,5)
    //uint32_t temp;
    uint16_t temp; //on peut trash 1 byte si faible courant dans LED
    
    for (int i = 0 ; i < BUFFER_SIZE ; i++)
    {
        data_red[i] = 0; //initialisation
        data_ir[i] = 0;
        
  
        MAX30102ReadMultipleBytes(REG_FIFO_DATA, &temp_buffer, 6);
        
        temp = temp_buffer[0]; //remplissage de 8bits
        temp <<= 16; //bitshift de 16bits (supprime un byte si 16bit)
        data_red[i] += temp; //ajout de 8 nouveau bits
        temp = temp_buffer[1]; //remplissage de 8bits
        temp <<= 8; //bitshift de 8bits
        data_red[i] += temp; //ajout de 8 nouveau bits
        temp = temp_buffer[2]; //remplissage de 8bits
        data_red[i] += temp; //ajout de 8bits pour un total de 24bits sur 32
        
        temp = temp_buffer[3]; //idem
        temp <<= 16;
        data_ir[i] += temp;
        temp = temp_buffer[4];
        temp <<= 8;
        data_ir[i] += temp;
        temp = temp_buffer[5];
        data_ir[i] += temp;
        
        data_ir[i] &= UN_MIN; //Masque MSB
        data_red[i] &= UN_MIN;
    }
}


void MAX30102ReadFIFO32bits(uint32_t *data_red, uint32_t *data_ir)
{
     
    //max30102 lit 3 bytes pour red et 3 bytes pour ir (24bit chaque)
    
    uint8_t temp_buffer[6]; //contient 3 bytes de red (0,1,2) suivis de 3 bytes de ir (3,4,5)
    //uint32_t temp;
    uint32_t temp; //on peut trash 1 byte si faible courant dans LED
    
    for (int i = 0 ; i < BUFFER_SIZE ; i++)
    {
        data_red[i] = 0; //initialisation
        data_ir[i] = 0;
        
  
        MAX30102ReadMultipleBytes(REG_FIFO_DATA, &temp_buffer, 6);
        
        temp = temp_buffer[0]; //remplissage de 8bits
        temp <<= 16; //bitshift de 16bits (supprime un byte si 16bit)
        data_red[i] += temp; //ajout de 8 nouveau bits
        temp = temp_buffer[1]; //remplissage de 8bits
        temp <<= 8; //bitshift de 8bits
        data_red[i] += temp; //ajout de 8 nouveau bits
        temp = temp_buffer[2]; //remplissage de 8bits
        data_red[i] += temp; //ajout de 8bits pour un total de 24bits sur 32
        
        temp = temp_buffer[3]; //idem
        temp <<= 16;
        data_ir[i] += temp;
        temp = temp_buffer[4];
        temp <<= 8;
        data_ir[i] += temp;
        temp = temp_buffer[5];
        data_ir[i] += temp;
        
        data_ir[i] &= UN_MIN; //Masque MSB
        data_red[i] &= UN_MIN;
    }
}

void MAX30102Config()
{
    I2C_2_Start();

    MAX30102Write(REG_INTR_ENABLE_1,0xc0); // INTR setting

    MAX30102Write(REG_INTR_ENABLE_2,0x00);

    MAX30102Write(REG_FIFO_WR_PTR,0x00); 

    MAX30102Write(REG_OVF_COUNTER,0x00); 

    MAX30102Write(REG_FIFO_RD_PTR,0x00);  

    MAX30102Write(REG_FIFO_CONFIG,
    (SMP_AVE_8 << 5) | (FIFO_ROLLOVER_EN_0 << 4) | (FIFO_A_FULL_15));

    MAX30102Write(REG_MODE_CONFIG,
    (SHDN_0 << 7)|(RESET_0 << 6)|(MODE_SPO2));

    MAX30102Write(REG_SPO2_CONFIG,
    (SPO2_ADC_RGE_4096 << 5)|(SPO2_SR_3200 << 2)|(LED_PW_411));

    MAX30102Write(REG_LED1_PA,2/0.2);   

    MAX30102Write(REG_LED2_PA,2/0.2);   

    MAX30102Write(REG_PILOT_PA,25/0.2); 

    MAX30102Write(REG_TEMP_CONFIG,0x01);

}

void MAX30102Reset(){
    MAX30102Write(REG_MODE_CONFIG,0x40);
}

void change_RED_LED_amp(uint8_t amp){
    
    MAX30102Write(REG_LED1_PA, amp); 
}

void MAX30102ReadTemperatureInt(uint8_t *buffer){
    
    MAX30102ReadMultipleBytes(REG_TEMP_INTR, buffer, 8);

}

void MAX30102ReadTemperatureFrac(uint8_t *buffer){
    
    MAX30102ReadMultipleBytes(REG_TEMP_FRAC, buffer, 8);

}


/* [] END OF FILE */