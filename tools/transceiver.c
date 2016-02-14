#include "transceiver.h"

/* make struct, assign the addresses */
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

void configure_transceiver(void){
	#define WRITE 1
	#define READ 0
	uint16_t results[6];
	uint16_t OpModeCfg = mask_spi_addr(transceiver.RegOpMode, WRITE, 0x08);

	/* set transceiver op mode to FS mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[0]);

	//Set the carrier frequency to 436.5 assuming transceiver PLL at 32MHz
	
	/* RegFrfMsb */
	uint16_t FrfMsbCfg = mask_spi_addr(transceiver.RegFrfMsb, WRITE, 0x6D);

	/* RegFrfMid */
	uint16_t FrfMidCfg = mask_spi_addr(transceiver.RegFrfMid, WRITE, 0x20);

	/* RegFrfLsb */
	uint16_t FrfLsbCfg = mask_spi_addr(transceiver.RegFrfLsb, WRITE, 0x00);

	/* WRITE configuration to appropriate registers */
	spi_transaction(&SPI0, 1, &FrfMsbCfg, &results[1]);
	spi_transaction(&SPI0, 1, &FrfMidCfg, &results[2]);
	spi_transaction(&SPI0, 1, &FrfLsbCfg, &results[3]);

	/* turn modulation to on-off keying */
	uint16_t RegDataModulCfg = mask_spi_addr(transceiver.RegDataModul, WRITE, 0x68);
	spi_transaction(&SPI0, 1, &RegDataModulCfg, &results[4]);

	/* Set transceiver to transmit mode by writing to op mode register */
	OpModeCfg = mask_spi_addr(transceiver.RegOpMode, WRITE, 0x0C);

	/* set transceiver op mode to transmit mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[5]);
}

/*
void read_register(uint8_t address, uint8_t * buffer, uint8_t length);
void write_register(uint8_t address, uint8_t * buffer, uint8_t length);
*/

/*Change to operating mode of the transceiver. Sets bits 2-4 in RegOpMode*/
/*
void trans_set_op_mode(uint8_t * mode){
	uint8_t current_value;
	read_register(transceiver.RegOpMode, &current_value, 0x1);
	uint8_t new_value = current_value & !mode;
	new_value |= mode;
	write_register(transceiver.RegOpMode, &new_value, 0x1);
}
*/
/*Configures the data modulation settings for the transceiver. See header for struct and defines*/
/*
void trans_set_data_mod(struct mod_config * config){
	uint8_t new_value = mod_config->data_mode << 5;
	new_value |= mod_config->mod_type << 3;
	new_value |= mod_config->mod_shaping;

	write_register(transceiver.RegDataModul, &new_value, 0x1);
}
*/
/*Calibrates the RC*/
//void trans_calibrate_rc(void){
	/*Initialize the calibration*/
	//write_register(transceiver.Osc1, 0x80, 0x1);

	/*Wait until the calibration is done*/
	//uint8_t done = 0x0;
	//while (!done){
		//read_register(transceiver.Osc1, &done, 0x1);
		//done &= 0x40;
	//}
//}

/*Returns the low battery status*/
//maybe include the current lowbat threshold later
/*
bool trans_read_low_bat(void){
	uint8_t battery_low;
	read_register(transceiver.LowBat, &battery_low, 0x1);
	return (battery_low & 0x10);
}
*/
/*Enable the transceiver's ow battery monitor*/
/*
void trans_enable_battery_mon(void){
	uint8_t current_value;
	read_register(transceiver.LowBat, &current_value, 0x1);
	uint8_t new_value = current_value |= 0x08;
	write_register(transceiver.LowBat, &new_value, 0x1);
}
*/
/*Disables the transceiver's low battery monitor*/
/*
void trans_disable_battery_mon(void){
	uint8_t current_value;
	read_register(transceiver.LowBat, &current_value, 0x1);
	uint8_t new_value = current_value &= 0xF7;
	write_register(transceiver.LowBat, &new_value, 0x1);	
}
*/
/*
000 - 1.695 V
001 - 1.764 V
010 - 1.835 V
011 - 1.905 V
100 - 1.976 V
101 - 2.045 V
110 - 2.116 V
111 - 2.185 V
*/
/*
void trans_set_lowbat_thresh(uint8_t * threshold){
	
}*/
/*
void trans_config_listen(struct listen_config * config);
void trans_set_pa_output(uint8_t * power);
*/
//void trans_set_pa_ramp(uint8_t * ramp_speed); /*In FSK mode*/
/*
void trans_enable_ocp(void);
void trans_disable_ocp(void);
void trans_set_ocp_trim(uint8_t * trim_value);
void trans_enable_aes(void);
void trans_disable_aes(void);
*/
//void trans_set_aes_key(uint8_t * buffer); /*16 bytes*/
/*
void trans_set_automode_enter(uint8_t * enter_cond);
void trans_set_automode_exit(uint8_t * exit_cond);
void trans_set_automode_intermed(uint8_t * intermed_cond);
*/
//cf
//sync
/*
void trans_start_temp_measure(void);
uint8_t trans_read_temp(void);
void trans_set_lna_sensitivity(uint8_t * sensitivity);
void trans_set_pll_bandwidth(uint8_t * bandwidth);
void trans_set_continuous_dagc(uint8_t * dagc);
void trans_set_lowbeta_agc_offset(uint8_t * offset);
*/
