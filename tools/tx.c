/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "uart.h"
#include "transceiver.h"
#include "clksetup.h"

/* green LED */
#define PTB1 (1 << 1)

/* red LED */
#define PTB2 (1 << 2)

/* blue LED */
#define PTB17 (1 << 17)

/* alternative function number */
#define pin_disable (0 << 8)
#define alt1 (1 << 8)
#define alt2 (2 << 8)
#define alt3 (3 << 8)
#define alt4 (4 << 8)
#define alt5 (5 << 8)
#define alt6 (6 << 8)
#define alt7 (7 << 8)

void initialize_gpio(void){
	/* procedure for getting the GPIO going on pins PTB1, PTB2, PTB17 */

	/* select alt 1 functionality
	   for PTB1, PTB2, PTB17.
	   Alt 1 functionality is just GPIO
	*/
	PORTB.PCR[1] |= alt1;
	PORTB.PCR[2] |= alt1;
	PORTB.PCR[17] |= alt1;

	/* set data direction as output */
	GPIOB.PDDR |= PTB17 | PTB2 | PTB1;

	/* turn all LEDs of by pulling pins high */
	GPIOB.PTOR = PTB17 | PTB2 | PTB1;

	return;
}

void initialize_uart0(void){
	/* UART0 configuration */
	struct uart_config myUART = {
		/* pin for transmit = PTA2 */
		.TX = {.port=&PORTA, .pin=2,},

		/* pin for receive = PTA1 */
		.RX = {.port=&PORTA, .pin=1,},

		/* baud rate */
		.baud = 9600,
	};
	uart_init(&UART0, &myUART);
}

int main(void) {
	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();
	initialize_uart0();

	/* this function is in transceiver.c if you want more details */
	configure_transceiver(Mode_TX, PAOutputCfg(PA0, 0x1F));

	uint8_t alive = 'G';
	uint8_t txbyte = 0x55;

	while(1) {
		uart_write(&UART0, 1, &alive); //I'm alive signal for the sys controller
		
		trans_write_register(transceiver.RegFifo, &txbyte, 1);

		/* test case 1: UART0 module, passed, passes when RDRF not polled as well */
		uart_write(&UART0, 1, &txbyte);
		for(uint32_t i = 0; i < 1000000; ++i);

		/* toggle LED connected to PTB2 */
		GPIOB.PTOR = PTB1;
	}
	return 0;
}
