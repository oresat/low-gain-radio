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
	configure_transceiver(Mode_TX, PAOutputCfg(PA1, 0));

	/* Due to a hardware error, DIO0 is hooked to RF reset, but goes high on 
	 * packet transmit, leading to as soon as the transmitter starting to send
	 * it resets itself
	 */
	uint8_t DIOMapping = 0x80;
	trans_write_register(transceiver.RegDioMapping1, &DIOMapping, 1);

	/* turn on LNA and PA */
	GPIOB.PTOR = PTB1;
	GPIOB.PTOR = PTB0;

	uint8_t tx = 0x55;
	while(1) {
		trans_write_register(transceiver.RegFifo, &tx, 1);

		for(uint32_t i = 0; i < 1000000; ++i);

		/* toggle LED connected to PTB2 */
		GPIOC.PTOR = PTC1;
	}
	return 0;
}
