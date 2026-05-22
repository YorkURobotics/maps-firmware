#include "servo.h"
#include <stdint.h>

static uint16_t Servo_ClampPulse(Servo_t *servo, uint16_t pulse_us)
{
    if (pulse_us < servo->min_us)
        return servo->min_us;

    if (pulse_us > servo->max_us)
        return servo->max_us;

    return pulse_us;
}

void Servo_Init(Servo_t *servo)
{
    HAL_TIM_PWM_Start(servo->htim, servo->channel);

    float center_angle = servo->max_angle_deg / 2.0f;
    Servo_SetAngle(servo, center_angle);
}

void Servo_SetPulseUs(Servo_t *servo, uint16_t pulse_us)
{
    pulse_us = Servo_ClampPulse(servo, pulse_us);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, pulse_us);
}

void Servo_SetAngle(Servo_t *servo, float angle_deg)
{
    if (angle_deg < 0.0f)
        angle_deg = 0.0f;

    if (angle_deg > servo->max_angle_deg)
        angle_deg = servo->max_angle_deg;

    float pulse =
        servo->min_us +
        (angle_deg / servo->max_angle_deg) *
        (servo->max_us - servo->min_us);

    Servo_SetPulseUs(servo, (uint16_t)pulse);
}
