/*
 * m8n.c
 *
 * Source code for the m8n gps
 */

#include "main.h"
#include "m8n.h"

int readData(void) {
	while (1) {
		// UART data receiver
		HAL_UART_Receive(&huart2, &gpsData, gpsDataSize, 1000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		HAL_Delay(1000);
		// Push data into buffer
		if (circBuffPush(&gpsBuffer, gpsData)) {
			printf("yes");
		}
		// Pop data into CAN_TX
		if (circBuffPop(&gpsBuffer, &CAN_TX)) {
			printf("yes");
		}
	}

	return 0;
}
