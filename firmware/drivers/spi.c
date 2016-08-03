/*!
* \file    spi.c
* \brief   SPI API
*
* \defgroup spi
* \brief    Generalized SPI driver for the Freescale MKW01.
* @{
*/

/*
 *     Generalized SPI driver for the Freescale MKW01.
 *
 *     Original programmed by William Harrington, Theo Hill
 */

#include <stdbool.h>

#include "v1_2.h"

#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"
#include "clocks.h"
#include "spi.h"

bool spi0_initialized = false;

static const struct pin_assign PCS0 [] =
{
	{.module = &SPI0, .pin = {&PORTE, 16}, .alt = 2},
	{.module = &SPI0, .pin = {&PORTD, 0},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTD, 4},  .alt = 2},
	{}
};

static const struct pin_assign SCK [] =
{
	{.module = &SPI0, .pin = {&PORTE, 17}, .alt = 2},
	{.module = &SPI0, .pin = {&PORTC, 5},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTD, 5},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTE, 2},  .alt = 2},
	{}
};

static const struct pin_assign MISO [] =
{
	{.module = &SPI0, .pin = {&PORTE, 18}, .alt = 5},
	{.module = &SPI0, .pin = {&PORTE, 19}, .alt = 2},
	{.module = &SPI0, .pin = {&PORTC, 7},  .alt = 2},
	{.module = &SPI0, .pin = {&PORTC, 6},  .alt = 5},
	{.module = &SPI1, .pin = {&PORTB, 17}, .alt = 2},
	{.module = &SPI1, .pin = {&PORTE, 3},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTE, 1},  .alt = 5},
	{.module = &SPI1, .pin = {&PORTD, 7},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTD, 6},  .alt = 5},
	{}
};

static const struct pin_assign MOSI [] =
{
	{.module = &SPI0, .pin = {&PORTE, 18}, .alt = 2},
	{.module = &SPI0, .pin = {&PORTE, 19}, .alt = 5},
	{.module = &SPI0, .pin = {&PORTC, 7},  .alt = 5},
	{.module = &SPI0, .pin = {&PORTC, 6},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTB, 17}, .alt = 5},
	{.module = &SPI1, .pin = {&PORTE, 3},  .alt = 5},
	{.module = &SPI1, .pin = {&PORTE, 1},  .alt = 2},
	{.module = &SPI1, .pin = {&PORTD, 7},  .alt = 5},
	{.module = &SPI1, .pin = {&PORTD, 6},  .alt = 2},
	{}
};

#define     SPI_C1_SSOE             (0b1 << 1)
#define     SPI_C1_CPOL_LOW         (0b1 << 3)
#define     SPI_C1_CPHA_START       (0b1 << 2)
#define     SPI_C1_MASTER_EN        (0b1 << 4)
#define     SPI_C1_SPTIE            (0b1 << 5)
#define     SPI_C1_SPE              (0b1 << 6)
#define     SPI_C1_SPIE             (0b1 << 7)

#define     SPI_C2_MODFEN           (0b1 << 4)
#define     SPI_C2_SPIMODE          (0b1 << 6)

#define     SPI_S_SPTEF             (0b1 << 5)
#define     SPI_S_SPRF              (0b1 << 7)

/*
 * SPI0 is directly connected to the transceiver on this SiP
 *
 * SPI0 is clocked by BUS CLOCK, SPI1 is clocked by SYSTEM CLOCK
 */
