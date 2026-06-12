#ifndef CAMERA_JOINT_CAN_H
#define CAMERA_JOINT_CAN_H

#include <stdint.h>
#include "main.h"
#include "servo.h"

/*
 * Extended 29-bit CAN IDs
 */
#define CAN_SERVO_X        0x0E110C10U
#define CAN_SERVO_Y        0x0E110C11U

/*
 * Payload sizes
 */
#define CAN_SERVO_DLC      2U

void CameraJointCAN_Init(Servo_t *pan_servo, Servo_t *tilt_servo);

void CameraJointCAN_ProcessFrame(
    CAN_HandleTypeDef *hcan,
    uint32_t id,
    uint8_t *data,
    uint8_t len
);

#endif
