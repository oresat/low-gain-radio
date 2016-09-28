/*!
 * \file    led.h
 * \brief   LED helper functions
 *
 * \addtogroup uart
 * @{
 */


#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>
#include <stdint.h>
#include "port.h"

enum led_mode {ON, OFF, TOGGLE};

struct LED
{
	volatile struct gpio * gpio;
	uint32_t pin;
	bool active_level;
};
void led_action(enum led_mode , struct LED );

//extern struct LED led5 ;
//extern struct LED led6 ;
extern struct LED led7 ;
//extern struct LED led8 ;
extern struct LED green ;
extern struct LED red   ;
extern struct LED blue  ;

#endif

/*! @} */
