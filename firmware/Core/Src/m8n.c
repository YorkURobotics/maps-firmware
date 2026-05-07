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
		HAL_UART_Receive(&huart2, &gpsData, GPS_DATA_SIZE, 1000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		HAL_Delay(1000);

		// Push data into buffer
		if (circBuffPush(&gpsBuffer, gpsData, GPS_DATA_SIZE)) {
			printf("Data pushed");
		}

		// Pop data into CAN_TX
		if (circBuffPop(&gpsBuffer, &CAN_TX, CAN_SIZE)) {
			printf("Data sent");
		}
	}

	return 0;
}
