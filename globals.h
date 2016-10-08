#define HARDWARE            "SC1016-bcardhldr"
#define HARDWARE_desc       "Business card holder and bubble level"
#define VERSION             "2.1"
#define URL                 "http://www.screamingcircuits.com.com"


/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
//#include <xc.h>             /* XC8 General Include File */
//#include "system.h"         /* System funct/params, like osc/peripheral config */
//#include "user.h"           /* User funct/params, such as InitApp */

/******************************************************************************/
/*Personality settings                                                        */
/******************************************************************************/

    #define LED0 LATEbits.LE0
    #define LED1 LATEbits.LE1
    #define LED2 LATEbits.LE2

    char Usr1, Usr2;
    char Int1, Int2;
    unsigned char MMAdata, ACTdataT, ACTdataP;

