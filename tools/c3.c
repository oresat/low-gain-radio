/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "kw0x.h"
#if 1
void initialize_spi(void){
	/* enable clock for SPI modules */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;


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

	//SPI0.DH = 0x81; //Transceiver Op Mode Register
	//SPI0.DL = 0xC;  //Change to transmitter mode

	//SPI0.DH = 0x83; //Bitrate MSB register
	//SPI0.DL = 0x68;

	//SPI0.DH = 0x84; //Bitrate LSB register
	//SPI0.DL = 0x2B;

	//SPI0.DH = 0x85; //Frequency deviation MSB register
	//SPI0.DL = 0x03;

	//SPI0.DH = 0x86; //Frequency deviation LSB register
	//SPI0.DL = 0x33;

	//SPI0.DH = 0x87; //RF carrier frequency MSB
	//SPI0.DL = 0x6D;

	//SPI0.DH = 0x88; //RF carrier frequency mid byte
	//SPI0.DL = 0x20;
	/* disable SPI module clock because theo said it would get mad if I didn't! */
	SIM.SCGC4 &= 0xFF3FFFFF;

	/* disable port module clock because theo said it would get mad if I didn't! */
	SIM.SCGC5 &= 0xFFFFC1FF;


}

void initialize_clock(void){
	/* simple clock configuration that involves initializing the SPI so we can get the external clock reference from the transceiver */

	/* set PLL external reference divider (PRDIV0) to 16, this will give us 2 MHz */
	MCG.C5 = 0xF;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 |= 0x40;

	/* select PLL instead of FLL */
	MCG.C6 |= 0x40;

	/* wait for PLL lock */
	while(!(MCG.S & (1 << 6)));

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	*/
	MCG.C2 |= 0x14;

	/* enable external oscillator */
	OSC0.CR = 0x80;

	/* now enable clock for SPI modules, AGAIN! */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* enable clock for TPM, RTC modules */
	SIM.SCGC6 |= 0x27000000;

	return;
}
#endif
void initialize_gpio(void){
	/* procedure for getting the GPIO going on pins PTB1, PTB2, PTB17 */

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
#if 0
void initialize_tpm(void){
  	/* procedure for initializing Timer/PWM module */

	/* Clock mode select for each module, make TPM counter increment on every TPM counter clock */
  	TPM0.SC = 0x8;
	TPM1.SC = 0x8;
	TPM2.SC = 0x8;

	/* more needs to be done here, maybe? */
  	return;
}
#endif

uint32_t i;

int main(void) {

	/* call initialization procedures */

	initialize_spi();

	initialize_clock();

	initialize_gpio();

	//initialize_tpm();

	//asm volatile ("cpsie   i");
	while(1) {
		/* toggle LED connected to PTB2 */
		GPIOB.PTOR = 0x00004;

		/* delay loop */
		//for(i = 0; i < 100000; ++i);
	}
	return 0;
}
