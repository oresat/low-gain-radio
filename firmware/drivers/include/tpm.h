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

#define TPM_SC			0b1001000
#define TPM_MOD_INIT	24000000
#define TPM_CNT_RESET	(0 << 16)

#define TPM_SC_TOF		(1 << 7)

void reset_counter(void);
void tpm_mod_init(void);
void tpm_sc_init(void);
void tpm_init(void);

#endif
