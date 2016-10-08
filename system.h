/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* System operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        64000000L
#define _XTAL_FREQ      64000000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
