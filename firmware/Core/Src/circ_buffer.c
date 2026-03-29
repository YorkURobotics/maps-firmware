/*
 * circ_buffer.c
 *
 *  Created on: 16 มี.ค. 2569
 *      Author: pkuna
 */

#include "circ_buffer.h"

bool checkCircBuff(circularBuffer *cb) {
	if (cb->head == cb->tail) {
		return true;
	} else if ((cb->head + 1) == cb->tail) {
		return false;
	}
}

bool circBuffPush(circularBuffer *cb, uint8_t data) {
	if (checkCircBuff(cb)) {
		int next = cb->head + 1;
	    if (next >= cb->maxLen) {
	    	next = 0;
	    }
		cb->buffer[cb->head] = data;
		cb->head = next;

		return true;
	} else {
		return false;
	}
}

bool circBuffPop(circularBuffer *cb, uint8_t *data) {
	if (!checkCircBuff(cb)) {
		int next = cb->tail + 1;
		if (next >= cb->maxLen) {
			next = 0;
		}
	    *data = cb->buffer[cb->tail];
	    cb->tail = next;

		return true;
	} else {
		return false;
	}
}
