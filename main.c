// ##########################################################################
// ##########################################################################
// MicroBot IR sensor balance test
//
// copyright 2013, Steelpuppet / Duane Benson
// Started 4/18/2012
//
// Controls one motor H-Bridge
//
// Communicates via by I2C
// PIC18F25K50 MCU
//
//
// Edit history:
//
// ********************************************

// ####
// #### Project specific notes
// ####

// ####
/*
 * File:   main.c
 * Author: Duane
 *
 * Created on February 21, 2013, 12:06 PM
 */
// #### #### #### #### #### #### #### #### #### #### #### #### #### ####
// #### Defines
// #### #### #### #### #### #### #### #### #### #### #### #### #### ####

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include "globals.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "configuration_bits.c"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


void main(void)
{
    int x;
    char PULSEdata, TRANSdata;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    // Test patterns
    if (!PORTBbits.RB4 && !PORTBbits.RB5) { // Bothe Usr1 and Usr2 held at start up: All LEDs on
        LED0 = 1;
        LED1 = 1;
        LED2 = 1;
        LATA = 0xff;
        LATC = 0xff;
        delayLong(10);
        while (PORTBbits.RB5);
    } else if (!PORTBbits.RB4) {    // Usr1 held at start: all blue LEDs on
        LED1 = 1;
        LATA = 0xAA;
        LATC = 0x55;
        delayLong(10);
        while (PORTBbits.RB5);
    } else if (!PORTBbits.RB5) {    // Usr2 held at start: all red LEDs on
        LED0 = 1;
        LED2 = 1;
        LATA = 0x55;
        LATC = 0xAA;
        delayLong(10);
        while (PORTBbits.RB5);
    }

    LATA = 0x00;
    LATC = 0x00;

    LED1 = 1;
    for (x = 0; x < 10; x++){
        LED0 = !LED0;
        LED1 = !LED1;
        LED2 = !LED2;
        delayLong(1);
    }

    LED0 = 0;
    LED1 = 0;
    LED2 = 0;

    MMAdata = readRegister(0x0D);  // Read WHO_AM_I register
    if (MMAdata == 0x2A) { // WHO_AM_I should always be 0x2A
        initMMA8452(2, 0);  // init the accelerometer if communication is OK
    } else {
        LATA = MMAdata;
        while(1) ; // Loop forever if communication doesn't happen
    }
    
    RBIF = 0;           // Clear flags
    INT1IF = 0;
    INT2IF = 0;
    Usr1 = 0;
    Usr2 = 0;
    Int1 = 0;
    Int2 = 0;

    INTCONbits.GIE = 1;

    while (1) {
        if (Usr1) {
            flashAllInward(1);
            flashAllOutward(1);
            flashAllInward(1);
            flashAllOutward(1);
            Usr1 = 0;
        } else if (Usr2) {
            bubbleGum(6);
            Usr2 = 0;
        } else if (Int1) {
            flashAllOutward(1);
            Int1 = 0;
        } else if (Int2) {
            if ((ACTdataP & 0b01000000) == 0b01000000) {    // Z axis
                allOn(5);
                if ((ACTdataP & 0b00000100) == 0b00000100) {
                    flashLeft(2);
                } else {
                    flashRight(2);
                }
            } else if ((ACTdataP & 0b00100000) == 0b00100000) {  // Y axis
                allRed(5);
                if ((ACTdataP & 0b00000010) == 0b00000010) {
                    flashLeft(2);
                } else {
                    flashRight(2);
                }
            } else if ((ACTdataP & 0b00010000) == 0b00010000) { // X axis
                allBlue(5);
                if ((ACTdataP & 0b00000001) == 0b00000001 ) {
                    flashLeft(2);
                } else {
                    flashRight(2);
                }
            } else {
                flashAllInward(1);
            }
            Int2 = 0;
        } else {
            Sleep();
        }
    }
}

