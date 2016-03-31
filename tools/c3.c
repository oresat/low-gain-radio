/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "drivers/uart.h"
#include "drivers/transceiver.h"
#include "drivers/spi.h"

#if 1
void initialize_spi(void){
	/* enable clock for SPI modules */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* configuration for SPI0, see Chapter 8.1 */
	struct spi_config myConfig = {
		/* Serial Clock */
		.SCK = {.port=&PORTC, .pin=5,},

		/* Slave Select */
		.SS = {.port=&PORTD, .pin=0,},

		/* Master out slave in */
		.MOSI = {.port=&PORTC, .pin=6,},

		/* Master in slave out */
		.MISO = {.port=&PORTC, .pin=7,},

		/* Polarity */
		.CPOL = 0,

		/* Phase */
		.CPHA = 0,

		.SPIMODE = 1,
	};

	/* initialize SPI0 */
	spi_init(&SPI0, &myConfig);

	/* send to transceiver to get 32MHz clock signal on PTA18 */
	uint16_t DioMapping2Cfg = (transceiver.RegDioMapping2 | 0x80) << 8;
	uint16_t bleh = 0;
	//spi_transaction_16(&SPI0, 1, &DioMapping2Cfg, &bleh);
	spi_transaction(&SPI0, 1, &DioMapping2Cfg, &bleh);

	//myConfig.SPIMODE = 0;
	//spi_init(&SPI0, &myConfig);

	/* disable SPI module clock because theo said it would get mad if I didn't! */
	SIM.SCGC4 &= 0xFF3FFFFF;

	/* disable port module clock because theo said it would get mad if I didn't! */
	SIM.SCGC5 &= 0xFFFFC1FF;

}

void initialize_clock(void){
	/* simple clock configuration that involves initializing the SPI so we can get the external clock reference from the transceiver */

	/* set PLL external reference divider (PRDIV0) to 16, this will give us 2 MHz */
	MCG.C5 = 0xF;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 |= 0x40;

	/* select PLL instead of FLL */
	MCG.C6 |= 0x40;

	/* wait for PLL lock */
	while(!(MCG.S & (1 << 6)));

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	*/
	MCG.C2 |= 0x14;

	/* enable external oscillator */
	OSC0.CR = 0x80;

	/* now enable clock for SPI modules, AGAIN! */
	SIM.SCGC4 |= 0xC00000;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* enable clock for TPM, RTC modules */
	SIM.SCGC6 |= 0x27000000;

	return;
}
#endif
void initialize_gpio(void){
	/* procedure for getting the GPIO going on pins PTB1, PTB2, PTB17 */

	/* modify mux to select alt 1 functionality
	   for PTB1, PTB2, PTB17.
	   Alt 1 functionality is just GPIO
	*/
	PORTB.PCR[1] |= 0x100;
	PORTB.PCR[2] |= 0x100;
	PORTB.PCR[17] |= 0x100;

	/* set data direction as output */
	GPIOB.PDDR |= 0x20006;

	/* turn all LEDs of by pulling pins high */
	GPIOB.PTOR = 0x20006;

	return;
}
#if 0
void initialize_uart(void){
	/* UART0 configuration */
	struct uart_config myUART = {
		/* pin for transmit = PTA1 */
		.TX = {.port=&PORTA, .pin=1,},

		/* pin for receive = PTA2 */
		.RX = {.port=&PORTA, .pin=2,},

		/* baud rate */
		.baud = 115200,
	};
	uart0_init(&UART0, &myUART);
}

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

void test_spi_8(void){
	spi_init_8(&SPI0);

	initialize_gpio();

	uint8_t write_data[3] = {0x12,0x34,0x56};
	uint8_t read_data[3];
	/*this is the first part of the AES key, we wont break anything by writing and reading there*/
	uint8_t test_address = 0x3E; 
	trans_read_register(&test_address, read_data, 3);
	if (!read_data[0] && !read_data[1] && !read_data[2]){
		GPIOB.PTOR = 0x00004;
	}
	trans_write_register(&test_address, write_data, 3);
	trans_read_register(&test_address, read_data, 3);
	if (read_data[0] == 0x12 && read_data[1] == 0x34 && read_data[2] == 0x56){
		GPIOB.PTOR = 0x00004;
	}
}

int main(void) {

	/* delay loop for POR, transceiver not available for 10ms */
	for(uint32_t i = 0; i < 1000000; ++i);

	/* call initialization procedures */
	initialize_spi();
	initialize_clock();
	initialize_gpio();

	//initialize_uart();
	//initialize_tpm();
   	//asm volatile ("cpsie   i");

	/* this function is in transceiver.c if you want more details */
	configure_transceiver();

	uint16_t FIFObyte = (transceiver.RegFifo | 0x80) << 8 | 0xFF;
	//uint8_t FIFObytes[] = {transceiver.RegFifo | 0x80, 0xFF};
	uint16_t bleh = 0;
	//uint8_t bleh2 = 0;

	while(1) {
		for(uint32_t i = 0; i < 1000000; ++i);

		spi_transaction(&SPI0, 1, &FIFObyte, &bleh);
		//spi_transaction_16(&SPI0, 1, &FIFObyte, &bleh);
		//spi_transaction_8(&SPI0, 2, FIFObytes, &bleh2);

	       	/* toggle LED connected to PTB2 */
		GPIOB.PTOR = 0x00004;
	}
	return 0;
}
