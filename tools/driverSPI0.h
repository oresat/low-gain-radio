/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include "kw0x.h"

void spi0_init(void);	/* initialization function */
void spi0_read(void);	/* read function */
void spi0_write(void);	/* write function */
