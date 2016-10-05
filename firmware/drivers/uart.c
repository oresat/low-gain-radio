/*!
 * \file    uart.c
 * \brief   UART API
 *
 * \defgroup uart
 * @{
 */

/*

Transmitting:
   TIE  - (UARTx_C2) Transmit Interrupt Enable for TDRE
   TCIE - (UARTx_C2) Transmit Complete Interrupt Enable for TC
   TDRE - (UARTx_S1) Transmit Data Register Empty Flag
   TC   - (UARTx_S1) Transmit Complete flag

 */

#include "v1_2.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#include "led.h"
#include "clocks.h"
#include "ringbuffer.h"

#include "uart.h"
static const struct pin_assign TX [] =
{
	{.module = &UART0, .pin = {&PORTA, 2},  .alt = 2},
	{.module = &UART0, .pin = {&PORTB, 17}, .alt = 3},
	{.module = &UART0, .pin = {&PORTD, 7},  .alt = 3},
	{.module = &UART1, .pin = {&PORTA, 19}, .alt = 3},
	{.module = &UART1, .pin = {&PORTC, 4},  .alt = 3},
	{.module = &UART1, .pin = {&PORTE, 0},  .alt = 3},
	{.module = &UART2, .pin = {&PORTD, 5},  .alt = 3},
	{.module = &UART2, .pin = {&PORTE, 16}, .alt = 3},
	{}
};

static const struct pin_assign RX [] =
{
	{.module = &UART0, .pin = {&PORTA, 1},  .alt = 2},
	{.module = &UART0, .pin = {&PORTD, 6},  .alt = 3},
	{.module = &UART1, .pin = {&PORTA, 18}, .alt = 3},
	{.module = &UART1, .pin = {&PORTC, 3},  .alt = 3},
	{.module = &UART1, .pin = {&PORTE, 1},  .alt = 3},
	{.module = &UART2, .pin = {&PORTD, 4},  .alt = 3},
	{.module = &UART2, .pin = {&PORTE, 17}, .alt = 3},
	{}
};


bool uart0_intr_initialized_g = false;

Ringbuffer uart0_tx_buff;
Ringbuffer uart0_rx_buff;

#ifdef DEBUG_UART
bool  uart0_intr_flag_g  = false; // For testing
// bool  uart1_intr_flag_g  = false;
// bool  uart2_intr_flag_g  = false;
#endif

void isr_uart0(void)
{
#ifdef DEBUG_UART
	uart0_intr_flag_g = true;
#endif

	// // is it TDRE?
	if(UART0.S1 & UART_TIE_SR1_TDRE)
	{
		if(!rb_is_empty(&uart0_tx_buff))
		{
			char c;
			if(rb_get_elem(&c, &uart0_tx_buff))
			{
				UART0.D = c;
			}
		}
		else
		{
			UART0.C2 &= ~(UART_TIE_SR1_TDRE);
		}
	}
	// // is it RDRF?
	if(UART0.S1 & UART_RIE_SR1_RDRF)
	{
		if(!rb_is_full(&uart0_rx_buff))
		{
			uint8_t c;
			c = UART0.D;
			rb_put_elem(c, &uart0_rx_buff) ;
			// led_action(TOGGLE, led8);
		}
	}
}

void uart0_init_poll(volatile struct uart0 * UART, const struct uart_config * config)
{
	enable_uart0_clock();
	UART->C4 |= (OSR_MASK & 15);
	uart12_init_poll((volatile struct uart *) UART, config);
}

void uart0_read_poll(volatile struct uart0 * UART, size_t len, uint8_t * buffer)
{
	uart12_read_poll((volatile struct uart *) UART, len, buffer);
}

bool uart0_char_poll(volatile struct uart0 * UART,  uint8_t * buffer)
{
	return uart12_char_poll((volatile struct uart *) UART, buffer);
}

void uart0_write_poll(volatile struct uart0 * UART, size_t len, uint8_t * buffer)
{
	uart12_write_poll((volatile struct uart *) UART, len, buffer);
}

