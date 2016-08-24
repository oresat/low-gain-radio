/*  \file test.c
 *
 *   Low Gain Radio firmware
 *
 *   Gather functional testing here. Also used for examples.
 */

#include <string.h>

#include "v1_2.h"

#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#include "lgr_util.h"
#include "port.h"
#include "clocks.h"
#include "led.h"
#include "spi.h"
#include "uart.h"
#include "xcvr.h"

#include "em-printf.h"
#include "test.h"

struct spi_config spi0_config =
{
	.SCK        = {.port = &PORTC, .pin = 5,},

	.SS         = {.port = &PORTD, .pin = 0,},

	.MOSI       = {.port = &PORTC, .pin = 6,},

	.MISO       = {.port = &PORTC, .pin = 7,},

	.CPOL       = ACTIVE_HIGH,

	.CPHA       = FIRST_EDGE_MIDDLE,

	.SPIMODE    = EIGHTBIT,
};

/* This is the A4 wake-up pin */
/* Boots to pullup, interrupt enabled */
void NMIVector(void)
{
	led_action(TOGGLE, led6);
}

void isr_porta(void)
{
	led_action(TOGGLE, led7);
};

void isr_portcd(void)
{
	led_action(TOGGLE, led8);
};


/*  When something goes wrong
 */
static void error_spin_led(struct LED led)
{
	uint32_t w = 0;
	while(1)  // something went wrong with SPI
	{
		++w;
		if(w > 400000)
		{
			led_action(TOGGLE, led);
			w = 0;
		}
	}
}

/* Quick check of interrupt */
void test_porta_isr(void)
{
	uint32_t i = 0;

	__enable_irq();
	NVIC_EnableIRQ(PORTA_IRQn);
	led_action(ON, led5);
	led_action(ON, led6);
	led_action(OFF, led7);
	led_action(ON, led8);
	for(uint32_t j = 0; j < 10; )
	{
		++i;
		if(i > 200000)
		{
			++j;
			NVIC_SetPendingIRQ(PORTA_IRQn);
			i = 0;
		}
	}
	__disable_irq();
	NVIC_DisableIRQ(PORTA_IRQn);
	led_action(OFF, led5);
	led_action(OFF, led6);
	led_action(OFF, led7);
	led_action(OFF, led8);
}

/* Read version register from xcvr */
static void test_xcvr_version(void)
{
	uint8_t vers = 0xff;

	if(!xcvr_read_8bit_reg(xcvr_addrs.RegVersion, &vers))
	{
		error_spin_led(led5);
	}

	if(vers != 0x23)
	{
		error_spin_led(led6);
	}
}

/* Read version register from xcvr
 * Assume reset value
 */
static void test_xcvr_PaLevel(void)
{
	uint8_t vers = 0xff;

	if(!xcvr_read_8bit_reg(xcvr_addrs.RegPaLevel, &vers))
	{
		error_spin_led(led7);
	}

	if(vers != 0x9a)     // manual claims default is 0x9f
	{
		error_spin_led(led8);
	}
}

static void test_xcvr_RegDioMapping2(void)
{
	uint8_t val = 0xff;

	if(!xcvr_read_8bit_reg(xcvr_addrs.RegDioMapping2, &val))
	{
		error_spin_led(led7);
	}

	if(val != XCVR_CLK_DIV16)
	{
		error_spin_led(led8);
	}

}

/* Test outclock from SPI */
void test_xcvr_outclock(void)
{
	led_action(OFF, led5);
	led_action(OFF, led6);
	led_action(OFF, led7);
	led_action(OFF, led8);


	if(!xcvr_set_outclk_div(XCVR_CLK_DIV16))
	{
		error_spin_led(led8);
	}

	// CLOCKOUT should now be 2Mhz verify at Test Point

	led_action(OFF, led5);
	led_action(OFF, led6);
	led_action(OFF, led7);
	led_action(OFF, led8);
}

/* If we make it through the tests play a unique pattern of leds */
static void test_pass_led_pattern(void)
{
	uint16_t n = 0;
	char     c = 'x';
	bool     gotchar = false;
	uint32_t i = 0;
	printf("*I* Type a char to test get char\r\n");
	while(1)
	{
		n = num_uart0_rx_chars_avail();
		while(n > 0)
		{
			gotchar = uart0_getchar_intr(&c);
			if (gotchar)
			{
				if(c == '\r')
				{
					printf("\n");
				}
				printf("%c", c);
			}
			n = num_uart0_rx_chars_avail();
		}

		++i;
		if(i == 100000)
		{
			led_action(TOGGLE, led5);
		}
		if(i == 200000)
		{
			led_action(TOGGLE, led6);
		}
		if(i == 300000)
		{
			led_action(TOGGLE, led7);
		}
		if(i > 400000)
		{
			led_action(TOGGLE, led8);
			i = 0;
			printf("*");
		}
	}
}

static  void test_write_uart0_poll(char * str)
{
	volatile size_t len ;
	len  = strlen(str);
	uart_write_poll(&UART0, len, (uint8_t *)str);
}

static void initialize_uart0_poll(void)
{
	/* UART0 configuration */
	struct uart_config myUART =
	{
		/* transmit = PTA2 */
		.TX = {.port = &PORTA, .pin = 2,},
		/* receive = PTA1 */
		.RX = {.port = &PORTA, .pin = 1,},
		.baud = 115200,
	};
	uart_init_poll(&UART0, &myUART);
}

static void initialize_uart0_init(void)
{
	/* UART0 configuration */
	struct uart_config myUART =
	{
		/* transmit = PTA2 */
		.TX = {.port = &PORTA, .pin = 2,},
		/* receive = PTA1 */
		.RX = {.port = &PORTA, .pin = 1,},
		.baud = 115200,
	};
	uart0_init_intr(&myUART);
}

int main(void)
{
	/* Hello, is this thing on? */
	/* Default POR clocking, initialize GPIO, basic LED side effect. */
	enable_all_port_clocks();

	initialize_gpio();

	/* PORT ISR */
	test_porta_isr();

	/* SPI */
	// Initialize SPI0
	initialize_spi0(&spi0_config);

	test_xcvr_version();

	/* See if we can talk to the transceiver through SPI by dividing the clock */
	test_xcvr_outclock();
	// CLOCKOUT should now be 2Mhz verify at Test Point

	test_xcvr_version();

	test_xcvr_RegDioMapping2();

	// test_xcvr_PaLevel(); // register not consistent value and doesn't match POR from Ref Manual.

	/* CLOCKS */
	enable_pll_48();  // \todo clever way to check? beyond not crashing...

	/* UART */
	initialize_uart0_poll();

	test_write_uart0_poll("\r\n\n---\r\n");
	test_write_uart0_poll("---\n\n");
	test_write_uart0_poll("\r\nTest...Test...Test...\n");
	test_write_uart0_poll("\r\nUART0 Polling Mode...\n");

	initialize_uart0_init();

	uart0_writestr_intr("UART0 Interrupt Mode...\r\n");

	lgr_version(LGR_GITVERSION);
	printf("Built with version(Git hash):\t%s\r\n", LGR_GITVERSION);
	printf("Char 'c':\t%c\r\n", 'c');
	printf("Decimal 10:\t%d\r\n", 10);
	printf("Hex 10:\t\t0x%x\r\n", 10);
	printf("Bin 10:\t\t0b%b\r\n", 10);
	printf("\r\nHello\tTab\nnewline\ttab...Yay!\r\n");

	/* End of tests */
	printf("\r\nTests Passed\r\n");
	test_pass_led_pattern();  // test get chars here interactively

	return(-1);
}

