/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18345
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <string.h>

#define  RESET_VECTOR   0x400
#define  FLASH_MEM_SIZE 0x2000
// SI7020_A20 registers
#define SI7020_A20_ADDRESS     0x40   // I2C slave device address
#define SI7020_A20_HUMIDITY_ADDRESS                        0xE5      //humidity measurement command 0xF5
#define SI7020_A20_TEMPERATURE_ADDRESS                     0xE3      //temperature measurement command 0xF3
// I2C max retry
#define SLAVE_I2C_GENERIC_RETRY_MAX  3
// PWM max dutycycle
#define MAX_DUTYCYCLE 319
//Version
#define VERSION_H 1
#define VERSION_L 3
//Max tempture, turn off PWM when over it 
#define MAX_TEMP 50
//EEPROM
#define EEPROM_CONFIG 1
#define EEPROM_BOARDID 3
#define EEPROM_START 0xF000
#define EEPROM_NOT_CONFIGED 0xFF 
#define EEPROM_CONFIGED 0xAA

#define UNI_TEST_MODE   1
//EMC1704 
#define EMC1704_1_ADDRESS     0x98   // slave device address
#define EMC1704_2_ADDRESS     0x30   // slave device address
#define EMC1704_TEMP1_H       0x38
#define EMC1704_TEMP1_L       0x39
#define EMC1704_TEMP2_H       0x3A
#define EMC1704_TEMP2_L       0x3B
#define EMC1704_TEMP3_H       0x3C
#define EMC1704_TEMP3_L       0x3D
//EMC2103
#define EMC2103_ADDRESS       0x5C    // slave device address
#define EMC2103_FAN_SETTING   0x40


/*
PWM_Table_Temp1 ~ PWM_Table_Temp5, and PWM1~6, details please check document
 */
volatile int8_t Default_PWM_Table[11] = {0xD8, 0xE2, 0xEC, 0xF6, 0x00, 0x64, 0x50, 0x3C, 0x28, 0x14, 0x00};
/*
Command_type & Data_Type details please check document
 */
struct Command {
        uint8_t Command_type;
        uint8_t Total_Length;
        uint8_t Data_Type;
        uint8_t Value[61];
    } cmd;
void EraseResetVector (void);
void Signal_BL_Requested (void);

const  char NVFlag __at(FLASH_MEM_SIZE - 1) = 0x55;
static unsigned char flg_reset=0;
int8_t PWM_Table_Temp1 = 0, PWM_Table_Temp2 = 0, PWM_Table_Temp3 = 0, PWM_Table_Temp4 = 0, PWM_Table_Temp5 = 0;
uint8_t PWM_1 = 0,PWM_2 = 0, PWM_3 = 0, PWM_4 = 0, PWM_5 = 0, PWM_6 = 0;
uint8_t CurrentPWM1 = 0;
uint8_t CurrentPWM2 = 0;
int32_t Read_SI7020_Temp=0, Read_EMC1704_Temp1=0, Read_EMC1704_Temp2=0, Read_EMC1704_Temp3=0, Read_EMC1704_Temp4=0, Read_EMC1704_Temp5=0, Read_EMC1704_Temp6=0;
int8_t Temp_1 = 0, Temp_2 = 0, Temp_3 = 0, Temp_4 = 0, Temp_5 = 0, Temp_6 = 0;
uint8_t Temp_1_lo = 0,  Temp_2_lo = 0,  Temp_3_lo = 0,  Temp_4_lo = 0,  Temp_5_lo = 0,  Temp_6_lo = 0;
uint8_t Fan_PWM_Value = 0;
int8_t Temp_Heater1 = 0, Temp_Heater2 = 0;

