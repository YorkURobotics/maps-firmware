#include "camera_joint_can.h"
#include "can_handler.h"

static CameraJoint_t *camera_joint_can_instance = 0;

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

void CameraJointCAN_Init(CameraJoint_t *joint)
{
    camera_joint_can_instance = joint;
}

void CameraJointCAN_ProcessFrame(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data, uint8_t len)
{
    if (camera_joint_can_instance == 0)
    {
        return;
    }

    switch (id)
    {
        case CAN_SERVO_X:
        {
            /*
             * Byte 0-1 = pan angle in tenths of degrees
             */
            if (len < CAN_SERVO_DLC)
            {
                return;
            }

            int16_t pan_tenths = CAN_ReadInt16LE(data[0], data[1]);

            float pan_deg = TenthsToDegrees(pan_tenths);

            CameraJoint_SetPan(camera_joint_can_instance, pan_deg);
            break;
        }

    case CAN_SERVO_Y:
        {
             /*
             * Byte 0-1 = tilt angle in tenths of degrees
             */
            if (len < CAN_SERVO_DLC)
            {
                return;
            }

            int16_t tilt_tenths = CAN_ReadInt16LE(data[0], data[1]);

            float tilt_deg = TenthsToDegrees(tilt_tenths);

            CameraJoint_SetTilt(camera_joint_can_instance, tilt_deg);
            break;
        }

        default:
            break;
    }
}

