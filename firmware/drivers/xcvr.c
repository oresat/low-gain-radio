/* \file xcvr.c
 */
/*
    Original Programmed by William Harrington and Michael Mathis
 */

#include "xcvr.h"

struct TRANSCEIVER xcvr_addrs =
{
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

static struct TRANSCEIVER xcvr_defaults =
{
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

bool xcvr_read_8bit_reg(uint8_t regaddr, uint8_t * d)
{
	return(spi0_read_8_poll(regaddr, d));
}

bool xcvr_read_8bit_reg_burst(uint8_t regaddr, uint8_t * d, uint16_t len){
	for(uint16_t i = 0; i < len; i++){
		if(!xcvr_read_8bit_reg(regaddr + i, d + i)) return false;
	}
	return true;
}

bool xcvr_write_8bit_reg(uint8_t regaddr, uint8_t payload)
{
	return(spi0_write_8_poll(regaddr, payload));
}

bool xcvr_write_8bit_reg_burst(uint8_t regaddr, uint8_t * payload, uint16_t len){
	for(uint16_t i = 0; i < len; i++){
		if(!xcvr_write_8bit_reg(regaddr + i, *(payload + i))) return false;
	}
	return true;
}

/* XTA,XTB connected to 32Mhz Crystal
 *  32/d = DIO5/CLKOUT Freq
 */
bool xcvr_set_outclk_div(XCVR_outdivs d)
{
	return(spi0_write_8_poll(xcvr_addrs.RegDioMapping2, d));
}

#define LNA_Zin_50 0x08
#define RcCalStart (1 << 7)
#define RcCalDone (1 << 6)
#define DataModul_FSK 0x0
#define PLLBandwidth_75kHz 0x0
#define PLLBandwidth_150kHz 0x4
#define PLLBandwidth_300kHz 0x8
#define PLLBandwidth_600kHz 0xC

// RegOpMode
#define SequencerOff (1 << 7)
#define ListenAbort (1 << 5)
//Modes moved to xcvr.h

// RegDataModul
#define Packet (0 << 5)
#define Continuous (2 << 5)
#define ContinuousNoSync (3 << 5)
#define FSK (0 << 3)
#define OOK (1 << 3)
#define NoShaping (0 << 0)

// RegAutoModes
#define EnterNone         (0b000 << 5)
#define EnterFifoNotEmpty (0b001 << 5)
#define EnterFifoLevel    (0b010 << 5)
#define EnterCrcOk        (0b011 << 5)
#define EnterPayloadReady (0b100 << 5)
#define EnterSyncAddress  (0b101 << 5)
#define EnterPacketSent   (0b110 << 5)
#define EnterFifoEmpty    (0b111 << 5)
#define ExitNone         (0b000 << 2)
#define ExitFifoEmpty    (0b001 << 2)
#define ExitFifoLevel    (0b010 << 2)
#define ExitCrcOk        (0b011 << 2)
#define ExitPayloadReady (0b100 << 2)
#define ExitSyncAddress  (0b101 << 2)
#define ExitPacketSent   (0b110 << 2)
#define ExitTimeout      (0b111 << 2)
#define InterSleep (0b00 << 0)
#define InterStdby (0b01 << 0)
#define InterRX    (0b10 << 0)
#define InterTX    (0b11 << 0)

// RegSyncConfig
#define SyncOn (1 << 7)
#define FifoFillSyncAddress (0 << 6)
#define FifoFillCondition (1 << 6)
#define SyncSize(bytes) ((((bytes) - 1) & 0x7) << 3)
#define SyncTol(errors) ((errors) & 0x7)

// RegAfcFei
#define AfcAutoOn (1 << 2)
#define AfcAutoclearOn (1 << 3)

#define FXOSC (32000000) //32MHz
#define Fstep (FXOSC/(1<<19))
#define FstepMul ((uint64_t)(1 << 8))
#define FstepDiv ((uint64_t)(15625))

static bool setCarrierFrequency(uint32_t carrierHz)
{
	/*
		Set carrier frequency

		Carrier Frequency formula
		section 5.5.3.3 of reference manual

		CAUTION: Weird math here because only 24 bits
			 to represent 436.5MHz?
	*/
	uint64_t frf = ((uint64_t)carrierHz * FstepMul) / FstepDiv;	
	uint8_t RegFrf[3] = {(frf >> 16) & 0xff, (frf >> 8) & 0xff, frf & 0xff};
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegFrfMsb, RegFrf, 3);
}

static bool setFrequencyDeviation(uint32_t deviationHz)
{
	/*
		Set frequency deviation for FSK
	*/
	uint64_t fdev = ((uint64_t)deviationHz * FstepMul) / FstepDiv;
	uint8_t RegFdev[2] = {(fdev >> 8) & 0x3F, fdev & 0xFF};
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegFdevMsb, RegFdev, 2);
}

static bool setBitrate(uint32_t bitrateHz)
{
	/*
		Set bitrate
	*/
	uint16_t rate = FXOSC/bitrateHz;
	uint8_t RegBitrate[2] = {(rate >> 8) & 0xff, rate & 0xff};
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegBitrateMsb, RegBitrate, 2);
}

bool changeMode(uint8_t mode)
{
	/* only accept mode constants */
	if((mode != ModeSleep) &
	   (mode != ModeStdby) &
	   (mode != ModeFS) &
	   (mode != ModeTX) &
	   (mode != ModeRX)) return false;

	return xcvr_write_8bit_reg(xcvr_addrs.RegOpMode, mode);
}

