/*
	Low Gain Radio firmware
*/
#include <string.h>

#include "transceiver.h"
#include "clksetup.h"
#include "uart.h"
#include "led.h"

/* LNA */
#define PTB0 (1 << 0)
void LNAEnable(void) {
	GPIOB.PSOR = PTB0;
}
/* PA */
#define PTB1 (1 << 1)
void PAEnable(void) {
	GPIOB.PSOR = PTB1;
}
void PADisable(void) {
	GPIOB.PCOR = PTB1;
}


/* RF Reset */
#define PTE2 (1 << 2)

/* LED5 */
#define PTC1 (1 << 1)
struct LED led5 = {
	.gpio = &GPIOC,
	.pin = PTC1,
	.active_level = 1
};
/* LED6 */
#define PTC2 (1 << 2)
struct LED led6 = {
	.gpio = &GPIOC,
	.pin = PTC2,
	.active_level = 1
};
/* LED7 */
#define PTC3 (1 << 3)
struct LED led7 = {
	.gpio = &GPIOC,
	.pin = PTC3,
	.active_level = 1
};
/* LED8 */
#define PTC4 (1 << 4)
struct LED led8 = {
	.gpio = &GPIOC,
	.pin = PTC4,
	.active_level = 1
};
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

void modeTX(void) {
	// LNA should be off in txonly, but because of a hardware quirk it
	// powers rx/tx switch too and must always be on.
	LNAEnable(); 
	PAEnable();

	/* Due to a hardware error, DIO0 is hooked to RF reset, but goes high on 
	 * packet transmit, leading to as soon as the transmitter starting to send
	 * it resets itself */
	uint8_t DIOMapping = 0x80;
	trans_write_register(transceiver.RegDioMapping1, &DIOMapping, 1);

	configure_transceiver(Mode_TX, PAOutputCfg(PA1, 0));
	/* Enter standby mode*/
	uint8_t standby = 0x4;
	trans_write_register(transceiver.RegOpMode, &standby, 1); 

	uint8_t txbytes[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD};
	uint8_t cmdbytes[PACKET_LENGTH] = {0};
	uint32_t i;
	while(1) {
		uint8_t command;
		if(uart_char(&UART0, &command)){
			memset(cmdbytes, command, PACKET_LENGTH);
			trans_write_register(transceiver.RegFifo, cmdbytes, PACKET_LENGTH);
		}

		/* write to transceiver fifoe to transmit data */
		++i;
		if(i > 1000000) {
			led(TOGGLE, led5);
			trans_write_register(transceiver.RegFifo, txbytes, PACKET_LENGTH);
			i = 0;
		}
	}
}

void modeRX(void) {
	LNAEnable();
	PADisable();
	configure_transceiver(Mode_RX, PAOutputCfg(PA0, 0));
	/* Due to a hardware error, DIO0 is hooked to RF reset, but goes high in 
	 * most rx modes, leading to the receiver resetting itself on receiving a
	 * packet. Set it to CrcOk and make sure CRC checking is off */
	uint8_t DIOMapping = 0x00;
	trans_write_register(transceiver.RegDioMapping1, &DIOMapping, 1);

	uint32_t ledcount = 0;
	uint8_t rxbyte = 0x0;
	uint8_t IrqFlags[2] = {0, 0};
	uint8_t OldFlags[2] = {0xFF, 0xFF};
	while(1) {
		trans_read_register(transceiver.RegIrqFlags1, IrqFlags, 2);
		if (memcmp(IrqFlags, OldFlags, 2)) {
			uint8_t chars[7] = {0, 0, ' ', 0, 0, '\r', '\n'};
			toHex(chars, IrqFlags[0]);
			toHex(chars + 3, IrqFlags[1]);
			uart_write(&UART0, sizeof(chars), chars);
			memcpy(OldFlags, IrqFlags, 2);
		}
		if(IrqFlags[1] & PayloadReady) {
			led(ON, led6);
			uart_write(&UART0, 9, "Payload: ");
			while(IrqFlags[1] & FifoNotEmpty) {
				trans_read_register(transceiver.RegFifo, &rxbyte, 1);
				uint8_t data[3] = {0, 0, ' '};
				toHex(data, rxbyte);
				uart_write(&UART0, sizeof(data), data);
				trans_read_register(transceiver.RegIrqFlags2, &IrqFlags[1], 1);
			}
			uart_write(&UART0, 2, "\r\n");
			led(OFF, led6);
		}
		ledcount += 1;
		if (ledcount > 5000) {
			led(TOGGLE, led5);
			ledcount = 0;
		}
	}
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
	/* call initialization procedures */
	initialize_clock();
	initialize_gpio();
	initialize_uart0();
	uart_write(&UART0, 11, "\r\nRestart\r\n");


	modeTX();
//	modeRX();
}