void I2C1_RBlk(
        uint16_t slaveDeviceAddress,
        uint8_t *wblk,
        uint16_t wCount,
        uint8_t *pData,
        uint16_t rCount)
{
    I2C1_MESSAGE_STATUS status;
    static  I2C1_TRANSACTION_REQUEST_BLOCK readTRB[2];

    uint8_t timeOut = 0;
    // this initial value is important
    status = I2C1_MESSAGE_PENDING;
    // build the write buffer first
    // we need to create the TRBs for a random read sequence to the EEPROM
    // Build TRB for sending address
    I2C1_MasterWriteTRBBuild(&readTRB[0],
            wblk,
            wCount,
            slaveDeviceAddress);
    // Build TRB for receiving data
    I2C1_MasterReadTRBBuild(&readTRB[1],
            pData,
            rCount,
            slaveDeviceAddress);
    while (status != I2C1_MESSAGE_FAIL) {
        // now send the transactions
        I2C1_MasterTRBInsert(2, readTRB, &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);
        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here
        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
}

void I2C1_WBlk(
        uint16_t slaveDeviceAddress,
        uint8_t *pData,
        uint16_t nCount)
{
    I2C1_MESSAGE_STATUS status;
    I2C1_TRANSACTION_REQUEST_BLOCK WriteTRB[1];
    uint8_t timeOut=0;

    // this initial value is important
    status = I2C1_MESSAGE_PENDING;
    // build the write buffer first
    // we need to create the TRBs for a random read sequence to the EEPROM
    // Build TRB for sending address
    I2C1_MasterWriteTRBBuild(WriteTRB,
            pData,
            nCount,
            slaveDeviceAddress);
    while (status != I2C1_MESSAGE_FAIL) {
        // now send the transactions
        I2C1_MasterTRBInsert(1, WriteTRB, &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C1_MESSAGE_PENDING);

        if (status == I2C1_MESSAGE_COMPLETE)
            break;
        // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C1_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;
    }
}

 void UART_Write_Buffer(uint8_t *sendBuff, uint8_t size)
 {  
     int i;  
     for(i=0;i<size;i++)	   
         EUSART_Write(sendBuff[i]); 
 }   

void Signal_BL_Requested ()
{
    NVMADRL  = (uint8_t)  (FLASH_MEM_SIZE-2) & 0x00FF;
    NVMADRH  = (uint8_t) (((FLASH_MEM_SIZE-2) & 0xFF00) >> 8);
    NVMDATL  = 0x00;
    NVMDATH  = 0x00;
    NVMCON1 = 0x14;  // WREN & FREE
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
}

void EraseResetVector ()
{    
    NVMADRL = (uint8_t)  (RESET_VECTOR & 0x00FF);
    NVMADRH = (uint8_t) ((RESET_VECTOR & 0xFF00) >> 8);
    NVMDATL = 0x00;
    NVMDATH = 0x00;
    NVMCON1 = 0x14;  // WREN & FREE
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
}

 /*
  System init, read EEPROM check has configed, if not, write default setting to EEPROM
 */
void init(void)
{
    uint8_t Read_EEPROM[32] = {0};
    uint16_t i; 
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
        for(i=0;i<(EEPROM_CONFIG+EEPROM_BOARDID+sizeof(Default_PWM_Table));i++){
        Read_EEPROM[i] = DATAEE_ReadByte(EEPROM_START+i);
    }
    
    if(Read_EEPROM[0] == EEPROM_NOT_CONFIGED){// first write
        DATAEE_WriteByte(EEPROM_START, EEPROM_CONFIGED); //Change config bytes to 0xAA
        for(i=0;i<sizeof(Default_PWM_Table);i++){
            DATAEE_WriteByte(EEPROM_START+EEPROM_CONFIG+EEPROM_BOARDID+i, Default_PWM_Table[i]);
        }
        __delay_ms(200);
        for(i=0;i<(EEPROM_CONFIG+EEPROM_BOARDID+sizeof(Default_PWM_Table));i++){//Read PWM table from EEPROM
            Read_EEPROM[i] = DATAEE_ReadByte(EEPROM_START+i);
        }
    }
    PWM_Table_Temp1 = (int8_t*)Read_EEPROM[4];
    PWM_Table_Temp2 = (int8_t*)Read_EEPROM[5];
    PWM_Table_Temp3 = (int8_t*)Read_EEPROM[6];
    PWM_Table_Temp4 = (int8_t*)Read_EEPROM[7];
    PWM_Table_Temp5 = (int8_t*)Read_EEPROM[8];
    PWM_1 = Read_EEPROM[9];
    PWM_2 = Read_EEPROM[10];
    PWM_3 = Read_EEPROM[11];
    PWM_4 = Read_EEPROM[12];
    PWM_5 = Read_EEPROM[13];
    PWM_6 = Read_EEPROM[14];
}
 /*
  Response UART Read command
 */
void UartResponse_ReadCmd(uint8_t type)
{
    uint8_t sendBuff[16] = {0};
    uint8_t i =0;
    sendBuff[0] = 0xFF;
    sendBuff[1] = 0x00;
    uint16_t ADC_result = 0;
    uint8_t reg[1];
       
   switch (type) {
        case 0x01:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp1>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp1;
#endif
            break;
        case 0x02:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp2>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp2;
#endif
            break;
        case 0x03:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = cmd.Data_Type; //PWM#1
            sendBuff[3] = CurrentPWM1;
        case 0x04:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = cmd.Data_Type; //PWM#2
            sendBuff[3] = CurrentPWM2;
            break;
        case 0x05:
            ADC_result = ADC_GetConversion(P1V8_Detect);
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //ADC
            sendBuff[3] = ADC_result>>8;
            sendBuff[4] = ADC_result;
            break;
        case 0x06:
            ADC_result = ADC_GetConversion(P5V_Detect);
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //ADC
            sendBuff[3] = ADC_result>>8;
            sendBuff[4] = ADC_result;
            break;
        case 0x07://read adc 3.3v
            ADC_result = ADC_GetConversion(P3V3_Detect);
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //ADC
            sendBuff[3] = ADC_result>>8;
            sendBuff[4] = ADC_result;
            break;
        case 0x08:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp3>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp3;
#endif
            break;
        case 0x09:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp4>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp4;
#endif
            break;
        case 0x0A://read fan pwm dutycycle
            /*
             * Read EMC 2103 Fan Control dutycycle
             */
            //Read Fan PWM dutycycle from I2C
            reg[0] = EMC2103_FAN_SETTING;
            I2C1_RBlk(EMC2103_ADDRESS, reg, 1, Fan_PWM_Value, 1);  //get int
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = cmd.Data_Type; //fan PWM dutycycle
            sendBuff[3] = Fan_PWM_Value;
            break;
        case 0x0C: //Get Version
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //VERSION
            sendBuff[3] = VERSION_H;
            sendBuff[4] = VERSION_L;
            break;
        case 0x0D://Read PWM Table
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 2 + sizeof(Default_PWM_Table); //total length
            sendBuff[2] = cmd.Data_Type; //Read PWM Table
            for(i=0;i<sizeof(Default_PWM_Table);i++){
                sendBuff[i+3] = DATAEE_ReadByte(EEPROM_START+EEPROM_CONFIG+EEPROM_BOARDID+i);
            }
            break;
        case 0x0E://Read Board ID
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x05; //total length
            sendBuff[2] = cmd.Data_Type; //Read Board ID
            sendBuff[3] = Board_ID_0_GetValue(); //Returns Board ID 0
            sendBuff[4] = Board_ID_1_GetValue(); //Returns Board ID 1
            sendBuff[5] = Board_ID_2_GetValue(); //Returns Board ID 2
            break;
        case 0x0F:
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp5>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp5;
#endif
            break;
        case 0x10:              
            sendBuff[0] = 0x02; //Read Response
            sendBuff[1] = 0x04; //total length
            sendBuff[2] = cmd.Data_Type; //TEMP
#if UNI_TEST_MODE
            sendBuff[3] = Read_SI7020_Temp>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_SI7020_Temp;
#else
            sendBuff[3] = Read_EMC1704_Temp6>>8; //cmd.Data_Type 1 or 2 & Temp1 or 2
            sendBuff[4] = Read_EMC1704_Temp6;
#endif
            break;
        default:
            break;         
        }//end of switch
    
    UART_Write_Buffer(sendBuff, sendBuff[1]+1);
}

 /*
  Response UART Write command
 */
void UartResponse_WriteCmd(uint8_t type, uint8_t value)
{
    uint8_t sendBuff[4] = {0};
    uint8_t i =0;
    uint8_t data[2];
    
    sendBuff[0] = 0x04; //Write Response
    sendBuff[1] = 0x02; //total length
    sendBuff[2] = type;    
    
    switch (type){
        case 0x03:
            CurrentPWM1 = value;
            PWM5_LoadDutyValue((CurrentPWM1*MAX_DUTYCYCLE)/100);
            sendBuff[0] = 0x04; //write response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = type; 
            sendBuff[3] = CurrentPWM1;
            break;
        case 0x04:
            CurrentPWM2 = value;
            PWM6_LoadDutyValue((CurrentPWM2*MAX_DUTYCYCLE)/100);
            sendBuff[0] = 0x04; //write response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = type; 
            sendBuff[3] = CurrentPWM2;
            break;
        case 0x0A:
            /*
             * Write EMC 2103 Fan Control dutycycle
             */
            //Write Fan PWM dutycycle from I2C
            Fan_PWM_Value = value;
            data[0] = EMC2103_FAN_SETTING; //reg
            data[1] = Fan_PWM_Value; //data
            I2C1_WBlk(EMC2103_ADDRESS, data, 2);
            
            sendBuff[0] = 0x04; //write response
            sendBuff[1] = 0x03; //total length
            sendBuff[2] = type; //Fan PWM dutycycle
            sendBuff[3] = Fan_PWM_Value;
            break;
            
        case 0x0B:
            //prepare to reset system, restart from bootloader
            sendBuff[0] = 0x04; //write response
            sendBuff[1] = 0x02; //total length
            sendBuff[2] = type; //bootloader
            UART_Write_Buffer(sendBuff, sendBuff[1]+1); //add UART Send Hear before Reset
            Signal_BL_Requested ();
            EraseResetVector ();
            __delay_ms (1000);
            flg_reset = 1;
            break;
        case 0x0D:
            DATAEE_WriteByte(EEPROM_START, EEPROM_CONFIGED); //Change config bytes to 0xAA
            for(i=0;i<sizeof(Default_PWM_Table);i++){
                DATAEE_WriteByte(EEPROM_START+EEPROM_CONFIG+EEPROM_BOARDID+i,cmd.Value[i]);
            }
            flg_reset = 1;
            break;
        default:
            sendBuff[0] = 0xFF;
            sendBuff[1] = 0;
            break;
    } //end of switch
    UART_Write_Buffer(sendBuff, sendBuff[1]+1);    
}

 /*
  Response Error message 0xFF
 */
void UartResponse_Err()
{
    uint8_t sendBuff = 0xFF;

    UART_Write_Buffer(&sendBuff, 1);
}

 /*
    Process UART
 */
void Handler_Uart( void )
{
    uint8_t rcv_Buff[64] = {0};
    uint8_t rx_len = 0;
    uint8_t i = 0;
    
   if ((eusartRxCount==0) || (eusartRxCount>64)) return;
    
    //Read UART Data from buffer
    memset(rcv_Buff,0,sizeof(rcv_Buff));
    rx_len = EUSART_Read_N((uint8_t*)rcv_Buff);   // wait for a new character
    cmd.Command_type = rcv_Buff[0];
    cmd.Total_Length = rcv_Buff[1];
    cmd.Data_Type = rcv_Buff[2];
     
    cmd.Command_type = rcv_Buff[0];
    cmd.Total_Length = rcv_Buff[1];
    cmd.Data_Type = rcv_Buff[2];
    
    if (cmd.Total_Length<2) return ;
    
    for(i=0;i<(cmd.Total_Length-2);i++){
        cmd.Value[i]=rcv_Buff[3+i];
    }
    if  ( (cmd.Command_type==0x01)&&(rx_len == 3) ) {//Read command
        UartResponse_ReadCmd(cmd.Data_Type);
    } else if(cmd.Command_type == 0x03 && rx_len <= 0x0E) { //Write command
        UartResponse_WriteCmd(cmd.Data_Type, cmd.Value[0]);
    } else {
       UartResponse_Err();
    }
}

 /*
    Process I2C
 */
void Handler_I2c( void)
{
    uint8_t Reg[1] = {0};
    uint8_t ReadBuffer[2] = {0};

#if UNI_TEST_MODE
    /*
     * SI7020_A20 use in Uni test mode
     */
    Reg[0] = SI7020_A20_TEMPERATURE_ADDRESS;
    memset(ReadBuffer,0,sizeof(ReadBuffer));   
        
    //Read temp data from I2C
    I2C1_RBlk(SI7020_A20_ADDRESS, Reg, 1,ReadBuffer, 2); 
        
    // Set Tempature if the value is not zero
    Read_SI7020_Temp = ((ReadBuffer[0] <<8) + ReadBuffer[1]);
        
    if (Read_SI7020_Temp==0) return;
        
    Read_SI7020_Temp = (((Read_SI7020_Temp*17572) >>16)-4685);
    Temp_Heater1 = Read_SI7020_Temp/100;
    Temp_Heater2 = Temp_Heater1;
    
#else //normal mode
     /*
     * Read EMC1704 Tempture
     */
    //Read temp1 data from I2C
    Reg[0] = EMC1704_TEMP1_H;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_1, 1);  //get int
    Reg[0] = EMC1704_TEMP1_L;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_1_lo, 1);  //get lsb
    Temp_1_lo = Temp_1_lo >> 6;
    if (Temp_1 < 0) Temp_1_lo = 3 - Temp_1_lo; //complement to 1 if T nagative
    Temp_1_lo = Temp_1_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_1, Temp_1_lo);
    Read_EMC1704_Temp1 = Temp_1 + Temp_1_lo*100;
    
    //Read temp2 data from I2C
    Reg[0] = EMC1704_TEMP2_H;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_2, 1);  //get int
    Reg[0] = EMC1704_TEMP2_L;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_2_lo, 1);  //get lsb
    Temp_2_lo = Temp_2_lo >> 6;
    if (Temp_2 < 0) Temp_2_lo = 3 - Temp_2_lo; //complement to 1 if T nagative
    Temp_2_lo = Temp_2_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_2, Temp_2_lo);
    Read_EMC1704_Temp2 = Temp_2 + Temp_2_lo*100;
    
    //Read temp3 data from I2C
    Reg[0] = EMC1704_TEMP3_H;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_3, 1);  //get int
    Reg[0] = EMC1704_TEMP3_L;
    I2C1_RBlk(EMC1704_1_ADDRESS, Reg, 1, (uint8_t*)Temp_3_lo, 1);  //get lsb
    Temp_3_lo = Temp_3_lo >> 6;
    if (Temp_3 < 0) Temp_3_lo = 3 - Temp_3_lo; //complement to 1 if T nagative
    Temp_3_lo = Temp_3_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_3, Temp_3_lo);
    Read_EMC1704_Temp3 = Temp_3 + Temp_3_lo*100;
    
    //Read temp4 data from I2C
    Reg[0] = EMC1704_TEMP1_H;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_4, 1);  //get int
    Reg[0] = EMC1704_TEMP1_L;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_4_lo, 1);  //get lsb
    Temp_4_lo = Temp_4_lo >> 6;
    if (Temp_4 < 0) Temp_4_lo = 3 - Temp_4_lo; //complement to 1 if T nagative
    Temp_4_lo = Temp_4_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_4, Temp_4_lo);
    Read_EMC1704_Temp4 = Temp_4 + Temp_4_lo*100;
    
    //Read temp5 data from I2C
    Reg[0] = EMC1704_TEMP2_H;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_5, 1);  //get int
    Reg[0] = EMC1704_TEMP2_L;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_5_lo, 1);  //get lsb
    Temp_5_lo = Temp_5_lo >> 6;
    if (Temp_5 < 0) Temp_5_lo = 3 - Temp_5_lo; //complement to 1 if T nagative
    Temp_5_lo = Temp_5_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_5, Temp_5_lo);
    Read_EMC1704_Temp5 = Temp_5 + Temp_5_lo*100;
    
    //Read temp6 data from I2C
    Reg[0] = EMC1704_TEMP3_H;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_6, 1);  //get int
    Reg[0] = EMC1704_TEMP3_L;
    I2C1_RBlk(EMC1704_2_ADDRESS, Reg, 1, (uint8_t*)Temp_6_lo, 1);  //get lsb
    Temp_6_lo = Temp_6_lo >> 6;
    if (Temp_6 < 0) Temp_6_lo = 3 - Temp_6_lo; //complement to 1 if T nagative
    Temp_6_lo = Temp_6_lo*25;
    //printf("The Temputure is : %d.%d C\n", Temp_6, Temp_6_lo);
    Read_EMC1704_Temp6 = Temp_6 + Temp_6_lo*100;
    
    Temp_Heater1 = Read_EMC1704_Temp1/100; 
    Temp_Heater2 = Read_EMC1704_Temp4/100;
