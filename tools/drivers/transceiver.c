#include "transceiver.h"
#include "spi.h"
#include <string.h>


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

void read_register(uint8_t address, uint8_t * buffer, uint8_t length){
	uint8_t addr_buffer [length + 1];
	addr_buffer [0] = address;
	memcpy(addr_buffer + 1, buffer, length);
	spi_read(&SPI0, length + 1, addr_buffer);
}

void write_register(uint8_t address, uint8_t * buffer, uint8_t length){
	uint8_t addr_buffer [length + 1];
	addr_buffer [0] = address;
	memcpy(addr_buffer + 1, buffer, length);
	spi_write(&SPI0, length + 1, addr_buffer);
}
/*COMMON CONFIGURATION FUNCTIONS*/
/*Change to operating mode of the transceiver. Sets bits 2-4 in RegOpMode*/
void trans_set_op_mode(uint8_t mode){
	uint8_t current_value;
	read_register(transceiver.RegOpMode, &current_value, 0x1);
	uint8_t new_value = current_value & !(mode << 2);
	new_value |= (mode << 2);
	write_register(transceiver.RegOpMode, &new_value, 0x1);
}

/*Configures the data modulation settings for the transceiver. See header for struct and defines*/
void trans_set_data_mod(struct mod_config * config){
	uint8_t new_value = config->data_mode << 5;
	new_value |= config->mod_type << 3;
	new_value |= config->mod_shaping;

	write_register(transceiver.RegDataModul, &new_value, 0x1);
}

/*Calibrates the RC*/
void trans_calibrate_rc(void){
	uint8_t calibrate_command = 0x80;
	/*Initialize the calibration*/
	write_register(transceiver.RegOsc1, &calibrate_command, 0x1);

	/*Wait until the calibration is done*/
	uint8_t done = 0x0;
	while (!done){
		read_register(transceiver.RegOsc1, &done, 0x1);
		done &= 0x40;
	}
}

/*Returns the low battery status*/
//maybe include the current lowbat threshold later
bool trans_read_low_bat(void){
	uint8_t battery_low;
	read_register(transceiver.RegLowBat, &battery_low, 0x1);
	return (battery_low & 0x10);
}

/*Enable the transceiver's ow battery monitor*/
void trans_enable_battery_mon(void){
	uint8_t current_value;
	read_register(transceiver.RegLowBat, &current_value, 0x1);
	uint8_t new_value = current_value |= 0x08;
	write_register(transceiver.RegLowBat, &new_value, 0x1);
}

/*Disables the transceiver's low battery monitor*/
void trans_disable_battery_mon(void){
	uint8_t current_value;
	read_register(transceiver.RegLowBat, &current_value, 0x1);
	uint8_t new_value = current_value &= 0xF7;
	write_register(transceiver.RegLowBat, &new_value, 0x1);	
}
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
/*Sets the threshold for the low battery monitor*/
void trans_set_lowbat_thresh(uint8_t threshold){
	uint8_t current_value;
	read_register(transceiver.RegLowBat, &current_value, 0x1);
	uint8_t new_value = current_value & !threshold;
	new_value |= threshold;
	write_register(transceiver.RegLowBat, &new_value, 0x1);
}

uint8_t mask_spi_addr(uint8_t addr, uint8_t write, uint8_t byteToWrite){
	if(write){
		/* masking for write transaction */
		uint8_t result = ((addr | 0x80) << 8) | byteToWrite;
		return result;
	}

	/* masking for read transaction */
     	byteToWrite = 0x00;
	uint8_t result = ((addr & 0x7F) << 8) | byteToWrite;
	return result;
}

