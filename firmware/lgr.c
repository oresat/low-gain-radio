/*
	Low Gain Radio firmware

	Programmed by William Harrington
*/
#include "transceiver.h"
#include "clksetup.h"
#include "uart.h"

#define PAYLOAD_READY_MASK 0x04

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

void initialize_uart0(void){
	/* UART0 configuration */
	struct uart_config myUART = {
		/* pin for transmit = PTA2 */
		.TX = {.port=&PORTA, .pin=2,},

		/* pin for receive = PTA1 */
		.RX = {.port=&PORTA, .pin=1,},

		/* baud rate */
		.baud = 9600,
	};
	uart_init(&UART0, &myUART);
}

int main(void) {
	/* check transceiver mode */
	uint8_t trans_mode = Mode_TX;
	

	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();
	initialize_uart0();

	

	/* Due to a hardware error, DIO0 is hooked to RF reset, but goes high on 
	 * packet transmit, leading to as soon as the transmitter starting to send
	 * it resets itself
	 */
	uint8_t DIOMapping = 0x80;
	trans_write_register(transceiver.RegDioMapping1, &DIOMapping, 1);

	
	
	static uint8_t standby = 0x4;

	if(trans_mode == Mode_TX){
		/* enable PA */
		GPIOB.PTOR = PTB1;
		/* Enable LNA in order to power inverter on rx/tx switch*/
		GPIOB.PTOR = PTB0;

		configure_transceiver(Mode_TX, PAOutputCfg(PA1, 0));
		/* Enter standby mode*/
		trans_write_register(transceiver.RegOpMode, &standby, 1); 

		
    }
	if(trans_mode == Mode_RX){
		/* Enable LNA */
		GPIOB.PTOR = PTB0;
		/* Enter receive mode */
		trans_write_register(transceiver.RegOpMode, &trans_mode, 1); 
		/* this function is in transceiver.c if you want more details */

		configure_transceiver(Mode_RX, PAOutputCfg(0, 0));
    }

    /*

	Be sure that trans_mode is Mode_RX or Mode_TX so that the appropriate
	branch is taken in the while loop. The actual opmode may be different.
		
    */
    
	uint8_t tx = 0x44;
	static uint8_t rx[PACKET_LENGTH];
	
	uint8_t alive = 0x7;
	uint8_t sleep = 0x4;
	
	static uint8_t payload_ready[2];

	static uint8_t txbytes[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD};

	static uint8_t test = 0;
	static uint8_t one = 0x1;

/*

	while(1){

		for(uint32_t i = 0; i < 500000; ++i){
			trans_read_register(transceiver.RegIrqFlags1, &test, 1);
			if (test & 0x8){
				GPIOC.PSOR = PTC2;
			}
			else{
				GPIOC.PCOR = PTC2;
			}
		}

		trans_write_register(transceiver.RegRssiConfig, &one, 1);
		uint8_t rssi_done = 0;
		while (!(rssi_done & 0x2)){
			trans_read_register(transceiver.RegRssiConfig, &rssi_done, 1);
		}
		trans_read_register(transceiver.RegRssiValue, &test, 1);
		if (test){
		GPIOC.PTOR = PTC2;
		}
	}*/
	

	


	while(1) {
		

		/* transmit byte if in TX mode */
		if(trans_mode == Mode_TX){

			/* write to transceiver fifoe to transmit data */
			trans_write_register(transceiver.RegFifo, txbytes, PACKET_LENGTH);
			
			
			/* blink status LED */
			GPIOC.PTOR = PTC1;
			for(uint32_t i = 0; i < 5000000; ++i);
			/* transmit byte written over UART for debugging */
			//uart_write(&UART0, 1, &tx);
        }

		/* check fifo for received bytes in RX mode */
		if(trans_mode == Mode_RX){
			uart_write(&UART0, 1, &alive); //I'm alive signal for the sys controller
				

			

			for(uint32_t i = 0; i < 500000; ++i);	
			
			/* blink status LED */
			GPIOC.PTOR = PTC4;

			/*Check if the payload is ready*/
			trans_read_register(transceiver.RegIrqFlags1, payload_ready, 2);

			//trans_read_register(transceiver.RegRssiValue, &trans_mode, 1);

			if (payload_ready[1] & 0x40){
				GPIOC.PSOR = PTC1;
			}
			else{
				GPIOC.PCOR = PTC1;
			}

			if (payload_ready[1] & 0x04){
				GPIOC.PSOR = PTC2;
			}
			else{
				GPIOC.PCOR = PTC2;
			}


			
			if (payload_ready[1] & 0x04){

				/* read transceiver fifo to grab received data */
				trans_read_register(transceiver.RegFifo, rx, PACKET_LENGTH);	
				/* Write the packet received out to UART */
				uart_write(&UART0, PACKET_LENGTH, rx);		
				/* Packet received LED toggle */
				GPIOC.PTOR = PTC3;
			}
        }
	}
	return 0;
}