void uart12_init_poll(volatile struct uart * UART, const struct uart_config * config)
{
	if(UART == &UART1)
	{
		enable_uart1_clock();
	}
	if(UART == &UART2)
	{
		enable_uart2_clock();
	}

	set_pin_alt(TX, UART, &config->TX);
	set_pin_alt(RX, UART, &config->RX);

	/* br = baud clock / concat(BDH[4:0], BDL[7:0]) * 16/
	   baud clock for UART[1,2] is the bus clock which is the system clock
	   divided by 2. See UART section of data book for equation and section
	   4 on clock distribution for clock definitions
	*/

	uint16_t        BR  = (uart_clock_input / OSRVAL) / config->baud;
	uint8_t         BDH = (BR >> 8) & 0x1F;
	uint8_t         BDL = BR & 0xFF;

	UART->BDH = BDH;
	UART->BDL = BDL;

	#ifdef DEBUG_UART
	UART->C1 = UART_CR1_LOOPS;
	#endif

	UART->C2 = UART_CR2_TE | UART_CR2_RE;
}

void uart12_read_poll(volatile struct uart * UART, size_t len, uint8_t * buffer)
{
	if(!len)
	{
		return;
	}

	for(unsigned int i = 0; i < len; ++i)
	{
		/* poll receive data register full flag */
		while(!(UART->S1 & UART_RIE_SR1_RDRF));

		buffer[i] = UART->D;
	}
}

bool uart12_char_poll(volatile struct uart * UART, uint8_t * buffer)
{
	/* check receive data register full flag */
	if (!(UART->S1 & UART_RIE_SR1_RDRF))
	{
		return false;
	}
	*buffer = UART->D;
	return true;
}

void uart12_write_poll(volatile struct uart * UART, size_t len, uint8_t * buffer)
{
	if(!len)
	{
		return;
	}

	/* write bytes to data register */
	for(unsigned int i = 0; i < len; ++i)
	{
		UART->D = buffer[i];

		/* poll transmit data register empty flag */
		while(!(UART->S1 & UART_TIE_SR1_TDRE));
	}
}

/*!  \warn __enable_irq();  &&  NVIC_EnableIRQ(UART0_IRQn);  Must be called
 * somewhere else or no interrupt
 */
void uart0_init_intr(const struct uart_config * config)
{
	rb_initialize(&uart0_tx_buff);
	rb_initialize(&uart0_rx_buff);

	set_pin_alt(RX, &UART0, &config->RX);
	uart0_init_poll(&UART0, config);

	// Enable rx interrupts on RIE
	UART0.C2 |= UART_RIE_SR1_RDRF;

	uart0_intr_initialized_g = true;
}


inline uint16_t num_uart0_rx_chars_avail() {
	return uart0_rx_buff.num_entries;
}

bool uart0_getchar_intr(char * c)
{
	if(rb_is_empty(&uart0_rx_buff))
	{
		return false;
	}
	if(!rb_get_elem(c, &uart0_rx_buff))
	{
		return false;
	}
	return true;
}

bool uart0_writechar_intr(char c)
{
	if(!uart0_intr_initialized_g)
	{
		return false;
	}

	__disable_irq();
	NVIC_DisableIRQ(UART0_IRQn);
	UART0.C2 |= UART_TIE_SR1_TDRE;  // use TDRE flag to govern ready for next char
	if(!rb_put_elem(c, &uart0_tx_buff))
	{
		return(false);
	}
	NVIC_EnableIRQ(UART0_IRQn);
	__enable_irq();
	return(true);
}

bool uart0_writestr_intr(char * s)
{
	if((s == NULL) || !uart0_intr_initialized_g)
	{
		return false;
	}

	__disable_irq();
	NVIC_DisableIRQ(UART0_IRQn);
	UART0.C2 |= UART_TIE_SR1_TDRE;  // use TDRE flag to govern ready for next char
	do
	{
		if(!rb_put_elem(*s, &uart0_tx_buff))
		{
			return(false);
		}
		++s;
	}
	while(*s != '\0');

	NVIC_EnableIRQ(UART0_IRQn);
	__enable_irq();
	return(true);
}
/*! @} */

