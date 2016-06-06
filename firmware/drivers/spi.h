/*
	SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
	This module is special because it is solely dedicated for communicating
	with the integrated transceiver which isn't really integrated..

	Programmed by William Harrington, Theo Hill
*/
#include <stdbool.h>
#include <stdint.h>
#include "port.h"

#ifndef _SPI_H_
#define _SPI_H_
/* struct for specifying config */
struct spi_config {
	struct pin SCK; /* clock */
	struct pin SS; /* slave select */
	struct pin MOSI; /* master out, slave in */
	struct pin MISO; /* master in, slave out */
	bool CPOL; /* clock polarity */
	bool CPHA; /* clock phase */
	bool SPIMODE;
};

/* initialization function */
void spi_init(volatile struct spi * SPI, const struct spi_config * config);
void spi_init_8(volatile struct spi * SPI, const struct spi_config * config);


/* read function */
void spi_read_16(volatile struct spi * SPI, size_t len, uint16_t * buffer);
void spi_read_8(volatile struct spi * SPI, size_t len, uint8_t * buffer);
#define spi_read(SPI, len, buffer) _Generic((buffer), \
		uint16_t *:spi_read_16, \
		uint8_t *:spi_read_8 \
		)(SPI, len, buffer)

/* write function */
void spi_write_16(volatile struct spi * SPI, size_t len, uint16_t * buffer);
void spi_write_8(volatile struct spi * SPI, size_t len, uint8_t * buffer);
#define spi_write(SPI, len, buffer) _Generic((buffer), \
		uint16_t *:spi_write_16, \
		uint8_t *:spi_write_8 \
		)(SPI, len, buffer)

/* SPI transaction frame */
//void spi0_transaction_8(size_t len, uint8_t * address, uint8_t * send, uint8_t * recv);
void spi_transaction_16(volatile struct spi * SPI, size_t len, uint16_t * send, uint16_t * recv);
void spi_transaction_8(volatile struct spi * SPI, size_t len, uint8_t * send, uint8_t * recv);
#define spi_transaction(SPI, len, send, recv) _Generic((send), \
		uint16_t *:spi_transaction_16, \
		uint8_t *:spi_transaction_8 \
		)(SPI, len, send, recv)

#endif
