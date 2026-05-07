#include <string.h>
#include "main.h"
#include "circ_buffer.h"

#define TX_SIZE 12
#define RX_SIZE 8
CircularBuffer buffer;
uint8_t txData[TX_SIZE];
uint8_t rxData[RX_SIZE];

circBuffDef(buffer, 100);

int test() {
	memcpy(txData, "abcdefghijk", TX_SIZE);

	for (int i = 0; i < 3; i++) {
		circBuffPush(&buffer, txData, TX_SIZE);
		circBuffPop(&buffer, rxData, RX_SIZE);

		HAL_Delay(1000);
	}

	return 0;
}

