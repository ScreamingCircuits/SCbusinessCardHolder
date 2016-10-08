/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include "globals.h"
#include "user.h"
#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{

    // datasheet 41412D.pdf. OSCCON registers are on page 32
    OSCCONbits.IDLEN   = 0;   	//Sleep on SLEEP instruction
    OSCCONbits.IRCF2   = 1;	//Internal OSC to 16MHz (111)
    OSCCONbits.IRCF1   = 1;
    OSCCONbits.IRCF0   = 1;
    OSCCONbits.OSTS    = 0;     //Running from internal oscillator
    OSCCONbits.SCS1    = 1;   	//Internal oscillator block
    OSCCONbits.SCS0    = 0;     // Secondary oscillator is off

    // datasheet 41412D.pdf. OSCCON2 registers are on page 33
    OSCCON2bits.PLLRDY = 1;     // Clock comes from 4X PLL
    OSCCON2bits.SOSCRUN = 0;    // Secondary clock not used
    OSCCON2bits.MFIOSEL = 0;    // Medium frequency clock not used
    OSCCON2bits.SOSCGO = 0;     // Secondary oscillator is off
    OSCCON2bits.PRISD  = 1;     // Primary oscillator on

    // datasheet 41412D.pdf. OSCTUNE registers are on page 37
    OSCTUNEbits.INTSRC = 1;     // Low frequency comes from main clock. Not used in this application
    OSCTUNEbits.PLLEN  = 1;     // Enable 4X PLL
}
