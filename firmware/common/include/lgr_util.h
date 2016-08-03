/*! \file lgr_util.h
 */

#ifndef _LGR_UTIL_H_
#define _LGR_UTIL_H_

#include <stdint.h>

#define         MAX_VERSION_CHARS       100
extern char LGR_GITVERSION[MAX_VERSION_CHARS];

void lgr_version(char * v);

void after_POR_pause(void);

char* util_itoa(int value, char* result, int base) ;
char * util_uitoa(uint32_t value, char * result, uint8_t base ) ;
uint16_t kr_strlen(char * s);

uint8_t fromHexChar(uint8_t ascii) ;
uint8_t fromHex(uint8_t * ascii) ;

void toHex(uint8_t * dest, uint8_t byte);

#endif
