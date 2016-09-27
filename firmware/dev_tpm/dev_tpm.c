/* \file dev_tpm.c
 * Low Gain Radio firmware
 * TPM Development
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
#include "uart.h"
#include "spi.h"
#include "xcvr.h"
#include "ringbuffer.h"
#include "em-printf.h"

#include "tpm.h"
#include "dev_tpm.h"

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


/* FYI: This is the A4 wake-up pin */
/* POR state: NMI, pullup, interrupt enabled
 */
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

static void initialize_uart0(void)
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

void main_loop(void)
{
	led_action(OFF, led5);
	led_action(OFF, led6);
	led_action(OFF, led7);
	led_action(OFF, led8);

	__enable_irq();

	// tpm0_init(false);
	tpm0_init(true);
	tpm0_test_loop();
}

int main(void)
{
	after_POR_pause();

	enable_all_port_clocks();

	initialize_gpio();

	initialize_spi0(&spi0_config);

	uint8_t vers = 0xff;

	if(!xcvr_read_8bit_reg(xcvr_addrs.RegVersion, &vers))
	{
		error_spin_led(led5);
	}

	if(vers != 0x23)
	{
		error_spin_led(led7);
	}

	if(!xcvr_set_outclk_div(XCVR_CLK_DIV16))
	{
		error_spin_led(led6);
	}

	enable_pll_48();

	/* UART */
	initialize_uart0();

	printf("\r\n%s\tTPM Driver Development...\r\n", __FILE__);
	lgr_version(LGR_GITVERSION);
	printf("Built with version(Git hash):\t%s\r\n", LGR_GITVERSION);
	printf("GCC Version: %d.%d.%d\r\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);

	main_loop();

	return(-1);
}

