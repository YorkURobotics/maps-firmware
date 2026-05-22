#ifndef CAMERA_JOINT_H
#define CAMERA_JOINT_H

#include "servo.h"

typedef struct
{
    Servo_t pan_servo;
    Servo_t tilt_servo;

    float pan_min_deg;
    float pan_max_deg;

    float tilt_min_deg;
    float tilt_max_deg;

    float current_pan_deg;
    float current_tilt_deg;
} CameraJoint_t;

void CameraJoint_Init(CameraJoint_t *joint);

void CameraJoint_SetPan(CameraJoint_t *joint, float angle_deg);
void CameraJoint_SetTilt(CameraJoint_t *joint, float angle_deg);
void CameraJoint_SetAngles(CameraJoint_t *joint, float pan_deg, float tilt_deg);

#endif
