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

void initialize_uart(void){
	/* UART configuration */
	struct uart_config myUART = {
		/* pin for transmit = PTC4 */
		//.TX = {.port=&PORTC, .pin=4,},

		/* pin for transmit = PTD5 */
		.TX = {.port=&PORTD, .pin=5,},

		/* pin for receive = PTC3 */
		//.RX = {.port=&PORTC, .pin=3,},

		/* pin for receive = PTD4 */
		.RX = {.port=&PORTD, .pin=4,},

		/* baud rate */
		.baud = 9600,
	};
	//uart_init(&UART1, &myUART);
	uart_init(&UART2, &myUART);
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

int main(void) {
	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();

	//initialize_uart();
	initialize_uart0();
	//initialize_tpm();
   	//asm volatile ("cpsie   i");

	/* this function is in transceiver.c if you want more details */
	configure_transceiver(Mode_TX, PAOutputCfg(PA0, 0x1F));

	uint8_t txbyte = 0x55;
	//static uint8_t txbyte[3] = {0x55, 0xD, 0xA};

	uint8_t rxbyte = 0x0;

	while(1) {

		/* test case 1: UART0 module, passed, passes when RDRF not polled as well */
          	uart_write(&UART0, 1, &txbyte);
          	//uart_read(&UART0, 1, &rxbyte);

          	/* test case 2: UART1 module, passed only when RDRF was not polled */
		//uart_write(&UART1, 1, &txbyte);
          	//uart_read(&UART1, 1, &rxbyte);

		/* test case 3: UART2 module, passed only when RDRF was not polled */
		//uart_write(&UART2, 1, &txbyte);
          	//uart_read(&UART2, 1, &rxbyte);

		for(uint32_t i = 0; i < 1000000; ++i);

	       	/* toggle LED connected to PTB2 */
		GPIOB.PTOR = PTB1;

		if(rxbyte == 0x55){
                	GPIOB.PTOR = PTB17;
		}
	}
	return 0;
}
