/*
 * m8n.c
 *
 *  Created on: 16 มี.ค. 2569
 *      Author: pkuna
 */

#include "main.h"
#include "m8n.h"

int readData(void) {
	while (1) {
		/* UART data receiver */
		HAL_UART_Receive(&huart2, &gpsData, gpsDataSize, 1000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		HAL_Delay(1000);

		if (circBuffPush(&gpsBuffer, gpsData)) {
			printf("yes");
		}

		if (circBuffPop(&gpsBuffer, &CAN_TX)) {
			printf("yes");
		}
	}

	return 0;
}
