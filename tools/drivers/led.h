#ifndef _LED_H_
#define _LED_H_
#include <stdbool.h>
#include "port.h"

enum mode {ON, OFF, TOGGLE};

struct LED {
	volatile struct gpio * gpio;
	uint32_t pin;
	bool active_level;
};

void led(enum mode mode, struct LED led);

#endif
