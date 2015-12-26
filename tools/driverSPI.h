/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include "kw0x.h"

/* struct for pin selection */
struct pin {
	struct PORT * port; /* port module */
	uint8_t pin; /* pin on port module */
	uint8_t alt; /* mux control value */
};

/* struct for specifying config */
struct spi_config {
	struct SPI_t SPI; /* SPI module */
	struct pin SCK; /* clock */
	struct pin SS; /* slave select */
	struct pin MOSI; /* master out, slave in */
	struct pin MISO; /* master in, slave out */
	bool CPOL; /* clock polarity */
	bool CPHA; /* clock phase */
};

/* initialization function */
void spi_init(struct spi_config config);

/* read function */
void spi_read(struct SPI_t SPI, size_t len, uint16_t * buffer);

/* write function */
void spi_write(struct SPI_t SPI, size_t len, uint16_t * buffer);

/* SPI transaction frame */
void spi_transaction(struct SPI_t SPI, size_t len, uint16_t * sendBuffer, uint16_t * recvBuffer);
