/*
	Generalized SPI driver for the Freescale MKW01.

	Programmed by William Harrington, Theo Hill
*/
//#include <assert.h>

#include "spi.h"

static const struct pin_assign PCS0 [] = {
	{.module=&SPI0, .pin={&PORTE, 16}, .alt=2},
	{.module=&SPI0, .pin={&PORTD, 0},  .alt=2},
	{.module=&SPI1, .pin={&PORTD, 4},  .alt=2},
	{}
};

static const struct pin_assign SCK [] = {
	{.module=&SPI0, .pin={&PORTE, 17}, .alt=2},
	{.module=&SPI0, .pin={&PORTC, 5},  .alt=2},
	{.module=&SPI1, .pin={&PORTD, 5},  .alt=2},
	{.module=&SPI1, .pin={&PORTE, 2},  .alt=2},
	{}
};

static const struct pin_assign MISO [] = {
	{.module=&SPI0, .pin={&PORTE, 18}, .alt=5},
	{.module=&SPI0, .pin={&PORTE, 19}, .alt=2},
	{.module=&SPI0, .pin={&PORTC, 7},  .alt=2},
	{.module=&SPI0, .pin={&PORTC, 6},  .alt=5},
	{.module=&SPI1, .pin={&PORTB, 17}, .alt=2},
	{.module=&SPI1, .pin={&PORTE, 3},  .alt=2},
	{.module=&SPI1, .pin={&PORTE, 1},  .alt=5},
	{.module=&SPI1, .pin={&PORTD, 7},  .alt=2},
	{.module=&SPI1, .pin={&PORTD, 6},  .alt=5},
	{}
};

static const struct pin_assign MOSI [] = {
	{.module=&SPI0, .pin={&PORTE, 18}, .alt=2},
	{.module=&SPI0, .pin={&PORTE, 19}, .alt=5},
	{.module=&SPI0, .pin={&PORTC, 7},  .alt=5},
	{.module=&SPI0, .pin={&PORTC, 6},  .alt=2},
	{.module=&SPI1, .pin={&PORTB, 17}, .alt=5},
	{.module=&SPI1, .pin={&PORTE, 3},  .alt=5},
	{.module=&SPI1, .pin={&PORTE, 1},  .alt=2},
	{.module=&SPI1, .pin={&PORTD, 7},  .alt=5},
	{.module=&SPI1, .pin={&PORTD, 6},  .alt=2},
	{}
};

#define ENABLE_IN_MASTER (5 << 4)
#define SS_OE (1 << 1)
#define BITMODE16_AND_MASTER_MODE_FAULT_EN (13 << 4)

void spi_init(volatile struct spi * SPI, const struct spi_config * config){
	/* 	TODO: add clock configuration in here
	*/

	/* select desired pin functionality */
	set_pin_alt(SCK,  SPI, &config->SCK);
	set_pin_alt(PCS0, SPI, &config->SS);
	set_pin_alt(MOSI, SPI, &config->MOSI);
	set_pin_alt(MISO, SPI, &config->MISO);

	/* apply SPI configuration */
	SPI->C1 = ENABLE_IN_MASTER | (config->CPOL << 3) | (config->CPHA << 2) | SS_OE;
	SPI->C2 = BITMODE16_AND_MASTER_MODE_FAULT_EN;
}

uint16_t mask_spi_addr(uint8_t addr, uint8_t write, uint8_t byteToWrite){
	if(write){
		/* masking for write transaction */
		uint16_t result = ((addr | 0x80) << 8) | byteToWrite;
		return result;
	}

	/* masking for read transaction */
     	byteToWrite = 0x00;
	uint8_t result = ((addr & 0x7F) << 8) | byteToWrite;
	return result;
}

void spi_read_16(volatile struct spi * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for send portion of transaction */
	uint16_t dummyBuffer[len];

	/* start transaction */
	spi_transaction(SPI, len, dummyBuffer, buffer);

}

void spi_write_16(volatile struct spi * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for receive portion of transaction */
	uint16_t dummyBuffer[len];

	/* start transaction */
	spi_transaction(SPI, len, buffer, dummyBuffer);

}

void spi_transaction_16(volatile struct spi * SPI, size_t len, uint16_t * send, uint16_t * recv){
 	if(!len) return;

	/* iterate through number of bytes for transaction */
	for(unsigned int i = 0; i < len; ++i){

		/* poll the transmit buffer empty flag */
		while(!(SPI->S & (1 << 5)));

		/* extract the MSB and LSB */
		uint8_t MSB = (send[i] >> 8) & 0xFF;
		uint8_t LSB = (send[i]) & 0xFF;

		/* send em by writing to the data registers */
		SPI->DH = MSB;
		SPI->DL = LSB;

		/* poll the read buffer full flag */
		while(!(SPI->S & (1 << 7)));

		/* grab data, concatenate into buffer */
		recv[i] = (SPI->DH << 8) | SPI->DL;
	}
}
