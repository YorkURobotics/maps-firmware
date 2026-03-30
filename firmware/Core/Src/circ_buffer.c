/*
 * circ_buffer.c
 *
 * Source code for circular buffer
 */

#include "circ_buffer.h"

/**
 * Checks the status of the circular buffer.(empty or full)
 * 
 * @param cb Pointer to the circular buffer structure.
 * @return true if the buffer is empty (head matches tail).
 * @return false if the buffer is full (head is one behind tail).
 */
bool checkCircBuff(circularBuffer *cb) {
	if (cb->head == cb->tail) {
		return true;
	} else if ((cb->head + 1) == cb->tail) {
		return false;
	}
}

/**
 * Adds a new byte of data to the buffer.
 * 
 * @param cb Pointer to the circular buffer structure.
 * @param data The 8-bit data to be stored.
 * @return true if data was successfully added.
 * @return false if the buffer is full or unable to accept data.
 */
bool circBuffPush(circularBuffer *cb, uint8_t data) {
	if (checkCircBuff(cb)) {
		int next = cb->head + 1;
		// Wrap around to the beginning when the pointer is at the end of the array
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

/**
 * Retrieves and removes a byte of data from the buffer.
 * 
 * @param cb Pointer to the circular buffer structure.
 * @param data Pointer to the variable where the popped data will be stored.
 * @return true if data was successfully retrieved.
 * @return false if the buffer is empty.
 */
bool circBuffPop(circularBuffer *cb, uint8_t *data) {
	if (!checkCircBuff(cb)) {
		int next = cb->tail + 1;
		// Wrap around to the beginning when the pointer is at the end of the array
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
