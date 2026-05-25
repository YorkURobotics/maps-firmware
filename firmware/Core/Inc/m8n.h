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

// Declaring gpsBuffer using extern to be used across files
extern CircularBuffer gpsBuffer;

#endif /* SRC_M8N_H_ */
