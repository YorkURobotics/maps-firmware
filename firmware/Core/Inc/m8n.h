/*
 * m8n.h
 *
 * Header file for the m8n gps
 */

#ifndef SRC_M8N_H_
#define SRC_M8N_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "circ_buffer.h"

// Declare and initialize variables
uint8_t gpsData = 0x55;
volatile uint64_t CAN_TX;
int gpsDataSize = 128;

circBuffDef(gpsBuffer, 1000);

#endif /* SRC_M8N_H_ */
