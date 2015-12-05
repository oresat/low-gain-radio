/*
	Example clock configuration setup

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */

/* header contains register definitions */
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

int main(void) {
  	initialize_clock(); /* call clock initialization function */
	while(1) {
	  /* do stuff here */
	}
	return 0;
}
