# SCbusinessCardHolder
Screaming Circuits business card holder, V2.1

The Screaming Circuits business card holder is a multi-function device intended for your amusement and as a demonstration of our workmanship.

After soldering in the pin headers, attaching the rubber feet, and inserting the batteries, it’s ready to go. Place it on your desk and put about ten business cards in. When someone takes a card (or if you pound on your keyboard hard enough) some of the LEDs will flash.

If you tip it up, so that the LEDs run along the bottom, it will act as a spirit level, and as a short ruler. It’s not angle calibrated. Doing so is up to you. 

The microcontroller fitted is of the Microchip PIC18F46K22 family. The initial version was produced with a PIC18F43K22 – the same, but with less FLASH and SRAM. The accelerometer is a Freescale MMA8452Q. The schematic and layout were created with EagleCAD. The code was written and compiled with Microchip XC8 in Mplab-X.

One of the pin headers is connected to the I2C and SPI bus pins on the MCU. The other is connected to the Microchip ICSP (in circuit serial programming) pins on the MCU. Button Usr 1 is connected to I/O pin RB4, and Usr 2 is connected to RB5.

