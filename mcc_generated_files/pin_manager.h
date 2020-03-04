/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18345
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set WATCHDOG aliases
#define WATCHDOG_TRIS                 TRISAbits.TRISA0
#define WATCHDOG_LAT                  LATAbits.LATA0
#define WATCHDOG_PORT                 PORTAbits.RA0
#define WATCHDOG_WPU                  WPUAbits.WPUA0
#define WATCHDOG_OD                   ODCONAbits.ODCA0
#define WATCHDOG_ANS                  ANSELAbits.ANSA0
#define WATCHDOG_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define WATCHDOG_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define WATCHDOG_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define WATCHDOG_GetValue()           PORTAbits.RA0
#define WATCHDOG_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define WATCHDOG_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define WATCHDOG_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define WATCHDOG_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define WATCHDOG_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define WATCHDOG_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define WATCHDOG_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define WATCHDOG_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set PRESENT aliases
#define PRESENT_TRIS                 TRISAbits.TRISA1
#define PRESENT_LAT                  LATAbits.LATA1
#define PRESENT_PORT                 PORTAbits.RA1
#define PRESENT_WPU                  WPUAbits.WPUA1
#define PRESENT_OD                   ODCONAbits.ODCA1
#define PRESENT_ANS                  ANSELAbits.ANSA1
#define PRESENT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PRESENT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PRESENT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PRESENT_GetValue()           PORTAbits.RA1
#define PRESENT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PRESENT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PRESENT_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define PRESENT_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define PRESENT_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define PRESENT_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define PRESENT_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define PRESENT_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set Board_ID_0 aliases
#define Board_ID_0_TRIS                 TRISAbits.TRISA2
#define Board_ID_0_LAT                  LATAbits.LATA2
#define Board_ID_0_PORT                 PORTAbits.RA2
#define Board_ID_0_WPU                  WPUAbits.WPUA2
#define Board_ID_0_OD                   ODCONAbits.ODCA2
#define Board_ID_0_ANS                  ANSELAbits.ANSA2
#define Board_ID_0_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Board_ID_0_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Board_ID_0_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Board_ID_0_GetValue()           PORTAbits.RA2
#define Board_ID_0_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Board_ID_0_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Board_ID_0_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Board_ID_0_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Board_ID_0_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define Board_ID_0_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define Board_ID_0_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Board_ID_0_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()              PORTAbits.RA5
#define RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()             do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()           do { WPUAbits.WPUA5 = 0; } while(0)
#define RA5_SetAnalogMode()         do { ANSELAbits.ANSA5 = 1; } while(0)
#define RA5_SetDigitalMode()        do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set POWERBTN aliases
#define POWERBTN_TRIS                 TRISBbits.TRISB4
#define POWERBTN_LAT                  LATBbits.LATB4
#define POWERBTN_PORT                 PORTBbits.RB4
#define POWERBTN_WPU                  WPUBbits.WPUB4
#define POWERBTN_OD                   ODCONBbits.ODCB4
#define POWERBTN_ANS                  ANSELBbits.ANSB4
#define POWERBTN_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define POWERBTN_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define POWERBTN_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define POWERBTN_GetValue()           PORTBbits.RB4
#define POWERBTN_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define POWERBTN_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define POWERBTN_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define POWERBTN_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define POWERBTN_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define POWERBTN_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define POWERBTN_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define POWERBTN_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RESETBTN aliases
#define RESETBTN_TRIS                 TRISBbits.TRISB5
#define RESETBTN_LAT                  LATBbits.LATB5
#define RESETBTN_PORT                 PORTBbits.RB5
#define RESETBTN_WPU                  WPUBbits.WPUB5
#define RESETBTN_OD                   ODCONBbits.ODCB5
#define RESETBTN_ANS                  ANSELBbits.ANSB5
#define RESETBTN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RESETBTN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RESETBTN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RESETBTN_GetValue()           PORTBbits.RB5
#define RESETBTN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RESETBTN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RESETBTN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define RESETBTN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define RESETBTN_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define RESETBTN_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define RESETBTN_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define RESETBTN_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set Board_ID_1 aliases
#define Board_ID_1_TRIS                 TRISCbits.TRISC0
#define Board_ID_1_LAT                  LATCbits.LATC0
#define Board_ID_1_PORT                 PORTCbits.RC0
#define Board_ID_1_WPU                  WPUCbits.WPUC0
#define Board_ID_1_OD                   ODCONCbits.ODCC0
#define Board_ID_1_ANS                  ANSELCbits.ANSC0
#define Board_ID_1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Board_ID_1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Board_ID_1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Board_ID_1_GetValue()           PORTCbits.RC0
#define Board_ID_1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Board_ID_1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Board_ID_1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Board_ID_1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Board_ID_1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define Board_ID_1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define Board_ID_1_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define Board_ID_1_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Board_ID_2 aliases
#define Board_ID_2_TRIS                 TRISCbits.TRISC1
#define Board_ID_2_LAT                  LATCbits.LATC1
#define Board_ID_2_PORT                 PORTCbits.RC1
#define Board_ID_2_WPU                  WPUCbits.WPUC1
#define Board_ID_2_OD                   ODCONCbits.ODCC1
#define Board_ID_2_ANS                  ANSELCbits.ANSC1
#define Board_ID_2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Board_ID_2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Board_ID_2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Board_ID_2_GetValue()           PORTCbits.RC1
#define Board_ID_2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Board_ID_2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Board_ID_2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Board_ID_2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Board_ID_2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Board_ID_2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Board_ID_2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Board_ID_2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set P1V8_Detect aliases
#define P1V8_Detect_TRIS                 TRISCbits.TRISC2
#define P1V8_Detect_LAT                  LATCbits.LATC2
#define P1V8_Detect_PORT                 PORTCbits.RC2
#define P1V8_Detect_WPU                  WPUCbits.WPUC2
#define P1V8_Detect_OD                   ODCONCbits.ODCC2
#define P1V8_Detect_ANS                  ANSELCbits.ANSC2
#define P1V8_Detect_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define P1V8_Detect_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define P1V8_Detect_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define P1V8_Detect_GetValue()           PORTCbits.RC2
#define P1V8_Detect_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define P1V8_Detect_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define P1V8_Detect_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define P1V8_Detect_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define P1V8_Detect_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define P1V8_Detect_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define P1V8_Detect_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define P1V8_Detect_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set P5V_Detect aliases
#define P5V_Detect_TRIS                 TRISCbits.TRISC3
#define P5V_Detect_LAT                  LATCbits.LATC3
#define P5V_Detect_PORT                 PORTCbits.RC3
#define P5V_Detect_WPU                  WPUCbits.WPUC3
#define P5V_Detect_OD                   ODCONCbits.ODCC3
#define P5V_Detect_ANS                  ANSELCbits.ANSC3
#define P5V_Detect_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define P5V_Detect_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define P5V_Detect_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define P5V_Detect_GetValue()           PORTCbits.RC3
#define P5V_Detect_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define P5V_Detect_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define P5V_Detect_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define P5V_Detect_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define P5V_Detect_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define P5V_Detect_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define P5V_Detect_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define P5V_Detect_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set P3V3_STBY_EN aliases
#define P3V3_STBY_EN_TRIS                 TRISCbits.TRISC4
#define P3V3_STBY_EN_LAT                  LATCbits.LATC4
#define P3V3_STBY_EN_PORT                 PORTCbits.RC4
#define P3V3_STBY_EN_WPU                  WPUCbits.WPUC4
#define P3V3_STBY_EN_OD                   ODCONCbits.ODCC4
#define P3V3_STBY_EN_ANS                  ANSELCbits.ANSC4
#define P3V3_STBY_EN_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define P3V3_STBY_EN_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define P3V3_STBY_EN_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define P3V3_STBY_EN_GetValue()           PORTCbits.RC4
#define P3V3_STBY_EN_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define P3V3_STBY_EN_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define P3V3_STBY_EN_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define P3V3_STBY_EN_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define P3V3_STBY_EN_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define P3V3_STBY_EN_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define P3V3_STBY_EN_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define P3V3_STBY_EN_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set P3V3_Detect aliases
#define P3V3_Detect_TRIS                 TRISCbits.TRISC5
#define P3V3_Detect_LAT                  LATCbits.LATC5
#define P3V3_Detect_PORT                 PORTCbits.RC5
#define P3V3_Detect_WPU                  WPUCbits.WPUC5
#define P3V3_Detect_OD                   ODCONCbits.ODCC5
#define P3V3_Detect_ANS                  ANSELCbits.ANSC5
#define P3V3_Detect_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define P3V3_Detect_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define P3V3_Detect_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define P3V3_Detect_GetValue()           PORTCbits.RC5
#define P3V3_Detect_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define P3V3_Detect_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define P3V3_Detect_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define P3V3_Detect_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define P3V3_Detect_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define P3V3_Detect_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define P3V3_Detect_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define P3V3_Detect_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/