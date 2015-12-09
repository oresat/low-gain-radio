/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "kw0x.h"

void initialize_clock(void){
	/* simple clock configuration */

	/* set PLL external reference divider (PRDIV0) to 16 */
	//MCG.C5 = 0xF;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	//MCG.C5 |= 0x40;

	/* select PLL instead of FLL */
	//MCG.C6 = 0x40;
	//MCG.C6 |= 0x68;

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	 */
	//MCG.C2 |= 0x14;
	//MCG.C2 |= 0x10;

	/* enable external oscillator */
	//OSC0.CR = 0x80;

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

int initialize_spi(void){
	/* now let's set up the SPI interface for the transceiver */
	/* first select the proper mux setting on each pin needed */
	PORTC.PCR[5] |= 0x200;
	PORTC.PCR[6] |= 0x200;
	PORTC.PCR[7] |= 0x200;
	PORTD.PCR[0] |= 0x200;
	PORTE.PCR[2] |= 0x100;
	PORTE.PCR[3] |= 0x100;

	/* configure SPI0 */
	SPI0.C1 = 0x52;
	SPI0.C2 = 0xD0;
  	
	/* poll the transmit buffer empty flag */
	while(!(SPI0.S & (1 << 5)));
	/* write to SPI0.DH and SPI0.DL */
	SPI0.DH = 0xA6;		/* we want to write to register 0x26 in the transceiver, but it needs be encoded with a 1 at the MSB for a write */ 
	SPI0.DL = 0x00;		/* clear the bits in register 0x26 of the transceiver block */
	while(SPI0.S & (1 << 7)); /* wait for read buffer full flag */
	volatile uint16_t mySPI = (uint16_t) SPI0.DL; /* read the lower half of the data register */

	return 1;
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
	int myInit = initialize_spi(); /* if this returns, we're good */
	initialize_tpm();

	while(1) {
	  	/* if we get here, myInit should be set, and then we light some LEDs */
	  	if(myInit){
		  	/* toggle LED connected to PTB2 */
	  		GPIOB.PTOR = 0x00004;

			/* delay loop */
			for(i = 0; i < 1000000; ++i);
	  	}
	}
	return 0;
}
