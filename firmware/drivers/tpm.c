#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#include "led.h"
#include "clocks.h"
#include "ringbuffer.h"

#include "tpm.h"

void isr_tpm0(void)
{
	//read TOF register, if bit in tfo is set, then proceed.
	if (TPM0.SC & TPM_SC_TOF)
	{
		reset_counter();
		//toggle io pin
		//GPIOB.PTOR = PTE0;
		//reset TOF bit
		led_action(TOGGLE, green);
	}
	else return;
}

void reset_counter()
{
	//write anything to counter register to clear it
	TPM0.CNT = 1;
}

void tpm_mod_init()
{
	TPM0.MOD = TPM_MOD_INIT;
}

void tpm_sc_init()
{
	TPM0.SC = TPM_SC;
}
void tpm_conf_init()
{
	TPM0.CONF = TPM_CONF;
}


void tpm_init()
{
	enable_tpm_mcg_clock();
	tpm_conf_init();
	tpm_mod_init();
	tpm_sc_init();
	
	
	
	
}
