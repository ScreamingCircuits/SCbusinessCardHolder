/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include "globals.h"
#include "user.h"
#include "system.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    LATA  = 0x00;
    LATB  = 0x00;
    LATC  = 0x00;
    LATD  = 0x00;
    LATE  = 0x00;

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;

    // Portsset to input for input switches and interrupts
    TRISB   |= 1 << 5;      // RB5 is input: Usr 2
    TRISB   |= 1 << 4;      // RB4 is input: Usr 1
    TRISB   |= 1 << 1;      // RB1 is input: Int 1 from accelerometer
    TRISB   |= 1 << 2;      // RB2 is input: Int 2 from accelerometer

    // Usr1 and Usr2 are normally-open active low. They need to pull-up
    WPUB4 = 1;              // Weak pull-up for RB4 / S2 / Usr 1
    WPUB5 = 1;              // Weak pull-up for RB5 / S3 / Usr 2

    // MMA8452 is set up with open drain, active-low interrupt lines
    //WPUB0 = 0;              // Weak pull-up for Int1
    WPUB1 = 0;              // Weak pull-up for Int1
    WPUB2 = 0;              // Weak pull-up for Int2
    RBPU = 0;               // 0 = enable pull-ups on PORTB, provided individual WPUB bits are set

    // Interrupts
    IPEN  = 0;              // Disable Interrupt prioritoes, as they are not needed
    INTCON = 0b00000000;    // Start with everything cleared

    // MMA8452 is set up with push-pull, active-high interrupt lines
    INTEDG1 = 1;            // Int1 pin interrupt on: 1 = rising edge, 0 = falling edge
    INTEDG2 = 1;            // Int2 pin interrupt on: 1 = rising edge, 0 = falling edge

    IOCBbits.IOCB4 = 1;     // Enable IOC on pin RB4
    IOCBbits.IOCB5 = 1;     // Enable IOC on pin RB5

    RBIF = 0;               // Clear interrupt flags
    INT1IF = 0;
    INT2IF = 0;

    INT1IE = 1;             // Interrupt pin 1: Accelerometer interrupt
    INT2IE = 1;             // Interrupt pin 2: Accelerometer interrupt

    RBIE = 1;               // Port B int on change: RB4 and RB5 are Usr 1 and Usr 2

    // Set I2C pins as inputs
    TRISD |= 1 << 0;        // RD0 = SCL2/SCK2
    TRISD |= 1 << 1;        // RD1 = SDA2/SDI2

    SSP2ADD = 0x9F;         // 100 KHz I2C clock with 64 MHz system clock
    SSP2STATbits.SMP = 1;   // Slew off
    SSP2CON1bits.SSPEN = 1; // Enable I2C
    SSP2CON1 = 0b00101000;

// setting and clearing the appropriate SSPxM bits in the SSPxCON1 register and by setting the SSPxEN bit.
}


// Delay time in multiples of 10 ms
void delayLong(unsigned long x) {
    unsigned long i;
    for (i = 0; i < x; i++) {
        __delay_ms(10);
    }
}


void flashAllInward(int x) {

    for (int i = 0; i < x; i++) {
        LED0 = 0;
        LED1 = 1;
        LED2 = 0;
        LATA = 0b00000001;
        LATC = 0b10000000;
        delayLong(1);
        for (int k = 0; k < 8; k++) {
            LATA = LATA << 1;
            LATC = LATC >> 1;
            LED0 = !LED0;
            LED1 = !LED1;
            LED2 = !LED2;
            delayLong(1);
        }
    }
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
}

void flashAllOutward(int x) {

    for (int i = 0; i < x; i++) {
        LED0 = 1;
        LED1 = 0;
        LED2 = 1;
        LATA = 0b10000000;
        LATC = 0b00000001;
        delayLong(1);
        for (int k = 0; k < 8; k++) {
            LATA = LATA >> 1;
            LATC = LATC << 1;
            LED0 = !LED0;
            LED1 = !LED1;
            LED2 = !LED2;
            delayLong(1);
        }
    }
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
}


void bubbleGum(int x) {
    for (int i = 0; i < x; i++) {
        LATC = 0b01010101; // blue
        delayLong(2);
        LATA = 0b10101010; // red
        delayLong(5);

        LATA = 0b01010101; // blue
        delayLong(2);
        LATC = 0b10101010; // red
        delayLong(5);
    }
    LATA = 0x00;
    LATC = 0x00;
}


void allOn(int x) {
    LED0 = 1;
    LED1 = 1;
    LED2 = 1;
    LATA = 0xff;
    LATC = 0xff;

    delayLong(x);

    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LATA = 0x00;
    LATC = 0x00;
}


void allBlue(int x) {
    LED1 = 1;
    LATA = 0xAA;
    LATC = 0x55;

    delayLong(x);

    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LATA = 0x00;
    LATC = 0x00;
}

void allRed(int x) {
    LED0 = 1;
    LED2 = 1;
    LATA = 0x55;
    LATC = 0xAA;

    delayLong(x);

    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LATA = 0x00;
    LATC = 0x00;
}

void allLeft(int x) {
    LATA = 0xFF;
    delayLong(x);
    LATA = 0x00;
}


void allRight(int x) {
    LATC = 0xFF;
    delayLong(x);
    LATC = 0x00;
}

void flashLeft(int x) {
    LATA = 0xFF;
    __delay_ms(10);
    __delay_ms(10);
    for (int i = 0; i < x; i++) {
        //LATA = 0b10000000;
        delayLong(1);
        for (int k = 0; k < 8; k++) {
            LATA = LATA >> 1;
            delayLong(1);
        }
    }
    LATA = 0x00;
}


