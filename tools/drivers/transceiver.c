/*
	Implementation file for transceiver driver.
	Contains a struct that holds the addresses for registers
	in the transceiver block. Also contains basic functions
	for utilizing the transceiver.

	Programmed by William Harrington and Michael Mathis
 */
#include "transceiver.h"
#include "spi.h"


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
	.PDSTST3 = 0x5F,
	.RegTestDagc = 0x6F,
	.RegTestAfc = 0x71,
	.RegTest = 0x50,
};


void trans_read_register(uint8_t * address, uint8_t * buffer, uint8_t length){
	/*
	   This function initiates a SPI transaction for reading
	   a register in the transceiver block. It is assumed that
	   the SPI0 module is in 8-bit mode.

           input address: pointer to unsigned 8-bit integer
			  that represents the address of the
			  register to read

	   input buffer: pointer to unsigned 8-bit integer that
			 represents start of array to fill with
			 data from register

	   input length: unsigned 8-bit integer that represents
			 the length of the transaction

	   return is void
	*/

	/* array for holding addresses */
	uint8_t addresses[length];

	/* copy address into every element of array */
	for(int i = 0; i < length; i++){
		addresses[i] = *address;
	}

	/* conduct SPI transaction */
	spi_transaction_8(&SPI0, length , addresses, buffer);
}

void trans_write_register(uint8_t * address, uint8_t * buffer, uint8_t length){
	/*
	   This function initiates a SPI transaction for writing to
	   the transceiver. It is assumed that the SPI0 module is in
	   8-bit mode.

	   input address: pointer to unsigned 8-bit integer
			  representing register to write to

	   input buffer: pointer to unsigned 8-bit integer
			 representing bytes to write

	   input length: unsigned 8-bit integer representing
			 length of transaction

	   return is void
	*/

	/* array for combining address and data */
	uint8_t addr_buf[length + 1];

	/* mask address byte with leading 1 for write */
	addr_buf[0] = *address | 0x80;

	/* copy data to remaining elements in array */
	for (int i = 0; i < length; i++){
		addr_buf[i + 1] = buffer[i];
	}

	/* dummy array for receive part of transaction */ 
	uint8_t recv[length + 1];

	/* conduct SPI transaction */
	spi_transaction_8(&SPI0, (length + 1), addr_buf, recv);
}

/*Sets up the carrier frequency for the transceiver*/
void configure_transceiver(void){
	/*
	   This function configures the transceiver assuming
	   a 16-bit spi mode for the SPI0 module.

	   return is void
	*/
	uint16_t results[7];

	uint16_t OpModeCfg = 0x08;
	spi_transaction_16(&SPI0, 1, &OpModeCfg, &results[0]);
	//trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);
	//trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);

	//Set the carrier frequency to 436.5 assuming transceiver PLL at 32MHz
	
	/* RegFrfMsb */
	uint16_t FrfMsbCfg = ((transceiver.RegFrfMsb | 0x80) << 8) | 0x6D;
	//uint8_t FrfMsbCfg = 0x6D;

	/* RegFrfMid */
	uint16_t FrfMidCfg = ((transceiver.RegFrfMid | 0x80) << 8) | 0x20;
	//uint8_t FrfMidCfg = 0x20;

	/* RegFrfLsb */
	uint16_t FrfLsbCfg = ((transceiver.RegFrfLsb | 0x80) << 8) | 0x00;
	//uint8_t FrfLsbCfg = 0x00;

	/* WRITE configuration to appropriate registers */
	//trans_write_register(transceiver.RegFrfMsb, &FrfMsbCfg, 1);
	//trans_write_register(transceiver.RegFrfMid, &FrfMidCfg, 1);
	//trans_write_register(transceiver.RegFrfLsb, &FrfLsbCfg, 1);
	spi_transaction_16(&SPI0, 1, &FrfMsbCfg, &results[1]);
	spi_transaction_16(&SPI0, 1, &FrfMidCfg, &results[2]);
	spi_transaction_16(&SPI0, 1, &FrfLsbCfg, &results[3]);

	/* turn modulation to on-off keying */
	uint16_t RegDataModulCfg = ((transceiver.RegDataModul | 0x80) << 8) | 0x68;
	//uint16_t RegDataModulCfg = 0x68;
	spi_transaction_16(&SPI0, 1, &RegDataModulCfg, &results[4]);
	//trans_write_register(transceiver.RegDataModul, &RegDataModulCfg, 1);

	/* configure PA level */
	/* 0x90 = ~0dBm, 0x91 = ~1dBm, 0x92 = ~2dBm, 0x80 = ~-18dBm */
	uint16_t RegPAOutputCfg = ((transceiver.RegPaLevel | 0x80) << 8) | 0x8C;
	//uint8_t RegPAOutputCfg = 0x00;
	spi_transaction_16(&SPI0, 1, &RegPAOutputCfg, &results[5]);
	//trans_write_register(transceiver.RegPaLevel, &RegPAOutputCfg, 1);

	/* Set transceiver to transmit mode by writing to op mode register */
	OpModeCfg = ((transceiver.RegOpMode | 0x80) << 8) | 0x0C;
	//OpModeCfg = 0x0C;
	//trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);
	spi_transaction_16(&SPI0, 1, &OpModeCfg, &results[6]);
}

/*Sets up the carrier frequency for the transceiver*/
void configure_transceiver_8(void){
	/*
	   This function configures the transceiver assuming
	   a 8-bit spi mode for the SPI0 module.

	   return is void
	*/
	uint8_t results[7];

	uint8_t OpModeCfg = 0x08;
	spi_transaction_8(&SPI0, 1, &OpModeCfg, &results[0]);
	//trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);
	//trans_write_register(transceiver.RegOpMode, &OpModeCfg, 1);

	//Set the carrier frequency to 436.5 assuming transceiver PLL at 32MHz
	
	/* RegFrfMsb */
	uint8_t FrfMsbCfg = 0x6D;

	/* RegFrfMid */
	uint8_t FrfMidCfg = 0x20;

	/* RegFrfLsb */
	uint8_t FrfLsbCfg = 0x00;

	/* WRITE configuration to appropriate registers */
	trans_write_register(&transceiver.RegFrfMsb, &FrfMsbCfg, 1);
	trans_write_register(&transceiver.RegFrfMid, &FrfMidCfg, 1);
	trans_write_register(&transceiver.RegFrfLsb, &FrfLsbCfg, 1);

	/* turn modulation to on-off keying */
	uint8_t RegDataModulCfg = 0x68;
	trans_write_register(&transceiver.RegDataModul, &RegDataModulCfg, 1);

	/* configure PA level */
	/* 0x90 = ~0dBm, 0x91 = ~1dBm, 0x92 = ~2dBm, 0x80 = ~-18dBm */
	uint8_t RegPAOutputCfg = 0x8C;
	trans_write_register(&transceiver.RegPaLevel, &RegPAOutputCfg, 1);

	/* Set transceiver to transmit mode by writing to op mode register */
	OpModeCfg = 0x0C;
	trans_write_register(&transceiver.RegOpMode, &OpModeCfg, 1);
}
