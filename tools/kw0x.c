#include "kw0x.h"

volatile struct PORT * const _PORTA = (struct PORT *) 0x40049000;
volatile struct PORT * const _PORTB = (struct PORT *) 0x4004A000;
volatile struct PORT * const _PORTC = (struct PORT *) 0x4004B000;
volatile struct PORT * const _PORTD = (struct PORT *) 0x4004C000;
volatile struct PORT * const _PORTE = (struct PORT *) 0x4004D000;

volatile struct GPIO * const _GPIOA = (struct GPIO *) 0x400FF000;
volatile struct GPIO * const _GPIOB = (struct GPIO *) 0x400FF040;
volatile struct GPIO * const _GPIOC = (struct GPIO *) 0x400FF080;
volatile struct GPIO * const _GPIOD = (struct GPIO *) 0x400FF0C0;
volatile struct GPIO * const _GPIOE = (struct GPIO *) 0x400FF100;

volatile struct OSC * const _OSC0 = (struct OSC *) 0x40065000;

volatile struct SIM_t * const _SIM = (struct SIM_t *) 0x40047000;