void flashRight(int x) {
    LATC = 0xFF;
    __delay_ms(10);
    __delay_ms(10);
        for (int i = 0; i < x; i++) {
        //LATC = 0b00000001;
        delayLong(1);
        for (int k = 0; k < 8; k++) {
            LATC = LATC << 1;
            delayLong(1);
        }
    }
    LATC = 0x00;
}

// MMA8452Q functions

// Initialize the MMA8452 registers
// See the many application notes for more info on setting all of these registers:
// http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q
// Feel free to modify any values, these are settings that work well for me.
void initMMA8452(char fsr, char dataRate){
  MMA8452Standby();  // Must be in standby to change registers

// Set up transients
  writeRegister(0x1D, 0b00011111);  //

/* Set up single and double tap - 5 steps:
   1. Set up single and/or double tap detection on each axis individually.
   2. Set the threshold - minimum required acceleration to cause a tap.
   3. Set the time limit - the maximum time that a tap can be above the threshold
   4. Set the pulse latency - the minimum required time between one pulse and the next
   5. Set the second pulse window - maximum allowed time between end of latency and start of second pulse
   for more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf */

  writeRegister(0x21, 0b01111111);  // 1. enable single/double taps on all axes

  // Set up sleep and power mode
  //writeRegister(0x29, 0x00);  // Minumum time to wake
  writeRegister(0x2A, 0b01011000);  // 100Hz data rate when awake
  writeRegister(0x2B, 0b00011111);  // Low power, Low power (0x1F adds in sleep???)

  // Set up interrupt 1 and 2
  writeRegister(0x2C, 0b01010010);  // Active high, push/pull interrupts, Pulse can wake, transient can wake (Originally 0x02)
  writeRegister(0x2D, 0b10101000);  // No DRDY, P/L and tap ints enabled (Originally 0x1B, Originally 0x19)
  writeRegister(0x2E, 0b10100001);  // DRDY on INT1, P/L and taps on INT2 (Originally 0x01)

  MMA8452Active();  // Set to active to start reading
}



// Sets the MMA8452 to standby mode.
// It must be in standby to change most register settings
void MMA8452Standby()
{
  char c = readRegister(0x2A);
  writeRegister(0x2A, c & ~(0x01));
}


// Sets the MMA8452 to active mode.
// Needs to be in this mode to output data
void MMA8452Active()
{
  char c = readRegister(0x2A);
  writeRegister(0x2A, c | 0x01);
}

#define WriteI2C write_I2C_byte
#define ReadI2C  read_I2C_byte
// Read i registers sequentially, starting at address into the dest char array
void readRegisters(char regAddress, int i, char * dest)
{
    char data;
    int status;

    //CloseI2C();
    //OpenI2C(MASTER, SLEW_OFF);
    //StartI2C();
    SSP1CON1 = 0b00101000;  // Enable I2C Master mode
   

    do {
        status = WriteI2C((MMA8452_ADDRESS<<1) | 0x01 ); //write the address of slave
        if(status == -1) { //check if bus collision happened
            data = SSPBUF; //upon bus collision detection clear the buffer,
            SSPCON1bits.WCOL=0; // clear the bus collision status bit
        }
    }
    while(status!=0); //write untill successful communication
    WriteI2C(regAddress);

    data = ReadI2C(1);
}

int write_I2C_byte(char byte_out)
{
	SSP2BUF = byte_out;
        while (SSP2STATbits.RW2);       // Wait for write to complete
	while (SSP2CON2bits.ACKSTAT);   // Wait for acknowledge from slave
    
    return(0);
}


char read_I2C_byte(char ackornot)
{
char dist;

    SSP2CON2bits.RCEN = 1;              // Set read mode
    while (SSP2CON2bits.RCEN);          // Wait until read is complete

    dist = SSP2BUF;                     // Read I2C data buffer

    if (ackornot == 1) {                // Only acknowledge if not the last char
        SSP2CON2bits.ACKDT = 0;         // Set acknowledge
        SSP2CON2bits.ACKEN = 1;         // Send acknowledge bit
        while (SSP2CON2bits.ACKEN);     // Wait for acknowledge to end
    }

    return(dist);
}

// Read a single char from address and return it as a char
char readRegister(char regAddress)
{
    char data;

    SSP2CON2bits.SEN = 1;               // Start condition
    while (SSP2CON2bits.SEN);           // Wait until bit is cleared

    write_I2C_byte(MMA8452_ADDRESS<<1);	// Send module address. 0xE0 to write to the SRF08
    write_I2C_byte(regAddress);         // Send register to read

    SSP2CON2bits.RSEN = 1;              // Start condition for the read cycle
    while (SSP2CON2bits.RSEN);          // Wait until bit is cleared

    write_I2C_byte((MMA8452_ADDRESS<<1) | 0x01 );   // Send module address with read bit on
    data = read_I2C_byte(0);            // "0" means don't acknoledge receiving because it's the last char

    SSP2CON2bits.PEN = 1;               // Initiate a Stop
    while (SSP2CON2bits.PEN);           // Wait until bit is cleared

    return data;
 }


// Writes a single char (data) into address
void writeRegister(char regAddress, char dataCommand)
{

    SSP2CON2bits.SEN = 1;               // Start condition
    while(SSP2CON2bits.SEN);            // Wait until bit is cleared

    write_I2C_byte(MMA8452_ADDRESS<<1); // Send module address
    write_I2C_byte(regAddress);         // Send address of register to write
    write_I2C_byte(dataCommand);        // Send data to write

    SSP2CON2bits.PEN = 1;               // Stop condition
    while (SSP2CON2bits.PEN);           // Wait until bit is cleared
}
