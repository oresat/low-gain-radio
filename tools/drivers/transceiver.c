/*
	Implementation file for transceiver driver.
	Contains a struct that holds the addresses for registers
	in the transceiver block. Also contains basic functions
	for utilizing the transceiver.

	Programmed by William Harrington and Michael Mathis
 */
#include "transceiver.h"
#include "spi.h"
#include <string.h>

/* assign the addresses to struct for registers in transceiver block */
struct TRANSCEIVER transceiver = {
	.RegFifo = 0x00,
	.RegOpMode = 0x01,
	.RegDataModul = 0x02,
	.RegBitrateMsb = 0x03,
	.RegBitrateLsb = 0x04,
	.RegFdevMsb = 0x05,
	.RegFdevLsb = 0x06,
	.RegFrfMsb = 0x07,
	.RegFrfMid = 0x08,
	.RegFrfLsb = 0x09,
	.RegOsc1 = 0x0A,
	.RegAfcCtrl = 0x0B,
	.RegLowBat = 0x0C,
	.RegListen1 = 0x0D,
	.RegListen2 = 0x0E,
	.RegListen3 = 0x0F,
	.RegVersion = 0x10,
	.RegPaLevel = 0x11,
	.RegPaRamp = 0x12,
	.RegOcp = 0x13,
	.RegLna = 0x18,
	.RegRxBw = 0x19,
	.RegAfcBw = 0x1A,
	.RegOokPeak = 0x1B,
	.RegOokAvg = 0x1C,
	.RegOokFix = 0x1D,
	.RegAfcFei = 0x1E,
	.RegAfcMsb = 0x1F,
	.RegAfcLsb = 0x20,
	.RegFeiMsb = 0x21,
	.RegFeiLsb = 0x22,
	.RegRssiConfig = 0x23,
	.RegRssiValue = 0x24,
	.RegDioMapping1 = 0x25,
	.RegDioMapping2 = 0x26,
	.RegIrqFlags1 = 0x27,
	.RegIrqFlags2 = 0x28,
	.RegRssiThresh = 0x29,
	.RegRxTimeout1 = 0x2A,
	.RegRxTimeout2 = 0x2B,
	.RegPreambleMsb = 0x2C,
	.RegPreambleLsb = 0x2D,
	.RegSyncConfig = 0x2E,
	.RegSyncValue1 = 0x2F,
	.RegSyncValue2 = 0x30,
	.RegSyncValue3 = 0x31,
	.RegSyncValue4 = 0x32,
	.RegSyncValue5 = 0x33,
	.RegSyncValue6 = 0x34,
	.RegSyncValue7 = 0x35,
	.RegSyncValue8 = 0x36,
	.RegPacketConfig1 = 0x37,
	.RegPayloadLength = 0x38,
	.RegNodeAdrs = 0x39,
	.RegBroadcastAdrs = 0x3A,
	.RegAutoModes = 0x3B,
	.RegFifoThresh = 0x3C,
	.RegPacketConfig2 = 0x3D,
	.RegAesKey1 = 0x3E,
	.RegAesKey2 = 0x3F,
	.RegAesKey3 = 0x40,
	.RegAesKey4 = 0x41,
	.RegAesKey5 = 0x42,
	.RegAesKey6 = 0x43,
	.RegAesKey7 = 0x44,
	.RegAesKey8 = 0x45,
	.RegAesKey9 = 0x46,
	.RegAesKey10 = 0x47,
	.RegAesKey11 = 0x48,
	.RegAesKey12 = 0x49,
	.RegAesKey13 = 0x4A,
	.RegAesKey14 = 0x4B,
	.RegAesKey15 = 0x4C,
	.RegAesKey16 = 0x4D,
	.RegTemp1 = 0x4E,
	.RegTemp2 = 0x4F,
	.RegTestLna = 0x58,
	.RegTestPLL = 0x5F,
	.RegTestDagc = 0x6F,
	.RegTestAfc = 0x71,
};


