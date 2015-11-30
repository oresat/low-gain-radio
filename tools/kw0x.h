
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


#endif
