#ifndef _TPM_H_
#define _TPM_H_

#include <stdbool.h>
#include <stdint.h>

#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"
#include "ringbuffer.h"
#include "port.h"

extern uint32_t     	tpm_clock_input;

#define TPM_SC	0b1001000
#define TPM_MOD_INIT	0b1111111111111111
#define TPM_CNT_RESET	0
#define TPM_CONF	0b1000000000100000000011000000
#define TPM_SC_TOF	(1 << 7)

void isr_tpm0(void)   __attribute__((interrupt("IRQ")));

void reset_counter(void);
void tpm_mod_init(void);
void tpm_sc_init(void);
void tpm_conf_init(void);
void tpm_init(void);

#endif