static struct TRANSCEIVER defaults = {
	.RegFifo = 0x00,
	.RegOpMode = 0x04,
	.RegDataModul = 0x00,
	.RegBitrateMsb = 0x1A,
	.RegBitrateLsb = 0x0B,
	.RegFdevMsb = 0x00,
	.RegFdevLsb = 0x52,
	.RegFrfMsb = 0xD4,
	.RegFrfMid = 0xC0,
	.RegFrfLsb = 0x00,
	.RegOsc1 = 0x41,
	.RegAfcCtrl = 0x00,
	.RegLowBat = 0x02,
	.RegListen1 = 0x92,
	.RegListen2 = 0xF5,
	.RegListen3 = 0x20,
	.RegVersion = 0x23,
	.RegPaLevel = 0x9F,
	.RegPaRamp = 0x09,
	.RegOcp = 0x1A,
	.RegLna = 0x08,
	.RegRxBw = 0x86,
	.RegAfcBw = 0x8A,
	.RegOokPeak = 0x40,
	.RegOokAvg = 0x80,
	.RegOokFix = 0x06,
	.RegAfcFei = 0x10,
	.RegAfcMsb = 0x00,
	.RegAfcLsb = 0x00,
	.RegFeiMsb = 0x00,
	.RegFeiLsb = 0x00,
	.RegRssiConfig = 0x02,
	.RegRssiValue = 0xFF,
	.RegDioMapping1 = 0x00,
	.RegDioMapping2 = 0x05,
	.RegIrqFlags1 = 0x80,
	.RegIrqFlags2 = 0x00,
	.RegRssiThresh = 0xFF,
	.RegRxTimeout1 = 0x00,
	.RegRxTimeout2 = 0x00,
	.RegPreambleMsb = 0x00,
	.RegPreambleLsb = 0x03,
	.RegSyncConfig = 0x98,
	.RegSyncValue1 = 0x00,
	.RegSyncValue2 = 0x00,
	.RegSyncValue3 = 0x00,
	.RegSyncValue4 = 0x00,
	.RegSyncValue5 = 0x00,
	.RegSyncValue6 = 0x00,
	.RegSyncValue7 = 0x00,
	.RegSyncValue8 = 0x00,
	.RegPacketConfig1 = 0x10,
	.RegPayloadLength = 0x40,
	.RegNodeAdrs = 0x00,
	.RegBroadcastAdrs = 0x00,
	.RegAutoModes = 0x00,
	.RegFifoThresh = 0x0F,
	.RegPacketConfig2 = 0x02,
	.RegAesKey1 = 0x00,
	.RegAesKey2 = 0x00,
	.RegAesKey3 = 0x00,
	.RegAesKey4 = 0x00,
	.RegAesKey5 = 0x00,
	.RegAesKey6 = 0x00,
	.RegAesKey7 = 0x00,
	.RegAesKey8 = 0x00,
	.RegAesKey9 = 0x00,
	.RegAesKey10 = 0x00,
	.RegAesKey11 = 0x00,
	.RegAesKey12 = 0x00,
	.RegAesKey13 = 0x00,
	.RegAesKey14 = 0x00,
	.RegAesKey15 = 0x00,
	.RegAesKey16 = 0x00,
	.RegTemp1 = 0x01,
	.RegTemp2 = 0x00,
	.RegTestLna = 0x1B,
	.RegTestPLL = 0x00,
	.RegTestDagc = 0x00,
	.RegTestAfc = 0x00,
};



void trans_read_register(uint8_t address, uint8_t * buffer, uint8_t length){
	/*
	   This function initiates a SPI transaction for reading
	   a register(s) in the transceiver block. It is assumed that
	   the SPI0 module is in 8-bit mode.
	*/

	/* We need to send arbitrary values after the address byte 
		because the transceiver autoincrements the address */
	uint8_t write_data[length + 1];
	uint8_t recv[length + 1];

	write_data[0] = address;
	memset(write_data + 1, 0, length);

	spi_transaction(&SPI0, length + 1, write_data, recv);

	/* Copy the received data back into the user's buffer */
	memcpy(buffer, recv + 1, length);

}

void trans_write_register(uint8_t address, uint8_t * buffer, uint8_t length){
	/*
	   This function initiates a SPI transaction for writing to
	   the transceiver. It is assumed that the SPI0 module is in
	   8-bit mode.
	*/

	/* Array for combining address and data */
	uint8_t addr_buf[length + 1];

	/* Mask address byte with leading 1 for write */
	addr_buf[0] = address | 0x80;

	/* copy data to remaining elements in array */
	memcpy(addr_buf + 1, buffer, length);

	/* dummy array for receive part of transaction */ 
	uint8_t recv[length + 1];

	/* conduct SPI transaction */
	spi_transaction_8(&SPI0, (length + 1), addr_buf, recv);
}

#define LnaZin50 0x08
#define RcCalStart (1 << 7)
#define RcCalDone (1 << 6)

#define DataModul_FSK 0x0
#define PLLBandwidth_75kHz 0x0

// RegOpMode
#define SequencerOff (1 << 7)
#define ListenAbort (1 << 5)
#define ModeListen (1 << 6)
#define ModeSleep (0 << 2)
#define ModeStdby (1 << 2)
#define ModeFS    (2 << 2)
#define ModeTX    (3 << 2)
#define ModeRX    (4 << 2)
// RegDataModul
#define Packet (0 << 5)
#define Continuous (2 << 5)
#define ContinuousNoSync (3 << 5)
#define FSK (0 << 3)
#define OOK (1 << 3)
#define NoShaping (0 << 0)


