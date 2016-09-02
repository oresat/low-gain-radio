/* \file v1_1.c
 */

#include <stdint.h>
#include "v1_1.h"


/* Board specific hacks might show up here */

/*
 * Simple minded way to keep track of which board we are targeting 
 */
const char _lgr_version[10] =  "1.1";

/* UART */
uint32_t uart_clock_input=UART_INPUT_CLOCKSPEED;

/* TPM */
uint32_t tpm_clock_input=TPM_INPUT_CLOCKSPEED;
