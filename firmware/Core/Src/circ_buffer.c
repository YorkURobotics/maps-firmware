/*
 * circ_buffer.c
 *
 * Source code for circular buffer
 */

#include "circ_buffer.h"

/**
 * Checks the status of the circular buffer: empty, full, or partially filled
 * 
 * @param cb Pointer to the circular buffer structure.
 * @return BUFFER_EMPTY if the buffer is empty (head matches tail).
 * @return BUFFER_FULL if the buffer is full (head is one behind tail).
 * @return BUFFER_PARTIAL if the buffer is partially filled (everything else).
 */
BufferStatus checkCircBuff(CircularBuffer *cb) {
	if (cb->head == cb->tail) {
		return BUFFER_EMPTY;
	} else if ((cb->head + 1) == cb->tail) {
		return BUFFER_FULL;
	} else {
		return BUFFER_PARTIAL;
	}
}

/**
 * Adds new bytes of data to the buffer.
 * 
 * @param cb Pointer to the circular buffer structure.
 * @param data The array of 8-bit data to be stored.
 * @param dataLength The number of bytes to be stored.
 * @return true if data was successfully added.
 * @return false if the buffer is full or unable to accept data.
 */
bool circBuffPush(CircularBuffer *cb, uint8_t data[], int dataLength) {
	if (checkCircBuff(cb) == BUFFER_FULL) {
		return false;
	}

	for (int i = 0; i < dataLength; i++) {
		cb->buffer[cb->head] = data[i];
		cb->head++;

		// Wrap around to the beginning when the pointer is at the end of the array
		if (cb->head >= cb->maxLen) {
			cb->head = 0;
		}
	}

	return true;
}

/**
 * Retrieves and removes bytes of data from the buffer.
 * 
 * @param cb Pointer to the circular buffer structure.
 * @param data Pointer to the variable where the popped data will be stored.
 * @param sendLength The number of bytes to be retrieved.
 * @return true if data was successfully retrieved.
 * @return false if the buffer is empty.
 */
bool circBuffPop(CircularBuffer *cb, uint8_t *data[], int sendLength) {
	if (checkCircBuff(cb) == BUFFER_EMPTY) {
		return false;
	}

	for (int i = 0; i < sendLength; i++) {
		*data[i] = cb->buffer[cb->tail];
		cb->tail++;

		// Wrap around to the beginning when the pointer is at the end of the array
		if (cb->tail >= cb->maxLen) {
			cb->tail = 0;
		}
	}

	return true;
}
