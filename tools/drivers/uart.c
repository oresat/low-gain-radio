#include "uart.h"

static const struct pin_assign TX [] = {
	{.module=&UART0, .pin={&PORTA, 2}, .alt=2},
	{.module=&UART0, .pin={&PORTB, 17}, .alt=3},
	{.module=&UART0, .pin={&PORTD, 7}, .alt=3},
	{.module=&UART1, .pin={&PORTA, 19}, .alt=3},
	{.module=&UART1, .pin={&PORTC, 4}, .alt=3},
	{.module=&UART1, .pin={&PORTE, 0}, .alt=3},
	{.module=&UART2, .pin={&PORTD, 5}, .alt=3},
	{.module=&UART2, .pin={&PORTE, 16}, .alt=3},
	{}
};

static const struct pin_assign RX [] = {
	{.module=&UART0, .pin={&PORTA, 1}, .alt=2},
	{.module=&UART0, .pin={&PORTD, 6}, .alt=3},
	{.module=&UART1, .pin={&PORTA, 18}, .alt=3},
	{.module=&UART1, .pin={&PORTC, 3}, .alt=3},
	{.module=&UART1, .pin={&PORTE, 1}, .alt=3},
	{.module=&UART2, .pin={&PORTD, 4}, .alt=3},
	{.module=&UART2, .pin={&PORTE, 17}, .alt=3},
	{}
};

void uart0_init(volatile struct uart0 * UART, const struct uart_config * config){
	/* enable clock for UART modules */
	SIM.SCGC4 |= 0x1c00; /* TODO: detect which one to turn one */

	/* setup pins */
	set_pin_alt(TX, UART, &config->TX);
	set_pin_alt(RX, UART, &config->RX);

	/* baud rate selection */
	UART->BDH = 0x1d;
	UART->BDL = 0xb7;
	UART->C1 = 0x0;
	UART->C2 = 0xC;
	UART->C3 = 0x0;
	UART->C4 = 0x0;
}

void uart_init(volatile struct uart * UART, const struct uart_config * config){
  	/* enable clock for UART modules */
	SIM.SCGC4 |= 0x1c00; /* TODO: detect which one to turn one */

	/* setup pins */
	set_pin_alt(TX, UART, &config->TX);
	set_pin_alt(RX, UART, &config->RX);

	/* baud rate selection */
	//uint32_t busClock = 24000000;
	//uint32_t baudRate = config->baud;
	//uint32_t divisor = busClock/(16*baudRate);
	//UART->BDH = (divisor & 0x1F00) >> 8;
	//UART->BDL = (divisor & 0xFF);
	UART->BDH = 0x1d;
	UART->BDL = 0xb7;
	UART->C1 = 0x0;
	UART->C2 = 0xC;
	UART->C3 = 0x0;
	UART->C4 = 0x0;
}

void uart0_read(volatile struct uart0 * UART, size_t len, uint8_t * buffer){
	uint8_t dummyBuff[len];

	uart0_transaction(UART, len, dummyBuff, buffer);

	//if(!len) return;
	/* poll the receive data register full flag */
	/* it will be 0 when empty */
	//while(!(UART->S1 >> 5));
	/* receive bytes */
	//for(size_t i = 0; i < len; ++i){
  	//buffer[i] = UART->D;
  	//}
}

void uart_read(volatile struct uart * UART, size_t len, uint8_t * buffer){
	uint8_t dummyBuff[len];

	uart_transaction(UART, len, dummyBuff, buffer);

  	//if(!len) return;
	/* poll the receive data register full flag */
	/* it will be 0 when empty */
	//while(!(UART->S1 >> 5));
	/* receive bytes */
	//for(size_t i = 0; i < len; ++i){
  	//buffer[i] = UART->D;
  	//}
}

void uart0_write(volatile struct uart0 * UART, size_t len, uint8_t * buffer){
	//uint8_t dummyBuff[len];

  	//uart0_transaction(UART, len, buffer, dummyBuff);

	/* make sure len is not 0 */
  	if(!len) return;

	/* poll transmit data register empty flag */
	while(!(UART->S1 >> 7));

        /* transmission */
	for(unsigned int i = 0; i < len; ++i){
		/* send byte */
  		UART->D = buffer[i];

		/* poll transmission complete flag */
		while(!(UART->S1 >> 6));
  	}
}

void uart_write(volatile struct uart * UART, size_t len, uint8_t * buffer){
	uint8_t dummyBuff[len];

	uart_transaction(UART, len, buffer, dummyBuff);

	//if(!len) return;
	/* poll transmit data register empty flag */
	//while(!(UART->S1 >> 7));
	//for(unsigned int i = 0; i < len; ++i){
        //UART->D = buffer[i];
	//}
}

void uart0_transaction(volatile struct uart0 * UART, size_t len, uint8_t * sendBuff, uint8_t * recvBuff){
	if(!len) return;
	for(unsigned int i = 0; i < len; ++i){
		/* poll transmit data register empty flag */
		while(!(UART->S1 >> 7));

		/* send data */
		UART->D = sendBuff[i];

		/* poll the receive data register full flag */
		/* it will be 0 when empty */
		while(!(UART->S1 >> 5));

		/* grab data */
		recvBuff[i] = UART->D;
        }
}

void uart_transaction(volatile struct uart * UART, size_t len, uint8_t * sendBuff, uint8_t * recvBuff){
	if(!len) return;
	for(unsigned int i = 0; i < len; ++i){
		/* poll transmit data register empty flag */
		while(!(UART->S1 >> 7));

		/* send data */
		UART->D = sendBuff[i];

		/* poll the receive data register full flag */
		/* it will be 0 when empty */
		while(!(UART->S1 >> 5));

		/* grab data */
		recvBuff[i] = UART->D;
        }
}
