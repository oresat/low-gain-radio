/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include "kw0x.h"

/* initialization function */
void spi0_init(void);

/* read function */
void spi0_read(size_t len, uint16_t * buffer);

/* write function */
void spi0_write(size_t len, uint16_t * buffer);

/* SPI transaction frame */
void spi_transaction(size_t len, uint16_t * sendBuffer, uint16_t * recvBuffer);