static bool changeDataModulation(uint8_t dataMode, uint8_t modulationType, uint8_t modulationShaping)
{
	/* only accept RegDataModul constants */
	if((dataMode != Packet) &
	   (dataMode != Continuous) &
	   (dataMode != ContinuousNoSync)) return false;
        if((modulationType != FSK) &
	   (modulationType != OOK)) return false;
        if((modulationShaping != NoShaping)) return false;

	return xcvr_write_8bit_reg(xcvr_addrs.RegDataModul, dataMode | modulationType | modulationShaping);
}

static bool adjustPLLBandwidth(uint8_t bandwidth)
{
	/* only accept bandwidth constants */
	if((bandwidth != PLLBandwidth_75kHz) &
           (bandwidth != PLLBandwidth_150kHz) &
           (bandwidth != PLLBandwidth_300kHz) &
           (bandwidth != PLLBandwidth_600kHz)) return false;

	return xcvr_write_8bit_reg(xcvr_addrs.RegTestPLL, bandwidth);
}

static bool setLNAInputImpedance(uint8_t zin)
{
	if((zin != LNA_Zin_50)) return false;

	return xcvr_write_8bit_reg(xcvr_addrs.RegLna, zin);
}

static bool setPAOutputPower(uint8_t cfg)
{
	/*
		CAUTION: This function is dangerous!
			 If you are not careful you could fry a board.
	*/
	return xcvr_write_8bit_reg(xcvr_addrs.RegPaLevel, cfg);
}

static bool setAutoModes(uint8_t OpModeCfg)
{
	uint8_t autoModes = 0;
	if(OpModeCfg == ModeTX)
		autoModes = EnterFifoNotEmpty | InterTX | ExitPacketSent;
	else
		autoModes = EnterNone | InterSleep | ExitNone;
		//autoModes = EnterSyncAddress | InterRX | ExitFifoNotEmpty;
		//autoModes = EnterPayloadReady | InterSleep | ExitFifoEmpty;

	return xcvr_write_8bit_reg(xcvr_addrs.RegAutoModes, autoModes);
}

static bool setSyncConfig(uint8_t SyncCfg)
{
	return xcvr_write_8bit_reg(xcvr_addrs.RegSyncConfig, SyncCfg);
}

static bool setSyncWord(uint8_t * word)
{
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegSyncValue1, word, 4);
}

static bool setPacketConfig(uint8_t cfg)
{
	return xcvr_write_8bit_reg(xcvr_addrs.RegPacketConfig1, cfg);
}

static bool setPreambleSize(uint8_t * size)
{
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegPreambleMsb, size, 2);
}

static bool setAfcFei(uint8_t * cfg)
{
	/* sets RegAfcFei and RegAfcMsb */
	return xcvr_write_8bit_reg_burst(xcvr_addrs.RegAfcFei, cfg, 2);
}

bool configure_transceiver(uint8_t OpModeCfg, uint8_t RegPAOutputCfg){
	if(!changeMode(ModeFS)) return 0;
	if(!setCarrierFrequency(436500000)) return 0;
	if(!setFrequencyDeviation(2500)) return 0;
	if(!setBitrate(2400)) return 0;
	if(!changeDataModulation(Packet, FSK, NoShaping)) return 0;

	/*
		lower bandwidth = less spurious signals with lower data rate
		higher bandwidth = higher data rates but more spurious signals
	*/
	if(!adjustPLLBandwidth(PLLBandwidth_75kHz)) return 0;

	/* set LNA's input impedance to 50 ohm */
	if(!setLNAInputImpedance(LNA_Zin_50)) return 0;

        if(!setPAOutputPower(RegPAOutputCfg)) return 0;
	if(!setAutoModes(OpModeCfg)) return 0;

	/* recommended RxBw value, see Table 7-4 in transceiver section of reference manual */
	if(!xcvr_write_8bit_reg(xcvr_addrs.RegRxBw, 0x55)) return 0;

	/* set RSSI threshold */
	if(!xcvr_write_8bit_reg(xcvr_addrs.RegRssiThresh, 0x70)) return 0;

	uint8_t SyncConfig = SyncOn | FifoFillSyncAddress | SyncSize(1) | SyncTol(0);
	if(!setSyncConfig(SyncConfig)) return 0;

	if(!setSyncWord((uint8_t[]){0xE7, 0xE7, 0xE7, 0xE7})) return 0;

	/* Setup the packet config: no encoding no crc */
	if(!setPacketConfig(0x08)) return 0;

	//Sets preamble size
	if(!setPreambleSize((uint8_t[]){0x00, 0x10})) return 0;

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
	if(!xcvr_write_8bit_reg(xcvr_addrs.RegPayloadLength, 0x5)) return 0;

	/* To trigger on a fifo threshhold set RegFifoThresh to PACKET_LENGTH*/
	/* Trigger on fifo not empty */
	if(!xcvr_write_8bit_reg(xcvr_addrs.RegFifoThresh, 0x4)) return 0;

	if(!setAfcFei((uint8_t[]){AfcAutoOn | AfcAutoclearOn})) return 0;

	if(!changeMode(OpModeCfg)) return 0;

	return 1;
}


