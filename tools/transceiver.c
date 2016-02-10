#include "transceiver.h"
void configure_transceiver(void){
	#define write 1
	uint16_t results[6];
	uint16_t OpModeCfg = mask_spi_addr(transceiver.RegOpMode, write, 0x08);

	/* set transceiver op mode to FS mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[0]);

	//Set the carrier frequency to 436.5 assuming transceiver PLL at 32MHz
	
	/* RegFrfMsb */
	uint16_t FrfMsbCfg = mask_spi_addr(transceiver.RegFrfMsb, write, 0x6D);

	/* RegFrfMid */
	uint16_t FrfMidCfg = mask_spi_addr(transceiver.RegFrfMid, write, 0x20);

	/* RegFrfLsb */
	uint16_t FrfLsbCfg = mask_spi_addr(transceiver.RegFrfLsb, write, 0x00);

	/* write configuration to appropriate registers */
	spi_transaction(&SPI0, 1, &FrfMsbCfg, &results[1]);
	spi_transaction(&SPI0, 1, &FrfMidCfg, &results[2]);
	spi_transaction(&SPI0, 1, &FrfLsbCfg, &results[3]);

	/* turn modulation to on-off keying */
	uint16_t RegDataModulCfg = mask_spi_addr(transceiver.RegDataModul, write, 0x68);
	spi_transaction(&SPI0, 1, &RegDataModulCfg, &results[4]);

	/* Set transceiver to transmit mode by writing to op mode register */
	OpModeCfg = mask_spi_addr(transceiver.RegOpMode, write, 0x0C);

	/* set transceiver op mode to transmit mode */
	spi_transaction(&SPI0, 1, &OpModeCfg, &results[5]);

}