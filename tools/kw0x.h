
#ifndef _KW0X_H_
#define _KW0X_H_
#include <stdint.h>

#define  PASTE(a, b) _PASTE(a, b)
#define _PASTE(a, b) a ## b

#define PAD_BYTES(bytes)  const uint8_t PASTE(__PAD, __COUNTER__)[bytes] \
  __attribute__((deprecated("Padding must never be accessed")))

#define PACKED __attribute__((packed))

struct PORT {
	uint32_t PCR[32];
	uint32_t GPCLR; // Write only
	uint32_t GPCHR; // Write only
	PAD_BYTES(24);
	uint32_t ISFR;  // W1C?
} PACKED;

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
} PACKED;

#define GPIOA (*((volatile struct GPIO *) 0x400FF000))
#define GPIOB (*((volatile struct GPIO *) 0x400FF040))
#define GPIOC (*((volatile struct GPIO *) 0x400FF080))
#define GPIOD (*((volatile struct GPIO *) 0x400FF0C0))
#define GPIOE (*((volatile struct GPIO *) 0x400FF100))

struct OSC {
	uint8_t CR;
} PACKED;

#define OSC0 (*((volatile struct OSC *) 0x40065000))

struct SIM_t {
	uint32_t SOPT1;
	PAD_BYTES(4096);
	uint32_t SOPT2;
	PAD_BYTES(4);
	uint32_t SOPT4;
	uint32_t SOPT5;
	PAD_BYTES(4);
	uint32_t SOPT7;
	PAD_BYTES(8);
	uint32_t SDID;
	PAD_BYTES(12);
	uint32_t SCGC4;
	uint32_t SCGC5;
	uint32_t SCGC6;
	uint32_t SCGC7;
	uint32_t CLKDIV1;
	PAD_BYTES(4);
	uint32_t FCFG1;
	uint32_t FCFG2;
	PAD_BYTES(4);
	uint32_t UIDMH;
	uint32_t UIDML;
	uint32_t UIDL;
	PAD_BYTES(156);
	uint32_t COPC;
	uint32_t SRVCOP;
} PACKED;

#define SIM (*((volatile struct SIM_t *) 0x40047000))


struct MCG_t {
	uint8_t C1;
	uint8_t C2;
	uint8_t C3;
	uint8_t C4;
	uint8_t C5;
	uint8_t C6;
	uint8_t S;
	PAD_BYTES(1);
	uint8_t SC;
	PAD_BYTES(1);
	uint8_t ATCVH;
	uint8_t ATCVL;
	uint8_t C7;
	uint8_t C8;
	PAD_BYTES(1);
	uint8_t C10;
} PACKED;

#define MCG (*((volatile struct MCG_t *) 0x40064000))

#undef PASTE
#undef _PASTE
#undef PAD_BYTES
#undef PACKED
#endif
