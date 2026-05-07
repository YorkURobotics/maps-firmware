/*
 * circ_buffer.h
 *
 *  Created on: 16 มี.ค. 2569
 *      Author: pkuna
 */

#ifndef INC_CIRC_BUFFER_H_
#define INC_CIRC_BUFFER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t * const buffer;
	int head;
	int tail;
	const int maxLen;
} CircularBuffer;

typedef enum {
	BUFFER_EMPTY,
	BUFFER_FULL,
	BUFFER_PARTIAL
} BufferStatus;

#define circBuffDef(buff, size)                	\
	uint8_t buff##_data_space[size];           	\
    CircularBuffer buff = {						\
        .buffer = buff##_data_space,         	\
        .head = 0,                        		\
        .tail = 0,                        		\
        .maxLen = size                       	\
    }



BufferStatus checkCircBuff(CircularBuffer *cb);
bool circBuffPush(CircularBuffer *cb, uint8_t data[], int dataLength);
bool circBuffPop(CircularBuffer *cb, uint8_t *data, int sendLength);

#endif /* INC_CIRC_BUFFER_H_ */
