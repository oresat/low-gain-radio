/*
	Utility for dealing with pins on associated KW0x port

	Programmed by William Harrington, Theo Hill
 */
#include "kw0x.h"

/* struct for pin selection */
struct pin {
	volatile struct port * port; /* port module */
	uint8_t pin; /* pin on port module */
};

struct pin_assign {
	volatile void * module;
	struct pin pin;
	int alt;
};

void set_pin_alt(const struct pin_assign list[], volatile void * module, const struct pin * pin);
