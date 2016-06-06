#include "led.h"

void led(enum mode mode, struct LED led) {
	volatile uint32_t * psor = &(led.gpio->PSOR);
	volatile uint32_t * pcor = &(led.gpio->PCOR);
	volatile uint32_t * ptor = &(led.gpio->PTOR);
	volatile uint32_t * action;

	switch(mode) {
	case ON:
		action = led.active_level ? psor : pcor;
		break;
	case OFF:
		action = led.active_level ? pcor : psor;
		break;
	case TOGGLE:
		action = ptor;
		break;
	}
	*action = led.pin;
}
