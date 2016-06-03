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
#define Mode_FS (1 << 3)

#define DataModul_FSK 0x0
#define PLLBandwidth_75kHz 0x0

void configure_transceiver(uint8_t OpModeCfg, uint8_t RegPAOutputCfg){
	/* Change to frequency synthesizer mode */
	uint8_t OpModeFS = Mode_FS;
	trans_write_register(transceiver.RegOpMode, &OpModeFS, 1);

	/* Set the carrier frequency to 436.5MHz assuming transceiver PLL at 32MHz 
		See Table 7-5 in the reference manual
	*/
	static uint8_t FrfCfg[3] = {0x6D, 0x20, 0x00};
	trans_write_register(transceiver.RegFrfMsb, FrfCfg, 3);

	/* turn modulation to frequency shift keying */
	uint8_t RegDataModulCfg = DataModul_FSK;
	trans_write_register(transceiver.RegDataModul, &RegDataModulCfg, 1);

	/* frequency deviation settings */
	static uint8_t RegFDevCfg[2] = {0x00, 0x29};
	trans_write_register(transceiver.RegFdevMsb, RegFDevCfg, 2);

	/* adjust PLL bandwidth to 75kHz */
	uint8_t RegTestPLLCfg = PLLBandwidth_75kHz;
	trans_write_register(transceiver.RegTestPLL, &RegTestPLLCfg, 1);

	/* bitrate settings = 2.4 kbps */
	static uint8_t RegBitrateCfg[2] = {0x34, 0x15};
	trans_write_register(transceiver.RegBitrateMsb, RegBitrateCfg, 2);

	/* set LNA's input impedance to 50 ohm */
	uint8_t LnaImpedanceConfig = LnaZin50;
	trans_write_register(transceiver.RegLna, &LnaImpedanceConfig, 1); 	

	if(OpModeCfg == Mode_TX){
		/* configure PA output power */
		trans_write_register(transceiver.RegPaLevel, &RegPAOutputCfg, 1);
		/*Setup automodes for transmitting*/
		//uint8_t auto_mode = 0x3B;
		//trans_write_register(transceiver.RegAutoModes, &auto_mode, 1);
    }
    else if (OpModeCfg == Mode_RX){
		/*Setup RX specific configurations*/
		uint8_t auto_afc_on = 0x04;
		trans_write_register(transceiver.RegAfcFei, &auto_afc_on, 1);

		uint8_t rxbw = 0x53;
		trans_write_register(transceiver.RegRxBw, &rxbw, 1);

		uint8_t rssi_thresh = 0xF5;
		trans_write_register(transceiver.RegRssiThresh, &rssi_thresh, 1);

		//uint8_t auto_mode = 0x85;
		//trans_write_register(transceiver.RegAutoModes, &auto_mode, 1);

    }

    /*Sync word setup*/
    //static uint8_t sync_word[] = {'B', 'E', 'E', 'F'};
    //trans_write_register(transceiver.RegSyncValue1, sync_word, 4);

    /*Setup the packet config*/
    static uint8_t encode_fixed_length = 0x00; //no encoding no crc
	trans_write_register(transceiver.RegPacketConfig1, &encode_fixed_length , 1);
	
	//No sync
	static uint8_t no_sync = 0x00; 
	trans_write_register(transceiver.RegSyncConfig, &no_sync, 1); 

	//Sets preamble size
	uint8_t preamble_size = 0x6;
	trans_write_register(transceiver.RegPreambleLsb, &preamble_size, 1);

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
	static uint8_t RegPayloadLengthCfg = PACKET_LENGTH; //PACKET_LENGTH is in transceiver.h
	trans_write_register(transceiver.RegPayloadLength, &RegPayloadLengthCfg, 1);

	/* To trigger on a fifo threshhold set RegFifoThresh to PACKET_LENGTH*/
	/* Trigger on fifo not empty */
	uint8_t fifo_thresh = 0x0;
	trans_write_register(transceiver.RegFifoThresh, &fifo_thresh, 1);

	/* Set transceiver mode */
	trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);
}
