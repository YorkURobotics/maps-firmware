/*
 * circ_buffer.c
 *
 *  Created on: 16 มี.ค. 2569
 *      Author: pkuna
 */

#include "circ_buffer.h"

BufferStatus checkCircBuff(CircularBuffer *cb) {
	if (cb->head == cb->tail) {
		return BUFFER_EMPTY;
	} else if ((cb->head + 1) == cb->tail) {
		return BUFFER_FULL;
	} else {
		return BUFFER_PARTIAL;
	}
}

bool circBuffPush(CircularBuffer *cb, uint8_t data[], int dataLength) {
	if (checkCircBuff(cb) == BUFFER_FULL) {
		return false;
	}

	for (int i = 0; i < dataLength; i++) {
		cb->buffer[cb->head] = data[i];
		cb->head++;

		if (cb->head >= cb->maxLen) {
			cb->head = 0;
		}
	}

	return true;
}

bool circBuffPop(CircularBuffer *cb, uint8_t *data, int sendLength) {
	if (checkCircBuff(cb) == BUFFER_EMPTY) {
		return false;
	}

	for (int i = 0; i < sendLength; i++) {
		data[i] = cb->buffer[cb->tail];
		cb->tail++;

		if (cb->tail >= cb->maxLen) {
			cb->tail = 0;
		}
	}

	return true;
}
