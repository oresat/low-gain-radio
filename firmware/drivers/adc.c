#include "adc.h"

#define ADC0_DM1 0x5
#define ADC0_DP2 0x2
#define ADC0_SC2_ADACT_MASK (1 << 7)
#define ADC0_SC1A_COCO_MASK (1 << 7)
#define BIT_MODE_16 0xC
#define ADC_DISABLE 0x1F
#define HW_AVG_EN (1 << 2)
#define HW_AVG_8 (1 << 0)
#define HW_AVG_16 (1 << 1)
#define HW_AVG_32 (3 << 0)
#define ADC0_CAL (1 << 7)
#define ADC0_SC3_CALF_MASK (1 << 6)

static bool adc_calibrate(void){
	uint16_t cal;
        ADC.SC3 |= ADC0_CAL;
	while(ADC.SC3 & ADC0_CAL);
        while(!(ADC.SC1A & ADC0_SC1A_COCO_MASK));
	if(ADC.SC3 & ADC0_SC3_CALF_MASK) return false;
	cal = ADC.CLP0 + ADC.CLP1 + ADC.CLP2 + ADC.CLP3 + ADC.CLP4 + ADC.CLPS;
	cal >>= 1;
	cal |= (1 << 15);
	ADC.PG = cal;
	cal = 0;
	cal = ADC.CLM0 + ADC.CLM1 + ADC.CLM2 + ADC.CLM3 + ADC.CLM4 + ADC.CLMS;
	cal >>= 1;
	cal |= (1 << 15);
	ADC.MG = cal;
	return true;
}

bool adc_init(void){
	enable_adc_clock();
	if(!adc_calibrate()) return false;
	ADC.CFG1 |= BIT_MODE_16;
	ADC.SC1A |= ADC_DISABLE;
        return true;
}

uint16_t adc_sample(void){
	/* select ADC channel, starts conversion */
	ADC.SC1A |= ADC0_DM1;

	/* conversion in progress */
	if(ADC.SC2 & ADC0_SC2_ADACT_MASK){
		/* wait for it to finish */
		while(!(ADC.SC1A & ADC0_SC1A_COCO_MASK));
		return ADC.RA;
        }
	else return 0;
}
