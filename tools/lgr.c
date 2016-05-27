/*
	Low Gain Radio firmware

	Programmed by William Harrington
*/
#include "transceiver.h"
#include "clksetup.h"

/* LNA Enable */
#define PTB0 (1 << 0)

/* PA Enable */
#define PTB1 (1 << 1)

/* RF Reset */
#define PTE2 (1 << 2)

/* LED5 */
#define PTC1 (1 << 1)

/* LED6 */
#define PTC2 (1 << 2)

/* LED7 */
#define PTC3 (1 << 3)

/* LED8 */
#define PTC4 (1 << 4)

/* alternative function number */
#define pin_disable (0 << 8)
#define alt1 (1 << 8)
#define alt2 (2 << 8)
#define alt3 (3 << 8)
#define alt4 (4 << 8)
#define alt5 (5 << 8)
#define alt6 (6 << 8)
#define alt7 (7 << 8)

void initialize_gpio(void){

	/* port B pins */
	PORTB.PCR[0] |= alt1;
	PORTB.PCR[1] |= alt1;

	/* port C pins */
	PORTC.PCR[1] |= alt1;
	PORTC.PCR[2] |= alt1;
	PORTC.PCR[3] |= alt1;
	PORTC.PCR[4] |= alt1;

	PORTE.PCR[2] |= alt1;

	/* set data direction as output */
	GPIOB.PDDR |= PTB1 | PTB0;
	GPIOC.PDDR |= PTC4 | PTC3 | PTC2 | PTC1;
	GPIOE.PDDR |= PTE2;

	GPIOE.PCOR = PTE2;
	return;
}

int main(void) {
	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();

	/* this function is in transceiver.c if you want more details */
	configure_transceiver(Mode_RX, PAOutputCfg(PA1, 0));

	/* Due to a hardware error, DIO0 is hooked to RF reset, but goes high on 
	 * packet transmit, leading to as soon as the transmitter starting to send
	 * it resets itself
	 */
	uint8_t DIOMapping = 0x80;
	trans_write_register(transceiver.RegDioMapping1, &DIOMapping, 1);


	/* check transceiver mode */
	uint8_t trans_mode;
	trans_read_register(transceiver.RegOpMode, &trans_mode, 1);

	if(trans_mode == Mode_TX){
		/* enable PA */
		GPIOB.PTOR = PTB1;
        }
	if(trans_mode == Mode_RX){
		/* Enable LNA */
		GPIOB.PTOR = PTB0;
        }

	uint8_t tx = 0x55;
	uint8_t rx;

	while(1) {

		/* transmit byte if in TX mode */
		if(trans_mode == Mode_TX){
			trans_write_register(transceiver.RegFifo, &tx, 1);
			GPIOC.PTOR = PTC1;
                }

		/* check fifo for received bytes in RX mode */
		if(trans_mode == Mode_RX){
			trans_read_register(transceiver.RegFifo, &rx, 1);
			GPIOC.PTOR = PTC2;

			/* if we received 0x55 toggle LED */
			if(rx == 0x55){
				GPIOC.PTOR = PTC3;
			}
                }

		for(uint32_t i = 0; i < 1000000; ++i);

	}
	return 0;
}
