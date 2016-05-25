/*
	Low Gain Radio firmware

	Programmed by William Harrington
*/
#include "uart.h"
#include "transceiver.h"
#include "clksetup.h"

/* LNA Enable */
#define PTB0 (1 << 0)

/* PA Enable */
#define PTB1 (1 << 1)

/* LED5 */
#define PTC1 (1 << 1)

/* LED6 */
#define PTC2 (1 << 2)

/* LED7 */
#define PTC3 (1 << 3)

/* LED8 */
#define PTC4 (1 << 4)

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

	/* port B pins */
	PORTB.PCR[0] |= alt1;
	PORTB.PCR[1] |= alt1;

	/* port C pins */
	PORTC.PCR[1] |= alt1;
	PORTC.PCR[2] |= alt1;
	PORTC.PCR[3] |= alt1;
	PORTC.PCR[4] |= alt1;

	/* set data direction as output */
	GPIOB.PDDR |= PTB1 | PTB0;
	GPIOC.PDDR |= PTC4 | PTC3 | PTC2 | PTC1;

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
	configure_transceiver(Mode_TX, PAOutputCfg(PA1, 0));
	GPIOB.PTOR = PTB1;
	GPIOB.PTOR = PTB0;

	uint8_t alive = 'G';
	uint8_t txbyte = 0x55;

	while(1) {
		uart_write(&UART0, 1, &alive);

		//trans_write_register(transceiver.RegFifo, &alive, 1);
		//trans_write_register(transceiver.RegFifo, &txbyte, 1);

		for(uint32_t i = 0; i < 1000000; ++i);

		/* toggle LED connected to PTB2 */
		GPIOC.PTOR = PTC1;
	}
	return 0;
}