#define FXOSC (32000000) //32MHz
#define Fstep (FXOSC/(1<<19))
#define FstepMul ((uint64_t)(1 << 8))
#define FstepDiv ((uint64_t)(15625))

static void setCarrierFrequency(uint32_t carrierHz) {
	uint64_t frf = ((uint64_t)carrierHz * FstepMul) / FstepDiv;
	uint8_t RegFrf[3] = {(frf >> 16) & 0xff, (frf >> 8) & 0xff, frf & 0xff};
	trans_write_register(transceiver.RegFrfMsb, RegFrf, 3);
}

static void setFrequencyDeviation(uint32_t deviationHz) {
	uint64_t fdev = ((uint64_t)deviationHz * FstepMul) / FstepDiv;
	uint8_t RegFdev[2] = {(fdev >> 8) & 0x3F, fdev & 0xFF};
	trans_write_register(transceiver.RegFdevMsb, RegFdev, 2);
}

static void setBitrate(uint32_t bitrateHz) {
	uint16_t rate = FXOSC/bitrateHz;
	uint8_t RegBitrate[2] = {(rate >> 8) & 0xff, rate & 0xff};
	trans_write_register(transceiver.RegBitrateMsb, RegBitrate, 2);
}

void configure_transceiver(uint8_t OpModeCfg, uint8_t RegPAOutputCfg){
	/* Change to frequency synthesizer mode */
	trans_write_register(transceiver.RegOpMode, (uint8_t[]){ModeFS}, 1);
	/* turn modulation to frequency shift keying */
	setCarrierFrequency(436500000);
	setFrequencyDeviation(2500);
	setBitrate(2400);

	trans_write_register(transceiver.RegDataModul, (uint8_t[]){Packet | FSK | NoShaping}, 1);
	/* adjust PLL bandwidth to 75kHz */
	trans_write_register(transceiver.RegTestPLL, (uint8_t[]){PLLBandwidth_75kHz}, 1);
	/* set LNA's input impedance to 50 ohm */
	trans_write_register(transceiver.RegLna, (uint8_t[]){LnaZin50}, 1); 
	
	/* configure PA output power */
	trans_write_register(transceiver.RegPaLevel, (uint8_t[]){RegPAOutputCfg}, 1);

	if(OpModeCfg == Mode_TX){
		/*Setup automodes for transmitting*/
		trans_write_register(transceiver.RegAutoModes, (uint8_t[]){0x3B}, 1);
	}
	else if (OpModeCfg == Mode_RX){
		/*Setup RX specific configurations*/
		trans_write_register(transceiver.RegRxBw, (uint8_t[]){0x55}, 1);
		trans_write_register(transceiver.RegRssiThresh, (uint8_t[]){0x70}, 1);
		trans_write_register(transceiver.RegAutoModes, (uint8_t[]){0x85} , 1);
	}

	//0x00 No sync
	//0x98 Sync with 4 bytes
	trans_write_register(transceiver.RegSyncConfig, (uint8_t[]){0xC1}, 1); 

	/*Sync word setup*/
	trans_write_register(transceiver.RegSyncValue1, (uint8_t[]){0xE7, 0xE7, 0xE7, 0xE7}, 4);

	/*Setup the packet config: no encoding no crc*/
	trans_write_register(transceiver.RegPacketConfig1, (uint8_t[]){0x08}, 1);

	//Sets preamble size
	trans_write_register(transceiver.RegPreambleMsb, (uint8_t[]){0x00, 0x06}, 2);

	//Sets the payload length
	/*
		The payload length needs to be equal to the buffer of data to be sent 
		when the tx ready signal is produces on fifo_not_empty. If the tx 
		ready signal is received from a fifo threshold reached condition
		then the payload length needs to be the same as the fifo threshold and 
		the buffer needs to be one larger than the payload size.

		When using auto modes be sure to set the transceiver into standby mode
		it will wake and do its thing automagically.

	*/
	trans_write_register(transceiver.RegPayloadLength, (uint8_t[]){5}, 1);

	/* To trigger on a fifo threshhold set RegFifoThresh to PACKET_LENGTH*/
	/* Trigger on fifo not empty */
	trans_write_register(transceiver.RegFifoThresh, (uint8_t[]){0x04}, 1);

	/* Set transceiver mode */
	trans_write_register(transceiver.RegOpMode, (uint8_t[]){OpModeCfg}, 1);
}
