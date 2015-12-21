/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include "driverSPI0.h"

void spi0_init(void){
	/* select the proper mux setting on each pin involved in spi0 */
	PORTC.PCR[5] |= 0x200;
	PORTC.PCR[6] |= 0x200;
	PORTC.PCR[7] |= 0x200;
	PORTD.PCR[0] |= 0x200;
	PORTE.PCR[2] |= 0x100;
	PORTE.PCR[3] |= 0x100;

	/* configure SPI0 */
	SPI0.C1 = 0x52;		/* interrupt enable off, system enable on, tx interrupt enable off, spi module configured as master, CPOL=0, CPHA=0, SS OE on, data transfers start with MSB */
	SPI0.C2 = 0xD0;		/* match interrupt enable on, 16bit mode, tx dma enable off, master mode fault function enable on, bidirectional mode OE off, rx dma enable off, stop in wait mode off, spi pin control 0 off (meant for bidirectional pin configurations) */

	return;
}

void spi0_read(size_t len, uint16_t * buffer){

	/* dummy buffer for send portion of transaction */
  	uint16_t dummyBuffer[len] = {0x0};

	/* start transaction */
	spi_transaction(len, dummyBuffer, buffer);

}

void spi0_write(size_t len, uint16_t * buffer){

	/* dummy buffer for receive portion of transaction */
	uint16_t dummyBuffer[len];

	/* start transaction */
	spi_transaction(len, buffer, dummyBuffer);

}

void spi_transaction(size_t len, uint16_t * sendBuffer, uint16_t * recvBuffer){

	/* iterate through number of bytes for transaction */
	for(int i = 0; i < len; ++i){

		/* poll the transmit buffer empty flag */
		while(!(SPI0.S & (1 << 5)));

		/* extract the MSB and LSB */
		uint8_t MSB = (sendBuffer[i] >> 8) & 0xFF;
		uint8_t LSB = (sendBuffer[i]) & 0xFF;

		/* send em by writing to the data registers */
		SPI0.DH = MSB;
		SPI0.DL = LSB;

		/* poll the read buffer full flag */
		while(!(SPI0.S & (1 << 7)));

		/* grab data, concatenate into buffer */
		recvBuffer[i] = (SPI0.DH << 8) | SPI0.DL;
	}
}
