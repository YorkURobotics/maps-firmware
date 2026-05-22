#include "camera_joint.h"
#include "can_handler.h"
#include <stdint.h>

static CameraJoint_t *camera_joint_can_instance = 0;

// -----------------------------------------------------------------------------
// Internal helper functions
// -----------------------------------------------------------------------------

static int16_t CAN_ReadInt16LE(uint8_t low_byte, uint8_t high_byte)
{
    return (int16_t)((uint16_t)low_byte | ((uint16_t)high_byte << 8));
}

static void CAN_WriteInt16LE(uint8_t *data, uint8_t index, int16_t value)
{
    data[index] = (uint8_t)(value & 0xFF);
    data[index + 1U] = (uint8_t)((value >> 8) & 0xFF);
}

static float TenthsToDegrees(int16_t value)
{
    return ((float)value) / 10.0f;
}

static int16_t DegreesToTenths(float value)
{
    if (value >= 0.0f)
    {
        return (int16_t)((value * 10.0f) + 0.5f);
    }
    else
    {
        return (int16_t)((value * 10.0f) - 0.5f);
    }
}

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------

void CameraJointCAN_Init(CameraJoint_t *joint)
{
    camera_joint_can_instance = joint;
}

void CameraJointCAN_ProcessFrame(uint32_t id, uint8_t *data, uint8_t len)
{
    if (camera_joint_can_instance == 0)
    {
        return;
    }

    switch (id)
    {
        case CAN_CAMERA_JOINT_SET_ANGLES_ID:
        {
            if (len < CAN_CAMERA_JOINT_SET_ANGLES_DLC)
            {
                return;
            }

            int16_t pan_tenths = CAN_ReadInt16LE(data[0], data[1]);
            int16_t tilt_tenths = CAN_ReadInt16LE(data[2], data[3]);

            float pan_deg = TenthsToDegrees(pan_tenths);
            float tilt_deg = TenthsToDegrees(tilt_tenths);

            CameraJoint_SetAngles(
                camera_joint_can_instance,
                pan_deg,
                tilt_deg
            );

            break;
        }

        case CAN_CAMERA_JOINT_CENTER_ID:
        {
            float pan_center =
                (camera_joint_can_instance->pan_min_deg +
                 camera_joint_can_instance->pan_max_deg) / 2.0f;

            float tilt_center =
                (camera_joint_can_instance->tilt_min_deg +
                 camera_joint_can_instance->tilt_max_deg) / 2.0f;

            CameraJoint_SetAngles(
                camera_joint_can_instance,
                pan_center,
                tilt_center
            );

            break;
        }

        case CAN_CAMERA_JOINT_GET_STATUS_ID:
        {
            /*
             * Do not send directly here unless you pass hcan into this function.
             * For now, status can be sent periodically from main.c.
             */
            break;
        }

        default:
            break;
    }
}

HAL_StatusTypeDef CameraJointCAN_SendStatus(CAN_HandleTypeDef *hcan)
{
    if (camera_joint_can_instance == 0)
    {
        return HAL_ERROR;
    }

    uint8_t data[8] = {0};

    int16_t pan_tenths =
        DegreesToTenths(camera_joint_can_instance->current_pan_deg);

    int16_t tilt_tenths =
        DegreesToTenths(camera_joint_can_instance->current_tilt_deg);

    CAN_WriteInt16LE(data, 0U, pan_tenths);
    CAN_WriteInt16LE(data, 2U, tilt_tenths);

    data[4] = CAMERA_JOINT_STATUS_OK;
    data[5] = 0U;
    data[6] = 0U;
    data[7] = 0U;

    return CAN_TRANSMIT(
        hcan,
        CAN_CAMERA_JOINT_STATUS_ID,
        data,
        CAN_CAMERA_JOINT_STATUS_DLC
    );
}
