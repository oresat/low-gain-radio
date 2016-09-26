#ifndef _ADC_H_
#define _ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "clocks.h"

void adc_init(void);
uint16_t adc_sample(void);

#endif
