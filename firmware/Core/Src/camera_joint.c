#include "camera_joint.h"

static float ClampFloat(float value, float min, float max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

void CameraJoint_Init(CameraJoint_t *joint)
{
    Servo_Init(&joint->pan_servo);
    Servo_Init(&joint->tilt_servo);

    CameraJoint_SetAngles(joint, 135.0f, 135.0f);
}

void CameraJoint_SetPan(CameraJoint_t *joint, float angle_deg)
{
    angle_deg = ClampFloat(angle_deg, joint->pan_min_deg, joint->pan_max_deg);

    joint->current_pan_deg = angle_deg;
    Servo_SetAngle(&joint->pan_servo, angle_deg);
}

void CameraJoint_SetTilt(CameraJoint_t *joint, float angle_deg)
{
    angle_deg = ClampFloat(angle_deg, joint->tilt_min_deg, joint->tilt_max_deg);

    joint->current_tilt_deg = angle_deg;
    Servo_SetAngle(&joint->tilt_servo, angle_deg);
}

void CameraJoint_SetAngles(CameraJoint_t *joint, float pan_deg, float tilt_deg)
{
    CameraJoint_SetPan(joint, pan_deg);
    CameraJoint_SetTilt(joint, tilt_deg);
}
