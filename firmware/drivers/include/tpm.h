/*!
 * \file    tpm.h
 * \brief   TPM Peripheral API 
 *
 * \addtogroup tpm_peripheral
 * @{
 */

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

extern uint32_t         tpm_clock_input;

#define TPM_TEST true

// TPM0 Status control register
#define TPM0_PS                     (0b000 << 0)
#define TPM0_CMOD                   (0b01  << 3)
#define TPM0_SC                     (TPM0_CMOD | TPM0_PS)

#define TPM0_TOIE                   (0b1   << 6)
#define TPM0_TOIE_MASK              (~(0b1   << 6))

// TPM0 Configuration
#define TPM0_DBGMODE                 (0b11    << 6)  //  Debug mode
#define TPM0_CONF_LGR                (TPM0_DBGMODE)

// TPM Status
#define TPM_STATUS_TOF              0b11111111
#define TPM_SC_TOF                  (1 << 7)
#define TPM_C0SC_CHF                (11 << 6)

#define TPM_SC_DISABLE 0b00000000
#define TPM_SC_SET_CMOD (01 << 3)

void isr_tpm0(void)   __attribute__((interrupt("IRQ")));

void tpm0_init(bool );
void wait_n_ms(uint32_t );
#ifdef TPM_TEST
void tpm0_test_loop(void);
#endif

#endif

/*! @} */
