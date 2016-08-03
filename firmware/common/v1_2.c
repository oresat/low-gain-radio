/* \file v1_2.c
 */

#include <stdint.h>
#include "v1_2.h"


/* Board specific hacks might show up here */

/*
 * Simple minded way to keep track of which board we are targeting 
 */
const char _lgr_version[10] =  "1.2";

/* UART */
uint32_t uart_clock_input=UART_INPUT_CLOCKSPEED;

/*  */
