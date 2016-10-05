
/*! \file em-printf.h
 *
 */

#ifndef _EM_PRINTF_H
#define _EM_PRINTF_H

/*! \ingroup em-printf
 *
 * @{
 */


#define DBG(args...) ( printf(args) )

void printf(const char * format, ... ) ;

#endif


//! @}

