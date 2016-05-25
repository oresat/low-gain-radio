/*
	Low Gain Radio firmware

	Programmed by William Harrington
*/
#include "drivers/uart.h"
#include "drivers/transceiver.h"
#include "drivers/spi.h"

/* System clock gating control */
#define SCGC_SPI1_CLK (1 << 23)
#define SCGC_SPI0_CLK (1 << 22)
#define SCGC_SPI_CLK_OFF 0xFF3FFFFF
#define SCGC_PORTA_CLK (1 << 9)
#define SCGC_PORTB_CLK (1 << 10)
#define SCGC_PORTC_CLK (1 << 11)
#define SCGC_PORTD_CLK (1 << 12)
#define SCGC_PORTE_CLK (1 << 13)
#define SCGC_PORTAE_CLK (31 << 9)
#define SCGC_PORTAE_CLK_OFF 0xFFFFC1FF

/* Reference clock control */
#define CLK_DIVIDE_0 0x0
#define CLK_DIVIDE_16 (1 << 2)

#if 1
void initialize_spi(void){
	/* enable clock for SPI modules */
	SIM.SCGC4 |= SCGC_SPI1_CLK | SCGC_SPI0_CLK;

	/* enable clock for all ports */
	SIM.SCGC5 |= SCGC_PORTAE_CLK;

	/* The transceiver requires a specific SPI configuration*/
	initialize_trans_spi(&SPI0);

	/* Send to transceiver to divide clock signal on PTA18 */
	//uint8_t RegDioMapping2Cfg = CLK_DIVIDE_0;
        uint8_t RegDioMapping2Cfg = CLK_DIVIDE_16;
	trans_write_register(transceiver.RegDioMapping2, &RegDioMapping2Cfg, 1);

	/* disable the clocks we enabled for this as we are going to mess with the clock settings now */
	SIM.SCGC4 &= SCGC_SPI_CLK_OFF;
	SIM.SCGC5 &= SCGC_PORTAE_CLK_OFF;
}

/* PLL External Reference Divider values in MCG.C5 */
#define PRDIV0_0 0x0
#define PRDIV0_16 0xF

/* PLL Clock Enable bit in MCG.C5 */
#define PLLCLKEN (1 << 6)

/* PLL Select in MCG.C6 */
#define PLLS (1 << 6)

/* PLL VCO Divide Factor */
#define VDIV0_24 0x0

/* PLL Lock Bit in MCG.S */
#define LOCK0 (1 << 6)

/* Frequency range select encoding in MCG.C2 */
#define RANGE0_HF (1 << 4)
#define RANGE0_VHF (1 << 5)

/* External Reference Select in MCG.C2 */
#define EREFS0 (1 << 2)

/* External Referance Enable bit in OSC0.CR */
#define ERCLKEN (1 << 7)

void initialize_clock(void){
	/* simple clock configuration that involves initializing the SPI so we can get the external clock reference from the transceiver */

	/* set PLL external reference divider (PRDIV0) to 16, this will give us 2 MHz */
	//MCG.C5 = PRDIV0_16;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 |= PLLCLKEN;

	/* select PLL instead of FLL, multiply signal by 24 to get 48MHz */
	MCG.C6 |= (1 << 6) | VDIV0_24;

	/* wait for PLL lock */
	while(!(MCG.S & LOCK0));

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	*/
	MCG.C2 |= RANGE0_HF | EREFS0;

	/* enable external oscillator */
	OSC0.CR = ERCLKEN;

	/* now enable clock for SPI modules, AGAIN! */
	SIM.SCGC4 |= SCGC_SPI1_CLK | SCGC_SPI0_CLK;

	/* enable clock for all ports */
	SIM.SCGC5 |= SCGC_PORTAE_CLK;

	/* enable clock for TPM, RTC modules */
	//SIM.SCGC6 |= 0x27000000;

	return;
}

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

	/* turn all LEDs of by pulling pins high */
	//GPIOC.PTOR = PTC4 | PTC3 | PTC2 | PTC1;

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

	/* delay loop for POR, transceiver not available for 10ms */
	for(uint32_t i = 0; i < 1000000; ++i);

	/* call initialization procedures */
	initialize_spi();
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

		/* memcpy is causing crash here */
		//trans_write_register(transceiver.RegFifo, &alive, 1);
		//trans_write_register(transceiver.RegFifo, &txbyte, 1);

		for(uint32_t i = 0; i < 1000000; ++i);

	       	/* toggle LED connected to PTB2 */
		GPIOC.PTOR = PTC1;
	}
	return 0;
}
#endif
