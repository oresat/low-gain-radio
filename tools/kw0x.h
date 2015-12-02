
#ifndef _KW0X_H_
#define _KW0X_H_
#include <stdint.h>

struct PORT {
	uint32_t PCR0;
	uint32_t PCR1;
	uint32_t PCR2;
	uint32_t PCR3;
	uint32_t PCR4;
	uint32_t PCR5;
	uint32_t PCR6;
	uint32_t PCR7;
	uint32_t PCR8;
	uint32_t PCR9;
	uint32_t PCR10;
	uint32_t PCR11;
	uint32_t PCR12;
	uint32_t PCR13;
	uint32_t PCR14;
	uint32_t PCR15;
	uint32_t PCR16;
	uint32_t PCR17;
	uint32_t PCR18;
	uint32_t PCR19;
	uint32_t PCR20;
	uint32_t PCR21;
	uint32_t PCR22;
	uint32_t PCR23;
	uint32_t PCR24;
	uint32_t PCR25;
	uint32_t PCR26;
	uint32_t PCR27;
	uint32_t PCR28;
	uint32_t PCR29;
	uint32_t PCR30;
	uint32_t PCR31;
	uint32_t GPCLR; // Write only
	uint32_t GPCHR; // Write only
	const uint32_t _PAD[7];
	uint32_t ISFR;  // W1C?
};

extern volatile struct PORT * const _PORTA;
extern volatile struct PORT * const _PORTB;
extern volatile struct PORT * const _PORTC;
extern volatile struct PORT * const _PORTD;
extern volatile struct PORT * const _PORTE;
#define PORTA (*_PORTA)
#define PORTB (*_PORTB)
#define PORTC (*_PORTC)
#define PORTD (*_PORTD)
#define PORTE (*_PORTE)

struct GPIO {
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
};

extern volatile struct GPIO * const _GPIOA;
extern volatile struct GPIO * const _GPIOB;
extern volatile struct GPIO * const _GPIOC;
extern volatile struct GPIO * const _GPIOD;
extern volatile struct GPIO * const _GPIOE;
#define GPIOA (*_GPIOA)
#define GPIOB (*_GPIOB)
#define GPIOC (*_GPIOC)
#define GPIOD (*_GPIOD)
#define GPIOE (*_GPIOE)

struct OSC {
	uint8_t CR;
};

extern volatile struct OSC * const _OSC0;
#define OSC0 (*_OSC0);


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

extern volatile struct SIM_t * const _SIM;
#define SIM (*_SIM)

#endif
