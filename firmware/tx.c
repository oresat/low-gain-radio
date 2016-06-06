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

	static uint8_t alive = 0x7;
	//static uint8_t txbytes[] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44};
	static uint8_t txbytes[] = {0, 1, 2, 3, 4, 5};
	static uint8_t txbyte = 0xF0;
	static uint8_t sleep = 0x4;
	static uint8_t transmit = 0xC;
	static uint8_t tx_ready = 0;

	trans_write_register(transceiver.RegOpMode, &sleep, 1);

	while(1) {
		//uart_write(&UART0, 1, &alive); //I'm alive signal for the sys controller
		
		/* write to transceiver fifoe to transmit data */
		//trans_write_register(transceiver.RegOpMode, &transmit, 1);

		
		/*while((tx_ready & 0x20) != 32){
			trans_read_register(transceiver.RegIrqFlags1, &tx_ready, 1);
		}
		tx_ready = 0;*/
		
		
		GPIOB.PTOR = PTB2;
		trans_write_register(transceiver.RegFifo, txbytes, 6);
		//for(uint32_t i = 0; i < 500000; ++i);
		/* toggle LED connected to PTB2 */
		GPIOB.PTOR = PTB1;
		/* test case 1: UART0 module, passed, passes when RDRF not polled as well */
		//uart_write(&UART0, 1, &txbyte);
		
	
		for(uint32_t i = 0; i < 10000000; ++i);

		
	}
	return 0;
}
