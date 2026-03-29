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
} circularBuffer;

#define circBuffDef(buff, size)                	\
    uint8_t buff##_data_space[size];           	\
    circularBuffer buff = {						\
        .buffer = buff##_data_space,         	\
        .head = 0,                        		\
        .tail = 0,                        		\
        .maxLen = size                       	\
    }

extern circularBuffer gpsBuffer;

bool checkCircBuff(circularBuffer *cb);
bool circBuffPush(circularBuffer *cb, uint8_t data);
bool circBuffPop(circularBuffer *cb, uint8_t *data);

#endif /* INC_CIRC_BUFFER_H_ */
