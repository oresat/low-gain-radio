#include <stdbool.h>

#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"
#include "lgr_util.h"

#include "led.h"
#include "clocks.h"
#include "ringbuffer.h"
#include "em-printf.h"

#include "tpm.h"
#define TPM0_MOD_1uS_at_24Mhz       23 * 100
#define TPM0_MOD_1mS_at_24Mhz       23999

static bool debug_isr_count = 0;
static bool tpm0_count_flag = false;

void isr_tpm0(void)
{
	debug_isr_count++;
	if(debug_isr_count % 1000000)
	{
		led_action(TOGGLE, blue);
	}

	//read TOF register, if bit in tfo is set, then proceed.
	if ((TPM0.SC & TPM_SC_TOF) != 0)
	{
		reset_tof();
		tpm0_count_flag  = true;
	}
	else
	{
		return;
	}
}

void tpm0_mod_1us(void)
{
	// word or halfword access only
	__STR(TPM0_MOD_1uS_at_24Mhz, &TPM0.MOD);
}

void tpm0_mod_1ms(void)
{
	// word or halfword access only
	__STR(TPM0_MOD_1mS_at_24Mhz, &TPM0.MOD);
}

void reset_tof()
{
	TPM0.C0SC |= TPM_C0SC_CHF;
	TPM0.STATUS |= TPM_STATUS_TOF;
	TPM0.SC |= TPM_SC_TOF;
}

void disable_tpm()
{
	TPM0.SC &= TPM_SC_DISABLE;
}

void tpm0_enable_int()
{
	TPM0.SC |= TPM0_TOIE;
}

void tpm0_disable_int(void)
{
	TPM0.SC &= TPM0_TOIE_MASK;
}

void tpm0_sc_init()
{
	TPM0.SC   = TPM0_SC;
}
void tpm0_conf_init()
{
	TPM0.CONF = TPM0_CONF_LGR;
	TPM0.C0SC = (0b01 << 4); // software compare
}

void tpm0_init()
{
	//led_action(TOGGLE, green);
	NVIC_EnableIRQ(TPM0_IRQn);
	__enable_irq();
	enable_tpm_mcg_clock();
	tpm0_conf_init();
	led_action(ON, red);
	tpm0_mod_1ms();
	led_action(OFF, red);
	tpm0_sc_init();
	tpm0_enable_int();
	tpm0_count_flag  = false;
}

void    tpm0_test_loop()
{
	uint32_t tpm0_count = 0;
	led_action(OFF, blue);
	led_action(OFF, green);
	led_action(OFF, red);
	while(1)
	{
		if(tpm0_count_flag)
		{
			led_action(TOGGLE, blue);
			tpm0_count++;
			tpm0_count_flag = false;
			if ((tpm0_count != 0) && ((tpm0_count % 1000) == 0))
			{
				led_action(TOGGLE, red);
				printf("tic\t%d\r\n", tpm0_count);
			}
		}
	}
}

