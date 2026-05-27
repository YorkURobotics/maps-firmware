#ifndef CAMERA_JOINT_CAN_H
#define CAMERA_JOINT_CAN_H

#include <stdint.h>
#include "main.h"
#include "camera_joint.h"

/*
 * Extended 29-bit CAN IDs
 */
#define CAN_CAMERA_JOINT_SET_ANGLES_ID        0x0E110C10U
#define CAN_CAMERA_JOINT_GET_STATUS_ID        0x0E110C11U
#define CAN_CAMERA_JOINT_STATUS_ID            0x0E110C12U
#define CAN_CAMERA_JOINT_CENTER_ID            0x0E110C13U

/*
 * Panorama mode:
 * Payload is 3 bytes:
 *   Byte 0   = axis selector
 *   Byte 1-2 = angle in tenths of degrees, little-endian
 */
#define CAN_CAMERA_JOINT_PANORAMA_MOVE_ID     0x0E110C20U

/*
 * Axis selector values
 */
#define CAMERA_JOINT_AXIS_X                   0x00U
#define CAMERA_JOINT_AXIS_Y                   0x01U

/*
 * Payload sizes
 */
#define CAN_CAMERA_JOINT_SET_ANGLES_DLC       4U
#define CAN_CAMERA_JOINT_PANORAMA_MOVE_DLC    3U
#define CAN_CAMERA_JOINT_STATUS_DLC           8U

/*
 * Status flags
 */
#define CAMERA_JOINT_STATUS_OK                0x00U
#define CAMERA_JOINT_STATUS_ANGLE_CLAMPED     0x01U
#define CAMERA_JOINT_STATUS_CAN_TIMEOUT       0x02U
#define CAMERA_JOINT_STATUS_ERROR             0x04U

void CameraJointCAN_Init(CameraJoint_t *joint);

void CameraJointCAN_ProcessFrame(
    uint32_t id,
    uint8_t *data,
    uint8_t len
);

HAL_StatusTypeDef CameraJointCAN_SendStatus(CAN_HandleTypeDef *hcan);

#endif
