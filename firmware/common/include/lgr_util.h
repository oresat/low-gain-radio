/*! \file lgr_util.h
 */

#ifndef _LGR_UTIL_H_
#define _LGR_UTIL_H_

#include <stdint.h>
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#define         MAX_VERSION_CHARS       100
extern char LGR_GITVERSION[MAX_VERSION_CHARS];

/**
  \brief   STR (32 bit)
  \details Executes a STR instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    ptr  Pointer to location
 */
__attribute__((always_inline)) __STATIC_INLINE void __STR(uint32_t value, volatile uint32_t * ptr)
{
	__ASM volatile ("str %1, %0" : "=Q" (*ptr) : "r" (value) );
}

void lgr_version(char * v);

void after_POR_pause(void);

char* util_itoa(int value, char* result, int base) ;
char * util_uitoa(uint32_t value, char * result, uint8_t base ) ;
uint16_t kr_strlen(char * s);

uint8_t fromHexChar(uint8_t ascii) ;
uint8_t fromHex(uint8_t * ascii) ;

void toHex(uint8_t * dest, uint8_t byte);

#endif
