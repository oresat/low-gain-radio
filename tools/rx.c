/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "uart.h"
#include "led.h"
#include "transceiver.h"
#include "clksetup.h"

/* green LED */
#define PTB1 (1 << 1)
struct LED green = {
	.gpio = &GPIOB,
	.pin = PTB1,
	.active_level = 1
};

/* red LED */
#define PTB2 (1 << 2)
struct LED red = {
	.gpio = &GPIOB,
	.pin = PTB2,
	.active_level = 1
};
/* blue LED */
#define PTB17 (1 << 17)
struct LED blue = {
	.gpio = &GPIOB,
	.pin = PTB17,
	.active_level = 1
};

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

	PORTD.PCR[5] |= alt1; //used as an input for detecting the transceivers fifonotempty sig

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
	configure_transceiver(Mode_RX, PAOutputCfg(PA0, 0));

	trans_write_register(transceiver.RegDioMapping1, (uint8_t[]){0x65}, 1);
	trans_write_register(transceiver.RegDioMapping2, (uint8_t[]){0x80 | (1<<2)}, 1);

	uint8_t rxbyte = 0x0;
	uint8_t alive = 0x44;

	while(1) {
		/* read fifo register in transceiver block */
		trans_read_register(transceiver.RegFifo, &rxbyte, 1);
		/* test case 1: UART0 module, passed, passes when RDRF not polled as well */
		uart_write(&UART0, 1, &rxbyte);
		if(rxbyte == 0){
			led(TOGGLE, green);
		}
		
		led(TOGGLE, red);
		for(uint32_t i = 0; i < 500000; ++i)
			if(GPIOE.PDIR)
				led(TOGGLE, blue);
;

	}
	return 0;
}
