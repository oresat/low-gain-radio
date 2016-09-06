/* \file dev.c

	Firmware for KW0x breakout boards

	Programmed by William Harrington
 */

#include <string.h>
#include "v1_1.h"
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
#include "dev.h"
#include "xcvr.h"

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
	led_action(TOGGLE, blue);
}

void isr_porta(void)
{
	led_action(TOGGLE, blue);
};

void isr_portcd(void)
{
	led_action(TOGGLE, blue);
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

void main_loop(void)
{
	if(USE_XCVR_TX_MODE){
		if(!configure_transceiver(ModeTX, PAOutputCfg(PA0, 0x1F))) error_spin_led(red);
	        changeMode(ModeStdby);
        }
	else if(USE_XCVR_RX_MODE){
		if(!configure_transceiver(ModeRX, PAOutputCfg(PA0, 0x1F))) error_spin_led(red);
        }

	uint8_t IrqFlags[2] = {0, 0};
	uint8_t OldFlags[2] = {0xFF, 0xFF};
	uint8_t rxbyte;
        uint8_t txbytes[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD};


	__enable_irq();
	// NVIC_EnableIRQ(PORTA_IRQn);

	/* Not yet Thu 21 July 2016 17:24:45 (PDT) because issues  with PTE2*/
	// NVIC_EnableIRQ(SPI0_IRQn);

	volatile size_t len ;
	char teststr[24] = "\r\nDevelopment...\r\n";
	len  = strlen(teststr);
	uint32_t i = 0;
	uart_write_poll(&UART0, len, (uint8_t *)teststr);

	char n;
	char ch[20];
	while(1)
	{
		++i;

		if(USE_XCVR_RX_MODE){
			// check transceiver irq flags
			xcvr_read_8bit_reg_burst(xcvr_addrs.RegIrqFlags1, IrqFlags, 2);

			// packet received, spit it out on UART0
			if(IrqFlags[1] & PayloadReady){
				led_action(TOGGLE, green);

				// read until fifo empty
                        	while(IrqFlags[1] & FifoNotEmpty) {
					xcvr_read_8bit_reg(xcvr_addrs.RegFifo, &rxbyte);
					uint8_t data[3] = {0, 0, ' '};
					toHex(data, rxbyte);
					uart_write_poll(&UART0, sizeof(data), data);
					xcvr_read_8bit_reg(xcvr_addrs.RegIrqFlags2, &IrqFlags[1]);
                        	}
				led_action(TOGGLE, green);
			}
                }

		if(i > 3000000)
		{
			if(USE_XCVR_TX_MODE){
				for(uint8_t j = 0; j < PACKET_LENGTH; j++){
	                                xcvr_write_8bit_reg(xcvr_addrs.RegFifo, *(txbytes + j));
				}
                	}
			if(uart0_intr_flag_g)
			{
				uart0_intr_flag_g = false;
			}
			led_action(TOGGLE, red);
			NVIC_SetPendingIRQ(PORTA_IRQn);
			if(!uart0_writestr_intr("NUM CHARS: "))
			{
				uart_write_poll(&UART0, len,(uint8_t *) " ouch\n");
			}

			n= num_uart0_rx_chars_avail();
			util_itoa(n, ch, 10);
			if(!uart0_writestr_intr( ch))
			{
				uart_write_poll(&UART0, len,(uint8_t *) " OUCH\n");
			}
			if(!uart0_writestr_intr( "\r\n"))
			{
				uart_write_poll(&UART0, len,(uint8_t *) " OUCH\n");
			}
			printf("Char 'c':\t%c\r\n", 'c');
			printf("Decimal 10:\t%d\r\n", 10);
			printf("Hex 10:\t\t0x%x\r\n", 10);
			printf("Bin 10:\t\t0b%b\r\n", 10);
			printf("\r\nHello\tTab\nnewline\ttab...Yay!\r\n");
			// uart0_writechar_intr('x');
			// uart0_writechar_intr(' ');
			i = 0;
		}
	}
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
		error_spin_led(red);
	}

	if(vers != 0x23)
	{
		error_spin_led(red);
	}

	if(!xcvr_set_outclk_div(XCVR_CLK_DIV16))
	{
		error_spin_led(red);
	}

	enable_pll_48();

	/* UART */
	// initialize_uart0_poll();
	initialize_uart0_init();

	main_loop();

	return(-1);
}

