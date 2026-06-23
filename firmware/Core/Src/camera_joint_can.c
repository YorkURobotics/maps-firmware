#include "camera_joint_can.h"
#include "can_handler.h"

static Servo_t *pan_servo_instance = 0;
static Servo_t *tilt_servo_instance = 0;

/*
 * Optional software limits for the camera servos.
 * These replace the old CameraJoint_t min/max fields.
 */
#define PAN_MIN_DEG        0.0f
#define PAN_MAX_DEG        270.0f

#define TILT_MIN_DEG       0.0f
#define TILT_MAX_DEG       270.0f

#define PAN_CENTER_DEG     135.0f
#define TILT_CENTER_DEG    135.0f

static float ClampFloat(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }

    if (value > max)
    {
        return max;
    }

    return value;
}

static int16_t CAN_ReadInt16BE(uint8_t high_byte, uint8_t low_byte)
{
	return (int16_t)(((uint16_t)high_byte << 8) | (uint16_t)low_byte);
}

static float TenthsToDegrees(int16_t value)
{
    return ((float)value) / 10.0f;
}

static void CameraJointCAN_SetPan(float angle_deg)
{
    if (pan_servo_instance == 0)
    {
        return;
    }

    angle_deg = ClampFloat(angle_deg, PAN_MIN_DEG, PAN_MAX_DEG);
    Servo_SetAngle(pan_servo_instance, angle_deg);
}

static void CameraJointCAN_SetTilt(float angle_deg)
{
    if (tilt_servo_instance == 0)
    {
        return;
    }

    angle_deg = ClampFloat(angle_deg, TILT_MIN_DEG, TILT_MAX_DEG);
    Servo_SetAngle(tilt_servo_instance, angle_deg);
}

HAL_StatusTypeDef CameraJointCAN_Init(Servo_t *pan_servo, Servo_t *tilt_servo)
{
    if ((pan_servo == NULL) || (tilt_servo == NULL))
      {
        return HAL_ERROR;
      }

    pan_servo_instance = pan_servo;
    tilt_servo_instance = tilt_servo;
    CameraJointCAN_SetPan(PAN_CENTER_DEG);
    CameraJointCAN_SetTilt(TILT_CENTER_DEG);
    return HAL_OK;
}

void CameraJointCAN_Handle_Pan(uint8_t *data, uint8_t len)
{
  if (data == 0)
    {
        return;
    }

  if (len < CAN_SERVO_DLC)
    {
        return;
    }
/*
* Byte 0-1 = pan angle in tenths of degrees
*/
  int16_t pan_tenths = CAN_ReadInt16BE(data[0], data[1]);
  float pan_deg = TenthsToDegrees(pan_tenths);
  CameraJointCAN_SetPan(pan_deg);
}

void CameraJointCAN_Handle_Tilt(uint8_t *data, uint8_t len)
{
  if (data == 0)
    {
        return;
    }

  if (len < CAN_SERVO_DLC)
    {
        return;
    }
/*
* Byte 0-1 = tilt angle in tenths of degrees
*/
  int16_t tilt_tenths = CAN_ReadInt16BE(data[0], data[1]);
  float tilt_deg = TenthsToDegrees(tilt_tenths);
  CameraJointCAN_SetTilt(tilt_deg);
}
