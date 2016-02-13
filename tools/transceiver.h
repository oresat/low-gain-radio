/*
	Transceiver header

	Programmed by William Harrington and Michael Mathis
*/
#include <stdbool.h>
#include <stdint.h>

#include "kw0x.h"
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
	uint8_t RegFrfMid; /* RF carrier frequency, Intermediate Bits */
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
	uint8_t RegPreambleMsb; /* Preamble length, MSB */
	uint8_t RegPreambleLsb; /* Preamble length, LSB */
	uint8_t RegSyncConfig; /* Sync Word Recognition control */
	uint8_t RegSyncValue1; /* Sync Word byte 1 */
	uint8_t RegSyncValue2; /* Sync Word byte 2 */
	uint8_t RegSyncValue3; /* Sync Word byte 3 */
	uint8_t RegSyncValue4; /* Sync Word byte 4 */
	uint8_t RegSyncValue5; /* Sync Word byte 5 */
	uint8_t RegSyncValue6; /* Sync Word byte 6 */
	uint8_t RegSyncValue7; /* Sync Word byte 7 */
	uint8_t RegSyncValue8; /* Sync Word byte 8 */
	uint8_t RegPacketConfig1; /* Packet mode settings */
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
	uint8_t RegTemp1; /* Temperature Sensor control */
	uint8_t RegTemp2; /* Temperature readout */
	uint8_t RegTestLna; /* Sensitivity boost */
	uint8_t PDSTST3; /* Test register includes PLL bandwidth */
	uint8_t RegTestDagc; /* Fading margin improvement */
	uint8_t RegTestAfc; /* AFC offset for low modulation index AFC */
	uint8_t RegTest; /* Internal test registers */
};


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


/*Operating Modes - trans_set_op_mode function
-------------------------------------------------*/
#define SLEEP_MODE 0
#define STAND_BY_MODE 1
#define FS_MODE 2
#define TRANSMIT_MODE 3
#define RECEIVE_MODE 4

/*Data Modulation - mode_config struct
-------------------------------------------------*/
#define PACKET_MODE 0			/*Packet mode*/
#define CONT_WITH_BIT_SYNC 2	/*Continuous mode with bit sync*/
#define CONT_WITHOUT_BIT_SYNC 3 /*Continuous mode without bit sync*/

#define FSK_MODULATION 0
#define OOK_MODULATION 1

#define NO_SHAPING 0			
#define GAUS_BT_1_0	1 /*BT = 1.0*/
#define GAUS_BT_0_5 2 /*BT = 0.5*/
#define GAUS_BT_0_3 3 /*BT = 0.3*/
#define OOK_BR_CUTOFF 1 /*Filtering with freq cutoff = BR*/
#define	OOK_2BR_CUTOFF 2 /*Filtering with freq cutoff = 2 * BR */

/*Auto Modes - set_automode_*****_cond functions
-------------------------------------------------*/
#define NONE 0
#define RISING_FIFONOTEMPTY 1
#define RISING_FIFOLEVEL 2
#define RISING_CRCOK 3
#define RISING_PAYLOADREADY 4
#define RISING_SYNCADDRESS 5
#define RISING_PACKETSENT 6
#define FALLING_FIFONOTEMPTY_ENTER 7

#define FALLING_FIFONOTEMPTY_EXIT 1

#define AUTO_SLEEP_MODE 0
#define AUTO_STAND_BY_MODE 1
#define AUTO_RECEIVE_MODE 2
#define AUTO_TRANSMIT_MODE 3

/*
-------------------------------------------------*/

struct mod_config {
	uint8_t data_mode; /*2 bits*/
	uint8_t mod_type; /*2 bits*/
	uint8_t mod_shaping; /*2 bits*/
};

/*Page 110 of referenc manual*/
struct listen_config {
	uint8_t idle_time_res;
	uint8_t receive_time_res;
	uint8_t listen_criteria;
	uint8_t listen_end;
	uint8_t idle_coef;
	uint8_t receive_coef;
};

struct sync_config {
	uint8_t fifo_fill_cond;
	uint8_t sync_word_size; /* sync_word_size + 1 bytes */
	uint8_t sync_error_toleration;
	uint8_t * sync_word;
};

/*Page 118 of referenc manual*/
struct packet_config {
	uint16_t preamble_size;
	uint8_t packet_format;
	uint8_t dc_free;
	uint8_t crc_check;
	uint8_t crc_auto_clear;
	uint8_t address_filtering;
	uint8_t payload_length;
	uint8_t node_address;
	uint8_t broadcast_address;
	uint8_t tx_start_cond;
	uint8_t fifo_threshold;
	uint8_t inter_packet_rxdelay;
	uint8_t auto_rx_restart;

};
void configure_transceiver(void);
void read_register(uint8_t address, uint8_t * buffer, uint8_t length);
void write_register(uint8_t address, uint8_t * buffer, uint8_t length);
void trans_set_op_mode(uint8_t mode);
void trans_set_data_mod(struct mod_config * config);
void trans_calibrate_rc(void);
bool trans_read_low_bat(void);
void trans_enable_battery_mon(void);
void trans_disable_battery_mon(void);
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
void trans_set_lowbat_thresh(uint8_t threshold);
void trans_enable_listen(void);
void trans_disable_listen(uint8_t new_mode);
void trans_config_listen(struct listen_config * config);
void trans_set_pa_output(uint8_t power);
void trans_set_pa_ramp(uint8_t ramp_speed); /*In FSK mode*/
void trans_enable_ocp(void);
void trans_disable_ocp(void);
void trans_set_ocp_trim(uint8_t trim_value);
void trans_enable_aes(void);
void trans_disable_aes(void);
void trans_set_aes_key(uint8_t * buffer); /*16 bytes*/
void trans_set_automode_enter(uint8_t enter_cond);
void trans_set_automode_exit(uint8_t exit_cond);
void trans_set_automode_intermed(uint8_t intermed_cond);
//cf
//sync
void trans_start_temp_measure(void);
uint8_t trans_read_temp(void);
void trans_set_lna_sensitivity(uint8_t sensitivity);
void trans_set_pll_bandwidth(uint8_t bandwidth);
void trans_set_continuous_dagc(uint8_t dagc);
void trans_set_lowbeta_agc_offset(uint8_t offset);