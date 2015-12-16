/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include "driverSPI0.h"

void spi0_init(void){
	/* select the proper mux setting on each pin involved in spi0 */
	PORTC.PCR[5] |= 0x200;
	PORTC.PCR[6] |= 0x200;
	PORTC.PCR[7] |= 0x200;
	PORTD.PCR[0] |= 0x200;
	PORTE.PCR[2] |= 0x100;
	PORTE.PCR[3] |= 0x100;

	/* configure SPI0 */
	SPI0.C1 = 0x52;		/* interrupt enable off, system enable on, tx interrupt enable off, spi module configured as master, CPOL=0, CPHA=0, SS OE on, data transfers start with MSB */
	SPI0.C2 = 0xD0;		/* match interrupt enable on, 16bit mode, tx dma enable off, master mode fault function enable on, bidirectional mode OE off, rx dma enable off, stop in wait mode off, spi pin control 0 off (meant for bidirectional pin configurations) */

	return;
}

uint8_t spi0_read(uint8_t addr){
	/* need to figure out if we are in 16-bit mode or 8-bit mode
	   if mode is 0, 8-bit mode. if mode is 1, 16-bit mode.
	 */
  	bool mode = SPI0.C1 & (1 << 6);

	if(mode){
	  	/* 16-bit mode */
		SPI0.DH = addr;
	}
	else{
		/* 8-bit mode */
		SPI0.DL = addr;
	}

	/* check SPI read FIFO empty flag, wait if not set */
	while((SPI0.S & (1 << 0)));

	return SPI0.DL;
}

void spi0_write(uint8_t addr, uint8_t data){
	/* need to figure out if we are in 16-bit mode or 8-bit mode
	   if mode is 0, 8-bit mode. if mode is 1, 16-bit mode.
	 */
  	bool mode = SPI0.C1 & (1 << 6);

	/* set MSB, needed to perform write */
	addr = addr | (1 << 7);

	/* poll the transmit buffer empty flag */
	while(!(SPI0.S & (1 << 5)));

	if(mode){
	  	/* 16-bit mode */
		SPI0.DH = addr;
		SPI0.DL = data;
	}
	else{
		/* 8-bit mode */
		SPI0.DL = addr;
		SPI0.DL = data;
	}

	/* should we do some verification here? */
}
