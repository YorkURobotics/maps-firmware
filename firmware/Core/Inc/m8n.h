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
#define GPS_DATA_SIZE 128
#define CAN_SIZE 8
uint8_t gpsData[GPS_DATA_SIZE];
volatile uint8_t CAN_TX[CAN_SIZE];
// Declaring gpsBuffer using extern to be used across files
extern CircularBuffer gpsBuffer;
circBuffDef(gpsBuffer, 1000);

#endif /* SRC_M8N_H_ */
