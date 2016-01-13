/*
	Generalized SPI driver for the Freescale MKW01.

	Programmed by William Harrington, Theo Hill
*/
#include "driverSPI0.h"

void spi_init(struct SPI_t * SPI, const struct spi_config * config){
	/* 	TODO: how do I figure out that this is the correct pin
		and what the proper value to write to the register is ?
	*/

	/* select desired pin functionality */
	config.SCK.port.PCR[config.SCK.pin] |= (config.SCK.alt << 8);
	config.SS.port.PCR[config.SS.pin] |= (config.SS.alt << 8);
	config.MOSI.port.PCR[config.MOSI.pin] |= (config.MOSI.alt << 8);
	config.MISO.port.PCR[config.MISO.pin] |= (config.MISO.alt << 8);

	/* apply SPI configuration */
	SPI->C1 = (5 << 4) | (config.CPOL << 3) | (config.CPHA << 2) | (1 << 1);
	SPI->C2 = (13 << 4);
}

void spi_read(struct SPI_t * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for send portion of transaction */
  	uint16_t dummyBuffer[len] = {0x0};

	/* start transaction */
	spi_transaction(SPI, len, dummyBuffer, buffer);

}

void spi_write(struct SPI_t * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for receive portion of transaction */
	uint16_t dummyBuffer[len];

	/* start transaction */
	spi_transaction(SPI, len, buffer, dummyBuffer);

}

void spi_transaction(struct SPI_t * SPI, size_t len, uint16_t * sendBuffer, uint16_t * recvBuffer){

	/* iterate through number of bytes for transaction */
	for(int i = 0; i < len; ++i){

		/* poll the transmit buffer empty flag */
		while(!(SPI->S & (1 << 5)));

		/* extract the MSB and LSB */
		uint8_t MSB = (sendBuffer[i] >> 8) & 0xFF;
		uint8_t LSB = (sendBuffer[i]) & 0xFF;

		/* send em by writing to the data registers */
		SPI->DH = MSB;
		SPI->DL = LSB;

		/* poll the read buffer full flag */
		while(!(SPI->S & (1 << 7)));

		/* grab data, concatenate into buffer */
		recvBuffer[i] = (SPI->DH << 8) | SPI->DL;
	}
}
