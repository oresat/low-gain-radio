/*! \file ringbuffer.h
 *
 *  \author kwilson
 */

#ifndef _RINGBUFF_H_
#define _RINGBUFF_H_

#include <stdint.h>
#include <stdbool.h>

/*! \ingroup ringbuffer
 *
 * @{
 */


/*! \typedef RB_ELEM 
 *
 */
typedef     char                 RB_ELEM;

/*! \brief Define the maximum number of bytes in a ringbuffer. */
#define     MAX_RINGBUFFER_ELEMS    255
// #define     MAX_RINGBUFFER_ELEMS    100


/*! \typedef
 */
typedef struct {
    /*! storage array for ringbuffer elements */
    RB_ELEM   rbuff[MAX_RINGBUFFER_ELEMS]   ;
    /*! head pointer into the storage array */
    uint16_t   headidx                       ;
    /*! tail pointer into the storage array */
    uint16_t   tailidx                       ;
    /*! number of entries currently in ringbuffer */
    uint16_t   num_entries                   ;
    /*! maximum number of entries for ringbuffer */
    uint16_t   max_entries                   ;
    /*! full or empty state of ringbuffer */
    bool      rbfull                        ;
} Ringbuffer;


bool rb_initialize(Ringbuffer* rb);

bool rb_put_elem(RB_ELEM c, Ringbuffer* rb);

bool rb_insert_string(char* s, Ringbuffer* rb);

bool rb_get_elem(RB_ELEM* c, Ringbuffer* rb);

void rb_get_line(RB_ELEM* s, Ringbuffer* rb) ;

void rb_get_string(RB_ELEM* s, Ringbuffer* rb);

bool rb_is_full(Ringbuffer* rb);

bool rb_is_empty(Ringbuffer* rb);

uint8_t rb_max_size(Ringbuffer* rb);

uint8_t rb_numentries(Ringbuffer* rb);

//! @}

#endif
