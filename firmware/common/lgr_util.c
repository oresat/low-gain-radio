/* \file lgr_util.c
 * Utility functions for lgr
 */

#include <string.h>

#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"

#include "lgr_util.h"

char LGR_GITVERSION[MAX_VERSION_CHARS];

/* GIT_COMMIT_VERSION is inserted by the build system, generated in
 * common/kw0x_head.mk
 */
void lgr_version(char * v)
{
	#ifndef GIT_COMMIT_VERSION
#define GIT_COMMIT_VERSION "Unknown"
	#endif
	size_t len;
	len = sizeof(GIT_COMMIT_VERSION);
	if(len < MAX_VERSION_CHARS)
	{
		strncpy(v, GIT_COMMIT_VERSION, len);
	}
}

/* K&R strlen  when string.h not avail. */
uint16_t kr_strlen(char * s)
{
	char * p = s;
	while (*p != '\0')
	{
		p++;
	}
	return p - s;
}

// \todo This is hacky, find a better way, like polling a status line or something.
// xcvr not available for 10ms after POR
void after_POR_pause()
{
	// maybe about 10mS?
	for(uint32_t i = 0; i < 1000000; ++i);
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 * Ref: http://www.strudel.org.uk/itoa/
 */
char * util_itoa(int value, char * result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36)
	{
		*result = '\0';
		return result;
	}

	char * ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do
	{
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	}
	while ( value );

	// Apply negative sign
	if (tmp_value < 0)
	{
		*ptr++ = '-';
	}
	*ptr-- = '\0';
	while(ptr1 < ptr)
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

static inline void _util_strrev(char * sp)
{
	char  t;
	char * d = &(sp[strlen(sp) - 1]);
	while (d > sp)
	{
		t = *sp;
		*sp++ = *d;
		*d-- = t;
	}
}

char * util_uitoa(uint32_t value, char * result, uint8_t base )
{
	if (result != NULL)
	{
		char  * sp   = result;

		if (base < 2 || base > 36)
		{
			*result = '\0';
			return result;
		}
		do
		{
			*sp    = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
			sp++;
			value /= base;
		}
		while (value > 0);
		*sp = '\0';
		_util_strrev(result);
	}
	return(result);
}

uint8_t fromHexChar(uint8_t ascii)
{
	if (ascii >= '0' && ascii <= '9')
	{
		return ascii - '0';
	}
	if (ascii >= 'a' && ascii <= 'f')
	{
		return ascii - 'a' + 10;
	}
	return ascii - 'A' + 10;
}

uint8_t fromHex(uint8_t * ascii)
{
	return (fromHexChar(ascii[0]) << 4) + fromHexChar(ascii[1]);
}

void toHex(uint8_t * dest, uint8_t byte)
{
	if(((byte >> 4) & 0xf)  <= 9)
	{
		dest[0] = '0' + ((byte >> 4) & 0xf);
	}
	else
	{
		dest[0] = '7' + ((byte >> 4) & 0xf);
	}

	if((byte & 0xf) <= 9)
	{
		dest[1] = '0' + (byte & 0xf);
	}
	else
	{
		dest[1] = '7' + (byte & 0xf);
	}
}


