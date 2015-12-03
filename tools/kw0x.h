
#ifndef _KW0X_H_
#define _KW0X_H_
#include <stdint.h>

struct PORT {
	uint32_t PCR[32];
	uint32_t GPCLR; // Write only
	uint32_t GPCHR; // Write only
	const uint32_t _PAD[7];
	uint32_t ISFR;  // W1C?
};

#define PORTA (*((volatile struct PORT *) 0x40049000))
#define PORTB (*((volatile struct PORT *) 0x4004A000))
#define PORTC (*((volatile struct PORT *) 0x4004B000))
#define PORTD (*((volatile struct PORT *) 0x4004C000))
#define PORTE (*((volatile struct PORT *) 0x4004D000))

struct GPIO {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
};

#define GPIOA (*((volatile struct GPIO *) 0x400FF000))
#define GPIOB (*((volatile struct GPIO *) 0x400FF040))
#define GPIOC (*((volatile struct GPIO *) 0x400FF080))
#define GPIOD (*((volatile struct GPIO *) 0x400FF0C0))
#define GPIOE (*((volatile struct GPIO *) 0x400FF100))

struct OSC {
	uint8_t CR;
};

#define OSC0 (*((volatile struct OSC *) 0x40065000))

struct SIM_t {
	uint32_t SOPT1;
	uint32_t _PAD0[1024];
	uint32_t SOPT2;
	uint32_t _PAD1[1];
	uint32_t SOPT4;
	uint32_t SOPT5;
	uint32_t _PAD2[1];
	uint32_t SOPT7;
	uint32_t _PAD3[2];
	uint32_t SDID;
	uint32_t _PAD4[3];
	uint32_t SCGC4;
	uint32_t SCGC5;
	uint32_t SCGC6;
	uint32_t SCGC7;
	uint32_t CLKDIV1;
	uint32_t _PAD5[1];
	uint32_t FCFG1;
	uint32_t FCFG2;
	uint32_t _PAD6[1];
	uint32_t UIDMH;
	uint32_t UIDML;
	uint32_t UIDL;
	uint32_t _PAD7[39];
	uint32_t COPC;
	uint32_t SRVCOP;
};

#define SIM (*((volatile struct SIM_t *) 0x40047000))

#endif
