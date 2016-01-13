/*
	Generalized SPI driver for the Freescale MKW01.

	Programmed by William Harrington, Theo Hill
*/
#include "driverSPI.h"



struct pin_assign {
	struct spi * spi;
	struct pin;
	int alt;
}

static const struct pin_assign PCS0 [] = {
	{spi=&SPI0, .pin={PORTE, 16}, .alt=2},
	{spi=&SPI0, .pin={PORTD, 0},  .alt=2},
	{spi=&SPI1, .pin={PORTD, 4},  .alt=2},
	{}
}

static const struct pin_assign SCK [] = {
	{spi=&SPI0, .pin={PORTE, 17}, .alt=2},
	{spi=&SPI0, .pin={PORTC, 5},  .alt=2},
	{spi=&SPI1, .pin={PORTD, 5},  .alt=2},
	{spi=&SPI1, .pin={PORTE, 2},  .alt=2},
	{}
}

static const struct pin_assign MISO [] = {
	{spi=&SPI0, .pin={PORTE, 18}, .alt=5},
	{spi=&SPI0, .pin={PORTE, 19}, .alt=2},
	{spi=&SPI0, .pin={PORTC, 7},  .alt=2},
	{spi=&SPI0, .pin={PORTC, 6},  .alt=5},
	{spi=&SPI1, .pin={PORTB, 17}, .alt=2},
	{spi=&SPI1, .pin={PORTE, 3},  .alt=2},
	{spi=&SPI1, .pin={PORTE, 1},  .alt=5},
	{spi=&SPI1, .pin={PORTD, 7},  .alt=2},
	{spi=&SPI1, .pin={PORTD, 6},  .alt=5},
	{}
}

static const struct pin_assign MOSI [] = {
	{spi=&SPI0, .pin={PORTE, 18}, .alt=2},
	{spi=&SPI0, .pin={PORTE, 19}, .alt=5},
	{spi=&SPI0, .pin={PORTC, 7},  .alt=5},
	{spi=&SPI0, .pin={PORTC, 6},  .alt=2},
	{spi=&SPI1, .pin={PORTB, 17}, .alt=5},
	{spi=&SPI1, .pin={PORTE, 3},  .alt=5},
	{spi=&SPI1, .pin={PORTE, 1},  .alt=2},
	{spi=&SPI1, .pin={PORTD, 7},  .alt=5},
	{spi=&SPI1, .pin={PORTD, 6},  .alt=2},
	{}
}


static void set_pin_alt(const struct pin_assign list[], struct spi * SPI, struct * pin) {
	for(int i = 0, list[i].spi != NULL, ++i) {
		if(SPI != list[i].spi)
			continue;
		if(pin->port != list[i].pin.port)
			continue;
		if(pin->pin != list[i].pin.pin)
			continue;

		pin->port.PCR[pin->pin] |= list[i].alt << 8;
		return;
	}
	assert(0);
}

void spi_init(struct spi * SPI, const struct spi_config * config){
	/* 	TODO: how do I figure out that this is the correct pin
		and what the proper value to write to the register is ?
	*/

	/* select desired pin functionality */
	set_pin_alt(SCK,  SPI, config->SCK);
	set_pin_alt(PCS0, SPI, config->SS);
	set_pin_alt(MOSI, SPI, config->MOSI);
	set_pin_alt(MISO, SPI, config->MISO);

	/* apply SPI configuration */
	SPI->C1 = (5 << 4) | (config.CPOL << 3) | (config.CPHA << 2) | (1 << 1);
	SPI->C2 = (13 << 4);
}

void spi_read(struct spi * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for send portion of transaction */
  	uint16_t dummyBuffer[len] = {0x0};

	/* start transaction */
	spi_transaction(SPI, len, dummyBuffer, buffer);

}

void spi_write(struct spi * SPI, size_t len, uint16_t * buffer){

	/* dummy buffer for receive portion of transaction */
	uint16_t dummyBuffer[len];

	/* start transaction */
	spi_transaction(SPI, len, buffer, dummyBuffer);

}

void spi_transaction(struct spi * SPI, size_t len, uint16_t * sendBuffer, uint16_t * recvBuffer){

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
