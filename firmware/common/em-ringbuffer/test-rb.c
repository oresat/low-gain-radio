


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ringbuffer.h"

#define MAX_RINGBUFFER_BYTES  MAX_RINGBUFFER_ELEMS

#define DBG(args...) printf(args)

/*! \brief Print the contents of the ringbuffer
 *
 */
void rb_print_buffer(Ringbuffer* rb) {
    uint8_t i=0;

    DBG("Print buffer hp:%d tp:%d\r\n", rb->headidx, rb->tailidx);
    for(i=0; i<MAX_RINGBUFFER_BYTES; ++i) {
        DBG("rbuff[%d]: %c\n\r",i, rb->rbuff[i]);
    }
}

void rb_print_state(Ringbuffer* rb) {

    DBG("\n\rStatus:\n\r");
    DBG("num entries: %d\n\r", rb->num_entries);

}

/*! \brief A little test of the ringbuffer ADT
 *
 * \param[in] rb, a Ringbuffer_s
 *
 * \return True if passes.
 */
bool rb_test() {

    Ringbuffer rbst;
    Ringbuffer* rb = &rbst;

    bool     pass = true;
    uint8_t     auint8;
    uint8_t     getstr[MAX_RINGBUFFER_BYTES];


    DBG("\n\r----------\n\rStart test\n\r");

    if(!rb_initialize(rb)) {
        DBG("Failed to init rb\n\r");
        pass = false;
    }

    rb_print_state(rb);

    DBG("***1. Insert a line\r\n");
    if(!rb_insert_string("Hello line\r\r\n", rb)) {
        DBG("Failed to insert line:\t%s\r\n", "Hello line\r\n");
        pass = false;
    }

    rb_print_state(rb);
    rb_get_line(getstr, rb);

    DBG("Got a line:\t-->%s<--\r\n", getstr);

    rb_print_state(rb);

    if(!rb_initialize(rb)) {
        DBG("Failed to re-init (2) rb\n\r");
        pass = false;
    }

    DBG("***2. Insert %c\r\n", 'a');
    if(!rb_put_elem('a',rb)) {
        DBG("Failed to insert uint8 %c\n\r", 'a');
        pass=false;
    }

    if(rb->num_entries != 1) {
        DBG("ERROR: Number of entries should be 1\r\n");
        pass = false;
    }

    DBG("***3. Get uint8 %c\r\n", 'a');
    if(!rb_get_elem(&auint8, rb)) {
        DBG("Failed to get uint8 %c\n\r", 'a');
        pass = false;
    } else if (auint8  != 'a') {
        DBG("wrong get uint8 %c\n\r", 'a');
        pass = false;
    } else {}


    if(rb->num_entries != 0) {
        DBG("ERROR: Number of entries should be 0\r\n");
        pass = false;
    }

    rb_print_state(rb);

    DBG("***4. Get a uint8\r\n");
    if(rb_get_elem(&auint8,rb)) {
        DBG("got a uint8 from empty rb");
        pass = false;
    }

    if(rb->num_entries != 0) {
        DBG("ERROR: Number of entries should be 0\r\n");
        pass = false;
    }

    DBG("***5. Insert uint8 b\t");
    if(!rb_put_elem('b',rb)) {
        DBG("Failed to insert uint8 %c\n\r", 'b');
        pass = false;
    }

    if(rb->num_entries != 1) {
        DBG("ERROR: Number of entries should be 1\r\n");
        pass = false;
    }

    rb_print_state(rb);

    DBG("***6. Insert string\r\n");
    if(!rb_insert_string("1234\n\r\n\r\t-->Ring-buffer!<--\r\n ",rb)) {
        DBG("Failed to insert string");
        pass = false;
        rb_print_state(rb);
        if(!rb_is_full(rb)) DBG("FAIL: Should report full\r\n");
    }

    rb_print_state(rb);

    if(!rb_get_elem(&auint8,rb)) {
        DBG("Failed to get uint8");
        pass = false;
    } else {
        DBG("Got a uint8: %c\n\r", auint8);
    }

    if(!rb_put_elem('c',rb)) {
        DBG("Failed to insert uint8 %c", 'c');
        pass = false;
    }

    rb_get_string(getstr, rb);

    DBG( "got string: -->%s<--\n", getstr);

    if(!rb_is_empty(rb))
    {
        DBG("FAIL: Should report empty\n\r");
        pass = false;
    }
    rb_print_state(rb);

	printf("***7.\n");
	for(int i = 0 ; i < 20 ; ++i) {
		printf("%i\n", i);
		if(!rb_insert_string("01234567890123456789",rb)) printf("fail insert string\n");
	}

	if(!rb_get_elem(&auint8,rb)) {
		DBG("Failed to get uint8");
		pass = false;
	} else {
		DBG("Got a uint8: %c\n\r", auint8);
	}

	rb_print_state(rb);

	rb_get_string(getstr, rb);
	DBG("got string: -->\n%s<--\n", getstr);
	if(strncmp(getstr, "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234",MAX_RINGBUFFER_BYTES) !=0) {
		DBG("FAIL: Strings not equal\n\r");
		pass = false;
	}


	rb_print_state(rb);

    (pass) ? DBG("PASSED RINGBUFFER TESTS\r\n") : DBG("FAILED RINGBUFFER TESTS\r\n");


    return(pass);
}


void main(void) {
	if(rb_test()) printf("Pass\n");
}