#endif    
        
    //Set PWM
    //TODO: make a table to reduce the cpu time
    if(Temp_Heater1 < MAX_TEMP)
    {
        if(Temp_Heater1 <= PWM_Table_Temp1){
            CurrentPWM1 = PWM_1;
        }else if (PWM_Table_Temp1 < Temp_Heater1 && Temp_Heater1<= PWM_Table_Temp2){
            CurrentPWM1 = PWM_2;
        }else if (PWM_Table_Temp2 < Temp_Heater1 && Temp_Heater1<= PWM_Table_Temp3){
            CurrentPWM1 = PWM_3;
        }else if (PWM_Table_Temp3 < Temp_Heater1 && Temp_Heater1<= PWM_Table_Temp4){
            CurrentPWM1 = PWM_4;
        }else if (PWM_Table_Temp4 < Temp_Heater1 && Temp_Heater1<= PWM_Table_Temp5){
            CurrentPWM1 = PWM_5;
        }else if (PWM_Table_Temp5 < Temp_Heater1){
            CurrentPWM1 = PWM_6;
        }
    }else{
        CurrentPWM1 = 0;
    }
    PWM5_LoadDutyValue((CurrentPWM1*MAX_DUTYCYCLE)/100); //Heater1 pum dutycycle
    
    if(Temp_Heater2 < MAX_TEMP)
    {
        if(Temp_Heater2 <= PWM_Table_Temp1){
            CurrentPWM2 = PWM_1;
        }else if (PWM_Table_Temp1 < Temp_Heater2 && Temp_Heater2<= PWM_Table_Temp2){
            CurrentPWM2 = PWM_2;
        }else if (PWM_Table_Temp2 < Temp_Heater2 && Temp_Heater2<= PWM_Table_Temp3){
            CurrentPWM2 = PWM_3;
        }else if (PWM_Table_Temp3 < Temp_Heater2 && Temp_Heater2<= PWM_Table_Temp4){
            CurrentPWM2 = PWM_4;
        }else if (PWM_Table_Temp4 < Temp_Heater2 && Temp_Heater2<= PWM_Table_Temp5){
            CurrentPWM2 = PWM_5;
        }else if (PWM_Table_Temp5 < Temp_Heater2){
            CurrentPWM2 = PWM_6;
        }
    }else{
        CurrentPWM2 = 0;
    }
    PWM6_LoadDutyValue((CurrentPWM2*MAX_DUTYCYCLE)/100);
}

 /*
                         Main application
 */
void main(void)
{
    init();
    while (1)
    {
        __delay_ms(1000);

        Handler_I2c();
        Handler_Uart();

        if (flg_reset) {
            RESET();
        }
    }// end of While(1))
    
}
/**
 End of File
*/