/*
 * circ_buffer.h
 *
 * Header file for circular buffer
 */

#ifndef INC_CIRC_BUFFER_H_
#define INC_CIRC_BUFFER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// The circular buffer is a struct
typedef struct {
	uint8_t * const buffer;
	int head;
	int tail;
	const int maxLen;
} circularBuffer;

// Define a macro to create a circular buffer
#define circBuffDef(buff, size)                	\
    uint8_t buff##_data_space[size];           	\
    circularBuffer buff = {						\
        .buffer = buff##_data_space,         	\
        .head = 0,                        		\
        .tail = 0,                        		\
        .maxLen = size                       	\
    }

extern circularBuffer gpsBuffer; // Preemptively declaring gpsBuffer using extern to be used across files

// Declare methods for circular buffer
bool checkCircBuff(circularBuffer *cb);
bool circBuffPush(circularBuffer *cb, uint8_t data);
bool circBuffPop(circularBuffer *cb, uint8_t *data);

#endif /* INC_CIRC_BUFFER_H_ */
