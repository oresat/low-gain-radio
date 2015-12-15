/*
	Struct for transceiver register mapping

	Programmed by William Harrington
*/

/* struct declaration for transceiver */
struct TRANSCEIVER {
  	uint8_t RegFifo; /* FIFO read/write access */
  	uint8_t RegOpMode; /* Operating modes of the transceiver */
  	uint8_t RegDataModul; /* Data operation mode and modulation settings */
  	uint8_t RegBitrateMsb; /* bit rate setting, most significant bits */
  	uint8_t RegBitrateLsb; /* bit rate setting, least significant bits */
  	uint8_t RegFdevMsb; /* frequency deviation setting, most significant bits */
  	uint8_t RegFdevLsb; /* frequency deviation setting, least significant bits */
  	uint8_t RegFrfMsb; /* RF carrier frequency, most significant bits */
	uint8_t RegFrfLsb; /* RF carrier frequency, least significant bits */
	uint8_t RegOsc1; /* RC Oscillators Settings */
	uint8_t RegAfcCtrl; /* AFC control in low modulation index situations */
	uint8_t RegLowBat; /* Low Battery Indicator Settings */
	uint8_t RegListen1; /* Listen Mode settings */
	uint8_t RegListen2; /* Listen Mode Idle duration */
	uint8_t RegListen3; /* Listen Mode RX duration */
	uint8_t RegVersion; /* RF ID relating the silicon revision */
	uint8_t RegPaLevel; /* PA selection and Output Power control */
	uint8_t RegPaRamp; /* Control of the PA ramp time in FSK mode */
	uint8_t RegOcp; /* Over Current Protection control */
	uint8_t RegLna; /* LNA settings */
	uint8_t RegRxBw; /* Channel Filter BW Control */
	uint8_t RegAfcBw; /* Channel Filter BW control during the AFC routine */
	uint8_t RegOokPeak; /* OOK demodulator selection and control in peak mode */
	uint8_t RegOokAvg; /* Average threshold control of the OOK demodulator */
	uint8_t RegOokFix; /* Fixed threshold control of the OOK demodulator */
	uint8_t RegAfcFei; /* AFC and FEI control and status */
	uint8_t RegAfcMsb; /* MSB of the frequency correction of the AFC */
	uint8_t RegAfcLsb; /* LSB of the frequency correction of the AFC */
	uint8_t RegFeiMsb; /* MSB of the calculated frequency error */
	uint8_t RegFeiLsb; /* LSB of the calculated frequency error */
	uint8_t RegRssiConfig; /* RSSI-related settings */
};


/* make struct, assign the addresses */
struct TRANSCEIVER transceiver = {
	.RegFifo = 0x00;
	.RegOpMode = 0x01;
	.RegDataModul = 0x02;
	.RegBitrateMsb = 0x03;
	.RegBitrateLsb = 0x04;
	.RegFdevMsb = 0x05;
	.RegFdevLsb = 0x06;
	.RegFrfMsb = 0x07;
}
