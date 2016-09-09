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
		led_action(TOGGLE, blue);
		
		reset_counter();
		reset_tof();
		
		disable_tpm_clocks();
		disable_tpm();
		
		enable_tpm_mcg_clock();
		tpm_sc_init();
	}
	else return;
}

void reset_counter()
{
	//write anything to counter register to clear it
	TPM0.CNT = TPM_CNT_RESET;
}

void tpm_mod_init()
{
	TPM0.MOD = TPM_MOD_INIT;
}

void tpm_mod_1ms()
{
	TPM0.MOD = TPM_MOD_1MS;
}

void reset_tof()
{
	TPM0.C0SC |= TPM_C0SC_CHF;
	TPM0.STATUS |= TPM_STATUS_TOF;
	TPM0.SC |= TPM_SC_TOF;
}

void cycle_tpm()
{
	TPM0.SC = TPM_SC_DISABLE;
	TPM0.SC = TPM_SC;
}

void disable_tpm()
{
	TPM0.SC &= TPM_SC_DISABLE;
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
	//led_action(TOGGLE, green);
	NVIC_EnableIRQ(TPM0_IRQn);
	__enable_irq();
	enable_tpm_mcg_clock();
	tpm_conf_init();
	tpm_mod_1ms();
	tpm_sc_init();
}
