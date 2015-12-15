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
	uint8_t RegRssiValue; /* RSSI value in dBm */
	uint8_t RegDioMapping1; /* Mapping of pins DIO0 to DIO3 */
	uint8_t RegDioMapping2; /* Mapping of pins DIO4 and DIO5/Clkout frequency */
	uint8_t RegIrqFlags1; /* Status register: PLL Lock state, Timeout, RSSI > Threshold... */
	uint8_t RegIrqFlags2; /* Status register: FIFO handling flags, Low battery detection... */
	uint8_t RegRssiThresh; /* RSSI Threshold control */
	uint8_t RegRxTimeout1; /* Timeout duration between RX request and RSSI detection */
	uint8_t RegRxTimeout2; /* Timeout duration between RSSI detection and PayloadReady */
	uint8_t PreambleMsb; /* Preamble length, MSB */
	uint8_t PreambleLsb; /* Preamble length, LSB */
	uint8_t RegSyncConfig; /* Sync Word Recognition control */
	uint8_t RegSyncValue1; /* Sync Word byte 1 */
	uint8_t RegSyncValue2; /* Sync Word byte 2 */
	uint8_t RegSyncValue3; /* Sync Word byte 3 */
	uint8_t RegSyncValue4; /* Sync Word byte 4 */
	uint8_t RegSyncValue5; /* Sync Word byte 5 */
	uint8_t RegSyncValue6; /* Sync Word byte 6 */
	uint8_t RegSyncValue7; /* Sync Word byte 7 */
	uint8_t RegSyncValue8; /* Sync Word byte 8 */
	uint8_t RegPacketConfig; /* Packet mode settings */
	uint8_t RegPayloadLength; /* Payload length setting */
	uint8_t RegNodeAdrs; /* Node address */
	uint8_t RegBroadcastAdrs; /* Broadcast address */
	uint8_t RegAutoModes; /* Auto modes settings */
	uint8_t RegFifoThresh; /* Fifo threshold, TX start condition */
	uint8_t RegPacketConfig2; /* Packet mode settings */
	uint8_t RegAesKey1; /* cypher key, byte 1 */
	uint8_t RegAesKey2; /* cypher key, byte 2 */
	uint8_t RegAesKey3; /* cypher key, byte 3 */
	uint8_t RegAesKey4; /* cypher key, byte 4 */
	uint8_t RegAesKey5; /* cypher key, byte 5 */
	uint8_t RegAesKey6; /* cypher key, byte 6 */
	uint8_t RegAesKey7; /* cypher key, byte 7 */
	uint8_t RegAesKey8; /* cypher key, byte 8 */
	uint8_t RegAesKey9; /* cypher key, byte 9 */
	uint8_t RegAesKey10; /* cypher key, byte 10 */
	uint8_t RegAesKey11; /* cypher key, byte 11 */
	uint8_t RegAesKey12; /* cypher key, byte 12 */
	uint8_t RegAesKey13; /* cypher key, byte 13 */
	uint8_t RegAesKey14; /* cypher key, byte 14 */
	uint8_t RegAesKey15; /* cypher key, byte 15 */
	uint8_t RegAesKey16; /* cypher key, byte 16 */
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