/*Sets up the carrier frequency for the transceiver*/
void configure_transceiver(void){
	#define WRITE 1
	uint8_t results[7];
	uint8_t OpModeCfg = mask_spi_addr(transceiver.RegOpMode, WRITE, 0x08);

	/* set transceiver op mode to FS mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[0]);

	//Set the carrier frequency to 436.5 assuming transceiver PLL at 32MHz
	
	/* RegFrfMsb */
	uint8_t FrfMsbCfg = mask_spi_addr(transceiver.RegFrfMsb, WRITE, 0x6D);

	/* RegFrfMid */
	uint8_t FrfMidCfg = mask_spi_addr(transceiver.RegFrfMid, WRITE, 0x20);

	/* RegFrfLsb */
	uint8_t FrfLsbCfg = mask_spi_addr(transceiver.RegFrfLsb, WRITE, 0x00);

	/* WRITE configuration to appropriate registers */
	spi_transaction(&SPI0, 1, &FrfMsbCfg, &results[1]);
	spi_transaction(&SPI0, 1, &FrfMidCfg, &results[2]);
	spi_transaction(&SPI0, 1, &FrfLsbCfg, &results[3]);

	/* turn modulation to on-off keying */
	uint8_t RegDataModulCfg = mask_spi_addr(transceiver.RegDataModul, WRITE, 0x68);
	spi_transaction(&SPI0, 1, &RegDataModulCfg, &results[4]);

	/* configure PA level */
	/* 0x90 = ~0dBm, 0x91 = ~1dBm, 0x92 = ~2dBm, 0x80 = ~-18dBm */
	uint8_t RegPAOutputCfg = mask_spi_addr(transceiver.RegPaLevel, WRITE, 0x80);
	spi_transaction(&SPI0, 1, &RegPAOutputCfg, &results[5]);

	/* Set transceiver to transmit mode by writing to op mode register */
	OpModeCfg = mask_spi_addr(transceiver.RegOpMode, WRITE, 0x0C);

	/* set transceiver op mode to transmit mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[6]);

}

/*Enable listen mode*/
void trans_enable_listen(void){
	uint8_t current_value;
	read_register(transceiver.RegOpMode, &current_value, 0x1);
	uint8_t new_value = current_value | 0x40;
	write_register(transceiver.RegOpMode, &new_value, 0x1);
}

/*Disable listen mode*/
void trans_disable_listen(uint8_t new_mode){
	uint8_t current_value;
	read_register(transceiver.RegOpMode, &current_value, 0x1);
	uint8_t new_value = current_value & !new_mode;
	new_value |= new_mode;
	new_value &= 0xBF;
	new_value |= 0x20;
	write_register(transceiver.RegOpMode, &new_value, 0x1);
}

/*Configure listen mode settings*/
void trans_config_listen(struct listen_config * config){
	/*Page 110 of reference manual*/
	uint8_t listen_config_vals[3];
	listen_config_vals[0] = config->idle_time_res << 6;
	listen_config_vals[0] |= config->receive_time_res << 4;
	listen_config_vals[0] |= config->listen_criteria << 3;
	listen_config_vals[0] |= config->listen_end << 1;
	listen_config_vals[1] = config->idle_coef;
	listen_config_vals[2] = config->receive_coef;

	/*Write the configuration to the three registers*/
	write_register(transceiver.RegListen1, listen_config_vals, 0x3);
}

/*TRANSMITTER CONFIGURATION FUNCTIONS*/
/*Sets the pa output power. -18dB + power with PA0 or PA1. 2dB + power with PA2*/
void trans_set_pa_output(uint8_t power){
	uint8_t current_value;
	read_register(transceiver.RegPaLevel, &current_value, 0x1);
	uint8_t new_value = current_value & !power;
	new_value |= power;
	write_register(transceiver.RegPaLevel, &new_value, 0x1);
}

/*Set the pa ramp power for FSK mode*/
void trans_set_pa_ramp(uint8_t ramp_speed){
	uint8_t current_value;
	read_register(transceiver.RegPaRamp, &current_value, 0x1);
	uint8_t new_value = current_value & !ramp_speed;
	new_value |= ramp_speed;
	write_register(transceiver.RegPaRamp, &new_value, 0x1);
}

/*Enable the overload current protection circuit*/
void trans_enable_ocp(void){
	uint8_t current_value;
	read_register(transceiver.RegOcp, &current_value, 0x1);
	uint8_t new_value = current_value | 0x08;
	write_register(transceiver.RegOcp, &new_value, 0x1);
}

/*Disable the overload current protection circuit*/
void trans_disable_ocp(void){
	uint8_t current_value;
	read_register(transceiver.RegOcp, &current_value, 0x1);
	uint8_t new_value = current_value & 0xF7;
	write_register(transceiver.RegOcp, &new_value, 0x1);
}

/*Set the overload current protection circuit threshold*/
void trans_set_ocp_trim(uint8_t trim_value){
	uint8_t current_value;
	read_register(transceiver.RegOcp, &current_value, 0x1);
	uint8_t new_value = current_value & !trim_value;
	new_value |= trim_value;
	write_register(transceiver.RegOcp, &new_value, 0x1);
}

/*RECEIVER CONFIGURATION FUNCTIONS*/
/*IRQ AND PIN MAPPING CONFIGURATION FUNCTIONS*/
/*PACKET ENGINE CONFIGURATION FUNCTIONS*/
void trans_enable_sync(void){
	uint8_t current_value;
	read_register(transceiver.RegSyncConfig, &current_value, 0x1);
	uint8_t new_value = current_value | 0x80;
	write_register(transceiver.RegSyncConfig, &new_value, 0x1);
}

void trans_disable_sync(void){
	uint8_t current_value;
	read_register(transceiver.RegSyncConfig, &current_value, 0x1);
	uint8_t new_value = current_value & 0x7F;
	write_register(transceiver.RegSyncConfig, &new_value, 0x1);
}

void trans_set_sync_config(struct sync_config * config){
	uint8_t config_value = config->fifo_fill_cond << 6;
	config_value |= config->sync_word_size << 2;
	config_value |= config->sync_error_toleration;

	uint8_t current_value;
	read_register(transceiver.RegSyncConfig, &current_value, 0x1);
	uint8_t new_value = current_value & !config_value;
	new_value |= config_value;
	write_register(transceiver.RegSyncConfig, &new_value, 0x1);

	/*Burst write the whole synce word*/
	for (uint8_t i = 0; i < config->sync_word_size; i++){
		write_register(transceiver.RegSyncValue1, config->sync_word, (config->sync_word_size));
	}
}

void trans_set_packet_config(struct packet_config * config){
	/*Burst write the preamble size to the MSB and LSB registers*/
	write_register(transceiver.RegPreambleMsb, config->preamble_size, 0x2);

	/*Build the configuration value for the packet config 1 reg*/
	uint8_t config_value = config->packet_format << 7;
	config_value |= config->dc_free << 5;
	config_value |= config->crc_check << 4;
	config_value |= config->crc_auto_clear << 3;
	config_value |= config->address_filtering << 1;
	
	write_register(transceiver.RegPacketConfig1, &config_value, 0x1);

	write_register(transceiver.RegPayloadLength, &config->payload_length, 0x1);
	
	write_register(transceiver.RegNodeAdrs, &config->node_address, 0x1);
	
	write_register(transceiver.RegBroadcastAdrs, &config->broadcast_address, 0x1);
	
	config_value = (config->tx_start_cond << 7) | config->fifo_threshold;
	write_register(transceiver.RegFifoThresh, &config_value, 0x1);
	
	config_value = (config->inter_packet_rxdelay << 4) | (config->auto_rx_restart << 1);
	uint8_t current_value;
	read_register(transceiver.RegPacketConfig2, &current_value, 0x1);
	uint8_t new_value;
	new_value = current_value & !config_value;
	new_value |= config_value;
	write_register(transceiver.RegPacketConfig2, &new_value, 0x1);
}

void trans_enable_aes(void){
	uint8_t current_value;
	uint8_t new_value;
	read_register(transceiver.RegPacketConfig2, &current_value, 0x1);
	new_value = current_value | 0x1;
	write_register(transceiver.RegPacketConfig2, &new_value, 0x1);
}

void trans_disable_aes(void){
	uint8_t current_value;
	uint8_t new_value;
	read_register(transceiver.RegPacketConfig2, &current_value, 0x1);
	new_value = current_value & 0xFE;
	write_register(transceiver.RegPacketConfig2, &new_value, 0x1);	
}

void trans_set_aes_key(uint8_t * buffer){ /*16 bytes*/
	write_register(transceiver.RegAesKey1, buffer, 16);
} 

void trans_set_automode_config(struct automode_config * config){
	uint8_t config_value = config->enter_cond << 5;
	config_value |= config->exit_cond << 2;
	config_value |= config->intermed_cond;

	write_register(transceiver.RegAutoModes, &config_value, 0x1);
}

/*TEMPERATURE SENSOR CONFIGURATION FUNCTIONS*/
void trans_start_temp_measure(void){
	uint8_t reading_temp;
	uint8_t current_value;
	read_register(transceiver.RegTemp1, &current_value, 0x1);
	uint8_t new_value = current_value | 0x08;
	write_register(transceiver.RegTemp1, &new_value, 0x1);
	reading_temp = 1;
	while(reading_temp){
		read_register(transceiver.RegTemp1, &reading_temp, 0x1);
		reading_temp &= 0x04;	
	}	
}

/*Get the temperature of the transceiver. Sensor must be calibrated*/
uint8_t trans_read_temp(void){
	uint8_t temperature;
	trans_start_temp_measure();
	read_register(transceiver.RegTemp1, &temperature, 0x1);
	return temperature;
}

/*TEST CONFIGURATION FUNCTIONS*/
void trans_set_lna_sensitivity(uint8_t sensitivity);
void trans_set_pll_bandwidth(uint8_t bandwidth);
void trans_set_continuous_dagc(uint8_t dagc);
void trans_set_lowbeta_agc_offset(uint8_t offset);
