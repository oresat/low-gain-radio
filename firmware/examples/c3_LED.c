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

	return;
}

int main(void) {

	/* variable for delay loop */
	int i;

	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();

	while(1) {
		/* toggle output with toggle output register */
		/* lights all LEDs on MCU */
		GPIOB.PTOR = 0x20006;

		/* delay */
		for(i = 0; i < 1000000; ++i);

		/* turn off two LEDs */
		GPIOB.PTOR = 0x20004;

		/* delay */
		for(i = 0; i < 1000000; ++i);

		/* turn off LED that was on, turn next one on */
		GPIOB.PTOR = 0x00006;

		/* delay */
		for(i = 0; i < 1000000; ++i);

		/* turn off LED that was on, turn next one on */
		GPIOB.PTOR = 0x20004;

		/* delay */
		for(i = 0; i < 1000000; ++i);

		/* turn off LED that was on, end of pattern */
		GPIOB.PTOR = 0x20000;

		/* delay */
		for(i = 0; i < 1000000; ++i);
	}
	return 0;
}
