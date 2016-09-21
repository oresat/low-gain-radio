/*! \file em-printf.c
 *
 *  \author: kwilson
 */

/*!
 * \defgroup em-printf Embedded printf routines
 *
 * @{
 */

#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include "v1_1.h"
#include "ringbuffer.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"


#include "lgr_util.h"
#include "uart.h"

#include "em-printf.h"

static char printnumbuff[100];

enum
{
	BIN = 2,
	OCT = 8,
	DEC = 10,
	HEX = 16
};

void em_print_intr(const char * format, va_list args )
{
	const char * curFormatPtr = format;

	for( ; *curFormatPtr != '\0'; curFormatPtr++ )
	{
		if( *curFormatPtr != '%' )
		{
			uart0_writechar_intr(*curFormatPtr);
		}
		else
		{
			curFormatPtr++;
			if( *curFormatPtr == '\0')
			{
				break;
			}
			if( *curFormatPtr == 'd')
			{
				const int valToPrint = va_arg( args, int );
				uart0_writestr_intr(util_itoa(valToPrint, printnumbuff, DEC));
			}
			else if( *curFormatPtr == 'u')
			{
				const unsigned int valToPrint = va_arg( args, unsigned int );
				uart0_writestr_intr(util_itoa(valToPrint, printnumbuff, DEC));
			}
			else if( *curFormatPtr == 'X' || *curFormatPtr == 'x')
			{
				unsigned int valToPrint = va_arg( args, unsigned int );
				uart0_writestr_intr(util_itoa(valToPrint, printnumbuff, HEX));
			}
			else if( *curFormatPtr == 'o')
			{
				unsigned int valToPrint = va_arg( args, unsigned int );
				uart0_writestr_intr(util_itoa(valToPrint, printnumbuff, OCT));
			}
			else if( *curFormatPtr == 'b')
			{
				unsigned int valToPrint = va_arg( args, unsigned int );
				uart0_writestr_intr(util_itoa(valToPrint, printnumbuff, BIN));
			}
			else if( *curFormatPtr == 's')
			{
				char * s = (char *) va_arg( args, int );
				uart0_writestr_intr( s );
			}
			else if( *curFormatPtr == 'c')
			{
				char ch = (char)va_arg( args, int );
				uart0_writechar_intr(ch);
			}
			else if( *curFormatPtr == '%')
			{
				uart0_writechar_intr('%');
			}
			else
			{
				// dont know what to do with this format string, don't molest it.
				uart0_writechar_intr('%');
				uart0_writechar_intr(*curFormatPtr);
			}
		}
	}
}


/*!
 * \brief A small version of printf
 *
 * Recognized formats:
 * <hr>
 *
 * - %x or %X  Hexadecimal
 * - %o        Octal
 * - %d        Decimal
 * - %c        Character
 * - %s        String
 *
 * <hr>
 *
 * Escape an actual '%' with a '%'. Example: em-printf("Type a percent %%")
 */
void printf(const char * format, ... )
{
	va_list args; //= NULL;
	va_start( args, format );

	em_print_intr(format, args);
}
//! @}