void initialize_spi0(struct spi_config * cfg)
{
	set_pin_alt(SCK,  &SPI0, &cfg->SCK);
	set_pin_alt(MOSI, &SPI0, &cfg->MOSI);
	set_pin_alt(MISO, &SPI0, &cfg->MISO);

	/*
	 * 8.3.3 MKW0xxx SPI Transaction Timing
	 * As defined in Section 8.3.2, the SPI transaction protocol is composed of two or more bytes per frame.
	 * Although the transceiver is capable of a continuous bit transfer for the entire frame, the MCU SPI port only
	 * transfers payload in bursts of 8 bits. There are implications in the way the MCU SPI is programmed and used:
	 * • The MCU SS signal -
	 * — Cannot be programmed for SPI module master mode driven operation
	 * — Port signal PTE3 must be enabled and programmed as a GPIO output to provide the required
	 * SS signal timing
	 * • The transaction bytes are sent as a bursts as allowed by the MCU 8-bit SPI module.
	 * Because the MCU is embedded in the SiP and the transceiver only supports the one clock format, the MCU
	 */

	/* We need to control the slave select manually with PTD0 set as GPIO
	 * to perform SPI operations longer than one byte
	 */
	// Can't do this for SPI0 on this chip: set_pin_alt(PCS0, SPI, &cfg->SS);

	PORTD.PCR[0] |= ALT1;       // Enable PTD0 as a GPIO
	PORTD.PCR[0] |= 0b11;       // Enable pullup
	GPIOD.PDDR   |= PTD0;       // Set PTD0 payload direction to output
	GPIOD.PTOR   =  PTD0;       // Set the output signal to high

	/* \todo Thu 21 July 2016 17:16:11 (PDT) finish this and rethink it after PTE2 reconnection
	PORTE.PCR[2] |= ALT1;
	PORTE.PCR[3] |= ALT1;
	GPIOE.PDDR   &= ~(PTE2 | PTE3); // set to input
	*/

	enable_spi0_clock();

	{
		// baud rate
		/*
		 * Section 8.2 transceiver reference manual
		 *    Programmable SPI clock rate; maximum transfer rate is 10 MHz as determined by the transceiver
		 */
		// SPI0.BR = 0x22; // 12 Mhz Bus Clock -> 500khz SPI0
		SPI0.BR = 0x0;     // 12 Mhz Bus Clock -> 6Mhz SPI0
	}

	{
		// C1
		uint8_t spi_c1  = 0x0;

		spi_c1  |= SPI_C1_SSOE | SPI_C1_MASTER_EN | SPI_C1_SPTIE | SPI_C1_SPE | SPI_C1_SPIE ;
		if(cfg->CPOL == ACTIVE_LOW)
		{
			spi_c1 |= SPI_C1_CPOL_LOW;
		}
		if(cfg->CPHA == FIRST_EDGE_START)
		{
			spi_c1 |= SPI_C1_CPHA_START;
		}
		SPI0.C1 = spi_c1;
	}

	{
		// C2
		uint8_t spi_c2  = 0x0;

		spi_c2      |=  SPI_C2_MODFEN;
		if(cfg->SPIMODE == SIXTEENBIT)
		{
			spi_c2 |= SPI_C2_SPIMODE;
		}
		else
		{
			spi_c2 &= ~(SPI_C2_SPIMODE);
		}

		SPI0.C2     =   spi_c2;
	}
	spi0_initialized = true;
}

static inline void _spi_set_8bit(void)
{
	SPI0.C2 &= ~(SPI_C2_SPIMODE);
}

static inline void _spi_set_16bit(void)
{
	SPI0.C2 |= SPI_C2_SPIMODE;
}

static inline bool _spi0_rx_buff_full(void)
{
	return((SPI0.S & SPI_S_SPRF) != 0);
}

static inline bool _spi0_tx_buff_full(void)
{
	return((SPI0.S & SPI_S_SPTEF) == 0);
}

bool _spi0_8_poll(uint8_t addr, uint8_t payload, uint8_t * buffer)
{
	if(buffer == NULL)
	{
		return false;
	}

	/* Will clear FIFO and Reset the SPI0.S register. any current transaction will be aborted */
	_spi_set_8bit();

	GPIOD.PCOR |= PTD0;   // _NSS low

	while(_spi0_tx_buff_full());

	SPI0.DL = addr;

	while(_spi0_tx_buff_full());
	while(!(_spi0_rx_buff_full()));

	*buffer = SPI0.DL;

	while(_spi0_tx_buff_full());

	SPI0.DL = payload;

	while(_spi0_tx_buff_full());

	while(!(_spi0_rx_buff_full()));

	*buffer = SPI0.DL;

	GPIOD.PSOR |= PTD0;   // _NSS high

	return true;
}

bool spi0_read_8_poll(uint8_t addr, uint8_t * buffer)
{
	uint8_t payload = 0x0;
	return _spi0_8_poll(addr, payload, buffer);
}

bool spi0_write_8_poll(uint8_t addr, uint8_t payload)
{
	uint8_t buffer = 0xff;
	/* Mask bit 7 of write address */
	addr = addr | 0x80;
	return _spi0_8_poll(addr, payload, &buffer);
}


/*! @} */
