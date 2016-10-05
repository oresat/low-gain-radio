/*!
 * \file    spi.h
 * \brief   SPI API
 *
 * \addtogroup spi
 * @{
 */

/*! 
 * \brief    SPI driver for the Freescale MKW01 internal SPI module (aka SPI0).
 *     This module is special because it is solely dedicated for communicating
 *     with the integrated transceiver which isn't really integrated..
 *
 *     Programmed by William Harrington, Theo Hill
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "port.h"

extern bool spi0_initialized ;

typedef enum spi_mode { EIGHTBIT=0, SIXTEENBIT=1 } 					spi_mode_width;
typedef enum spi_cpol { ACTIVE_HIGH=0, ACTIVE_LOW=1 } 				spi_cpol_polarity;
typedef enum spi_cpha { FIRST_EDGE_MIDDLE=0, FIRST_EDGE_START=1 } 	spi_cpha_phase;

struct spi_config
{
	struct pin              SCK; /* clock */
	struct pin              SS; /* slave select */
	struct pin              MOSI; /* master out, slave in */
	struct pin              MISO; /* master in, slave out */
	spi_cpol_polarity       CPOL; /* clock polarity */
	spi_cpha_phase          CPHA; /* clock phase */
	spi_mode_width          SPIMODE;
};

void initialize_spi0(struct spi_config * cfg);

/* initialization function */
// void spi_init(volatile struct spi * SPI, const struct spi_config * config);
bool spi0_read_8_poll(uint8_t addr, uint8_t * buffer);
bool spi0_write_8_poll(uint8_t addr, uint8_t payload);


/* read function */
// void spi_read_16(volatile struct spi * SPI, size_t len, uint16_t * buffer);
// void spi_read_8(volatile struct spi * SPI, size_t len, uint8_t * buffer);
// #define spi_read(SPI, len, buffer) _Generic((buffer), \
        // uint16_t *:spi_read_16, \
        // uint8_t *:spi_read_8 \
                                           // )(SPI, len, buffer)

/* write function */
// void spi_write_16(volatile struct spi * SPI, size_t len, uint16_t * buffer);
// void spi_write_8(volatile struct spi * SPI, size_t len, uint8_t * buffer);
// #define spi_write(SPI, len, buffer) _Generic((buffer), \
        // uint16_t *:spi_write_16, \
        // uint8_t *:spi_write_8 \
                                            // )(SPI, len, buffer)

/* SPI transaction frame */
//void spi0_transaction_8(size_t len, uint8_t * address, uint8_t * send, uint8_t * recv);
// void spi_transaction_16(volatile struct spi * SPI, size_t len, uint16_t * send, uint16_t * recv);
// void spi_transaction_8(volatile struct spi * SPI, size_t len, uint8_t * send, uint8_t * recv);
// #define spi_transaction(SPI, len, send, recv) _Generic((send), \
        // uint16_t *:spi_transaction_16, \
        // uint8_t *:spi_transaction_8 \
                                                      // )(SPI, len, send, recv)

#endif
/*! @} */

