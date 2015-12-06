/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "kw0x.h"

void initialize_clock(void){
	/* simple clock configuration */

	/* set PLL external reference divider (PRDIV0) to 16 */
	MCG.C5 = 0xF;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 = 0x40;

	/* select PLL instead of FLL */
	MCG.C6 = 0x40;

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	 */
	MCG.C2 |= 0x14;

	/* enable external oscillator */
	OSC0.CR = 0x80;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* enable clock for SPI modules */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for TPM, RTC modules */
	SIM.SCGC6 |= 0x27000000;

	return;
}

void initialize_gpio(void){

	/* modify mux to select alt 1 functionality
	   for PTB1, PTB2, PTB17.
	   Alt 1 functionality is just GPIO
	*/
	PORTB.PCR[1] |= 0x100;
	PORTB.PCR[2] |= 0x100;
	PORTB.PCR[17] |= 0x100;

	/* set data direction as output */
	GPIOB.PDDR |= 0x20006;

	/* turn all LEDs of by pulling pins high */
	GPIOB.PTOR = 0x20006;

	return;
}

void initialize_spi(void){
	/* configure SPI0 */
	SPI0.C1 = 0xF2;		/* enable interrupts, enable SPI system, transmit interrupt enabled
				   active high SPI clock, first edge on clk occurs at middle of the first cycle of a data transfer
				   enable slave select output, spi serial data transfers start with MSB
				 */
	SPI0.C2 = 0x10;		/* enable mode fault function, automatically select mode fault input or slave select output */
	SPI0.BR = 0x24;		/* 12.5 kbps baud rate */

	/* this code causes an unhandled exception...why? */
	//SPI0.C3 = 0x1;		/* set bit 0 to enable FIFO mode */
	//SPI0.C3 |= 0x8;		/* set bit 3 to make it such that writing to CI register clears interrupts */

	return;
}

void initialize_tpm(void){
  	TPM0.SC = 0x8;
	TPM1.SC = 0x8;
	TPM2.SC = 0x8;
  	return;
}

int main(void) {

	/* variable for delay loop */
	int i;

	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();
	initialize_spi();
	initialize_tpm();

	while(1) {
		/* toggle output with toggle output register */
		/* lights all LEDs on MCU */
	  	GPIOB.PTOR = 0x00004;
		for(i = 0; i < 1000000; ++i);
	}
	return 0;
}
