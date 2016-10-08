/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include "globals.h"
#include "user.h"
#include "system.h"


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Interrupt priorities have been disabled. All are equal */

void interrupt isr(void) {

    if (RBIE && RBIF) {             // Check for PORTB change, clear all INT flags & reset timer
        Usr1 = !PORTBbits.RB4;
        Usr2 = !PORTBbits.RB5;
    } else if ((INT1IE && INT1IF) || (INT2IE && INT2IF)) {
        MMAdata = readRegister(0x0C);
        ACTdataT = readRegister(0x1E);
        ACTdataP = readRegister(0x22);
        if (INT1IF) {
            Int1 = 1;
        } else if (INT2IF) {
            Int2 = 1;
        }
    }

    RBIF = 0;                       // Clear interrupt flag for PORTB
    INT1IF = 0;
    INT2IF = 0;
}

