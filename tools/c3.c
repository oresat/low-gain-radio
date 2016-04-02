/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "drivers/uart.h"
#include "drivers/transceiver.h"
#include "drivers/spi.h"

#if 1



void initialize_spi(void){
	/* enable clock for SPI modules */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* The transceiver requires a specific SPI configuration*/
	initialize_trans_spi(&SPI0);

	/* Send to transceiver to get 32MHz clock signal on PTA18 */
	uint8_t RegDioMapping2Cfg = 0x0;
	trans_write_register(transceiver.RegDioMapping2, &RegDioMapping2Cfg, 1);

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
void initialize_uart(void){
	/* UART0 configuration */
	struct uart_config myUART = {
		/* pin for transmit = PTA1 */
		.TX = {.port=&PORTA, .pin=1,},

		/* pin for receive = PTA2 */
		.RX = {.port=&PORTA, .pin=2,},

		/* baud rate */
		.baud = 115200,
	};
	uart0_init(&UART0, &myUART);
}

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

int main(void) {

	/* delay loop for POR, transceiver not available for 10ms */
	for(uint32_t i = 0; i < 1000000; ++i);
	//test_spi_8();
	/* call initialization procedures */
	initialize_spi();
	initialize_clock();
	initialize_gpio();

	//initialize_uart();
	//initialize_tpm();
   	//asm volatile ("cpsie   i");

	/* this function is in transceiver.c if you want more details */
	configure_transceiver();

	
	uint8_t FIFObyte = 0x55;
	uint8_t bleh2 = 0;

	while(1) {
		for(uint32_t i = 0; i < 1000000; ++i);

		trans_write_register(transceiver.RegFifo, &FIFObyte, 1);
		
		//spi_transaction_16(&SPI0, 1, &FIFObyte, &bleh);
		//spi_transaction_8(&SPI0, 2, FIFObytes, &bleh2);

	       	/* toggle LED connected to PTB2 */
		GPIOB.PTOR = 0x00004;
	}
	return 0;
}
