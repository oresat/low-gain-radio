/*! \file tpm.c
 * \brief   TPM Peripheral
 *
 * \defgroup tpm_peripheral
 * @{
 */

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

#define TPM0_MOD_50uS_at_24Mhz       1199
#define TPM0_MOD_100uS_at_24Mhz      2399
#define TPM0_MOD_250uS_at_24Mhz      5999
#define TPM0_MOD_500uS_at_24Mhz      11999
#define TPM0_MOD_1mS_at_24Mhz        23999

static bool     debug_isr_count  = 0;
static bool     tpm0_count_flag  = false;

static uint32_t TPM0_MOD_PERIOD  = TPM0_MOD_1mS_at_24Mhz;

static void reset_tof(void)
{
	TPM0.C0SC |= TPM_C0SC_CHF;
	TPM0.STATUS |= TPM_STATUS_TOF;
	TPM0.SC |= TPM_SC_TOF;
}


void isr_tpm0(void)
{
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

/*! High accuracy interrupts from timer0 ISR
 */
static void tpm0_mod_50us(void)
{
	TPM0_MOD_PERIOD = TPM0_MOD_50uS_at_24Mhz;
	// word or halfword access only
	__STR(TPM0_MOD_50uS_at_24Mhz, &TPM0.MOD);
}

static void tpm0_mod_1ms(void)
{
	TPM0_MOD_PERIOD = TPM0_MOD_1mS_at_24Mhz;
	// word or halfword access only
	__STR(TPM0_MOD_1mS_at_24Mhz, &TPM0.MOD);
}
static void disable_tpm(void)
{
	TPM0.SC &= TPM_SC_DISABLE;
}

static void tpm0_enable_int(void)
{
	TPM0.SC |= TPM0_TOIE;
}

static void tpm0_disable_int(void)
{
	TPM0.SC &= TPM0_TOIE_MASK;
}

static void tpm0_sc_init(void)
{
	TPM0.SC   = TPM0_SC;
}

static void tpm0_conf_init(void)
{
	TPM0.CONF = TPM0_CONF_LGR;
	TPM0.C0SC = (0b01 << 4); // software compare
}

/*!
 *  \warning Must run: tpm0_enable_int() to use tpm0 isr
 */
void tpm0_init(bool highres)
{
	__disable_irq();
	NVIC_EnableIRQ(TPM0_IRQn);

	enable_tpm_clocks();
	tpm0_conf_init();
	if(highres)
	{
		tpm0_mod_50us();
	}
	else
	{
		tpm0_mod_1ms();
	}
	tpm0_sc_init();
	tpm0_count_flag  = false;

	__enable_irq();
}

/*!
 * Enable the ISR and wait for integer n number of milliseconds
 *
 */
void wait_n_ms(uint32_t n)
{
	if(TPM0_MOD_PERIOD == TPM0_MOD_1mS_at_24Mhz)
	{
		// write the count register to clear it
		TPM0.CNT = 0;
		tpm0_enable_int();
		for(uint32_t tpm0_count = 0; tpm0_count < n; )
		{
			if(tpm0_count_flag)
			{
				led_action(TOGGLE, blue);
				tpm0_count++;
				tpm0_count_flag = false;
			}
		}
	}
	else if (TPM0_MOD_PERIOD == TPM0_MOD_50uS_at_24Mhz)
	{
		// write the count register to clear it
		TPM0.CNT = 0;
		tpm0_enable_int();
		for(uint32_t tpm0_count = 0; tpm0_count < n * 20; )
		{
			if(tpm0_count_flag)
			{
				led_action(TOGGLE, blue);
				tpm0_count++;
				tpm0_count_flag = false;
			}
		}

	}
	else
	{
		#ifdef TPM_TEST
		printf("TPM0_MOD_PERIOD undefined");
		#endif
		while(1)
		{
			;
		}
	}
	tpm0_disable_int();
}

#ifdef TPM_TEST
void tpm0_test_loop()
{
	led_action(OFF, blue);
	led_action(OFF, red);
	led_action(OFF, green);
	while(1)
	{
		wait_n_ms(500);
		led_action(TOGGLE, green);
		printf("*");
	}
}
#endif

/*! @} */
