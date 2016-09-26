#include "adc.h"

#define ADC0_DM1 0x5
#define ADC0_DP2 0x2
#define ADC0_SC2_ADACT_MASK (1 << 7)
#define ADC0_SC1A_COCO_MASK (1 << 7)
#define BIT_MODE_16 0xC
#define ADC_DISABLE 0x1F

void adc_init(void){
	enable_adc_clock();
	ADC.CFG1 |= BIT_MODE_16;
	ADC.SC1A |= ADC_DISABLE;
}

uint16_t adc_sample(void){
	/* select ADC channel, starts conversion */
	ADC.SC1A |= ADC0_DM1;

	/* conversion in progress */
	if(ADC.SC2 & ADC0_SC2_ADACT_MASK){
		/* wait for it to finish */
		while(ADC.SC1A & ADC0_SC1A_COCO_MASK);
		return ADC.RA;
        }
	else return 0;
}
