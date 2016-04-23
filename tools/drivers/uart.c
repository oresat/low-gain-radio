/* 
	Universal asynchronous receiver/transmitter driver for MKW01Z128

	Programmed by William Harrington
 */

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

//SIM.SCGC4
#define SCGC_UART0 (1 << 10)
#define SCGC_UART1 (1 << 11)
#define SCGC_UART2 (1 << 12)
//SIM.SOPT2
#define UART0SRC_MCGIRCLK (3 << 26)
#define UART0SRC_MCGPLLFLLCLK (1 << 26)

#define PLLFLLSEL (1 << 16)

//
#define TDRE (1 << 7)
#define RDRF (1 << 5)
//C2
#define TE (1 << 3)
#define RE (1 << 2)

void uart0_init(volatile struct uart0 * UART, const struct uart_config * config){
	/* select UART0 clock source to PLL */
	/* note: this step isn't needed for UART1/UART2
           since they are run off the bus clock */
	SIM.SOPT2 |= UART0SRC_MCGPLLFLLCLK | PLLFLLSEL;

	/* enable clock*/
	SIM.SCGC4 |= SCGC_UART0;
	uart12_init((volatile struct uart *) UART, config);
}

void uart0_read(volatile struct uart0 * UART, size_t len, uint8_t * buffer){
	uart12_read((volatile struct uart *) UART, len, buffer);
}

void uart0_write(volatile struct uart0 * UART, size_t len, uint8_t * buffer){
	uart12_write((volatile struct uart *) UART, len, buffer);
}


void uart12_init(volatile struct uart * UART, const struct uart_config * config){
	/* enable clock */
	if(UART == &UART1)
		SIM.SCGC4 |= SCGC_UART1;
	if(UART == &UART2)
		SIM.SCGC4 |= SCGC_UART2;

	/* setup pins */
	set_pin_alt(TX, UART, &config->TX);
	set_pin_alt(RX, UART, &config->RX);

	/* br = baud clock / concat(BDH[4:0], BDL[7:0]) */
	/* baud clock for UART[1,2] is the bus clock which is the system clock
	   divided by 2. See UART section of data book for equation and section
	   4 on clock distribution for clock definitions

	   the calculation below assumes baud clock = 24MHz
	*/
	UART->BDH = 0x0;
	UART->BDL = 0xD0;
	//UART->BDH = 0x1d;
	//UART->BDL = 0xb7;

	UART->C2 = TE | RE;
}

void uart12_read(volatile struct uart * UART, size_t len, uint8_t * buffer){
	if(!len) return;

	for(unsigned int i = 0; i < len; ++i){
		/* poll receive data register full flag */
		while(!(UART->S1 & RDRF));

		buffer[i] = UART->D;
	}
}

void uart12_write(volatile struct uart * UART, size_t len, uint8_t * buffer){
	if(!len) return;

	/* write bytes to data register */
	for(unsigned int i = 0; i < len; ++i){
		UART->D = buffer[i];

		/* poll transmit data register empty flag */
		while(!(UART->S1 & TDRE));
	}
}
