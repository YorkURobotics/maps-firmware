/*
 * buffer_test.c
 *
 * Test file for circular buffer
 */

#include <string.h>
#include "main.h"
#include "circ_buffer.h"

// Initialize variables and define buffer
#define TX_SIZE 12
#define RX_SIZE 8
CircularBuffer buffer;
uint8_t txData[TX_SIZE];
uint8_t rxData[RX_SIZE];

circBuffDef(buffer, 100);

// Test
int test() {
	// Copies a dummy string to an 8-bit array
	memcpy(txData, "abcdefghijk", TX_SIZE);

	// Pushes and pops data in a loop
	for (int i = 0; i < 3; i++) {
		circBuffPush(&buffer, txData, TX_SIZE);
		circBuffPop(&buffer, rxData, RX_SIZE);

		HAL_Delay(1000);
	}

	return 0;
}

