/*!
 * \file    led.c
 * \brief   LED 
 *
 * \defgroup led
 * @{
 */


#include "led.h"


/*struct LED led5 =
{
	.gpio = &GPIOC,
	.pin = PTC1,
	.active_level = 1
};

struct LED led6 =
{
	.gpio = &GPIOC,
	.pin = PTC2,
	.active_level = 1
};

struct LED led7 =
{
	.gpio = &GPIOC,
	.pin = PTC3,
	.active_level = 1
};

struct LED led8 =
{
	.gpio = &GPIOC,
	.pin = PTC4,
	.active_level = 1
};
*/

struct LED green =
{
	.gpio = &GPIOB,
	.pin = PTB1,
	.active_level = 0
};

struct LED red =
{
	.gpio = &GPIOB,
	.pin = PTB2,
	.active_level = 0
};

struct LED blue =
{
	.gpio = &GPIOB,
	.pin  = PTB17,
	.active_level = 0
};

void led_action(enum led_mode mode, struct LED led)
{
	volatile uint32_t * psor = &(led.gpio->PSOR);
	volatile uint32_t * pcor = &(led.gpio->PCOR);
	volatile uint32_t * ptor = &(led.gpio->PTOR);
	volatile uint32_t * action;

	switch(mode)
	{
		case ON:
			action = led.active_level ? psor : pcor;
			break;
		case OFF:
			action = led.active_level ? pcor : psor;
			break;
		case TOGGLE:
			action = ptor;
			break;
		default:
			action = pcor;
			break;
	}
	*action = led.pin;
}

/*! @} */
