#include "kw0x.h"

int main(void) {
	int i;

	/* clock configuration */
	MCG.C5 = 0xF;
	MCG.C5 = 0x40;
	MCG.C6 = 0x40; /* selects PLL instead of FLL */
	MCG.C2 |= 0x14; /* set encoding to high frequency range, select source for the external reference clock */
	OSC0.CR = 0x80; /* enable external oscillator */
	SIM.SCGC5 |= 0x3E00; /* Enable clock for all ports */

	/* modify mux to select alt 1 functionality
	   for PTB1, PTB2, PTB17.
	   Alt 1 functionality is just GPIO
	*/
	PORTB.PCR[1] |= 0x100;
	PORTB.PCR[2] |= 0x100;
	PORTB.PCR[17] |= 0x100;
	GPIOB.PDDR |= 0x20006; /* set as OUTPUT */

	while(1) {
	  /* toggle output with toggle output register */
		GPIOB.PTOR = 0xFFFFFFFF;
		for(i = 0; i < 1000000; ++i);
	}
	return 0;
}
