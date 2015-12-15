/*
	Struct for transceiver register mapping

	Programmed by William Harrington
*/

struct TRANSCEIVER {
  	uint8_t RegFifo = 0x00; /* FIFO read/write access */
  	uint8_t RegOpMode = 0x01; /* Operating modes of the transceiver */
  	uint8_t RegDataModul = 0x02; /* Data operation mode and modulation settings */
  	uint8_t RegBitrateMsb = 0x03; /* bit rate setting, most significant bits */
  	uint8_t RegBitrateLsb = 0x04; /* bit rate setting, least significant bits */
  	uint8_t RegFdevMsb = 0x05; /* frequency deviation setting, most significant bits */
  	uint8_t RegFdevLsb = 0x06; /* frequency deviation setting, least significant bits */
  	uint8_t RegFrfMsb = 0x07; /* RF carrier frequency, most significant bits */
} transceiver;
