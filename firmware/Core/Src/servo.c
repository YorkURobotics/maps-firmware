#include "servo.h"
#include <stdint.h>

static uint16_t Servo_ClampPulse(Servo_t *servo, uint16_t pulse_us)
{
    if (pulse_us < servo->min_us)
    {
        return servo->min_us;
    }

    if (pulse_us > servo->max_us)
    {
        return servo->max_us;
    }

    return pulse_us;
}

HAL_StatusTypeDef Servo_Init(Servo_t* servo, TIM_HandleTypeDef* htim, uint32_t channel, uint16_t min_us, uint16_t max_us, float max_angle_deg)
{
    if (servo == NULL || htim == NULL)
      {
        return HAL_ERROR;
      }

    if (min_us >= max_us)
      {
        return HAL_ERROR;
      }

    if (max_angle_deg <= 0.0f)
      {
        return HAL_ERROR;
      }

    servo->htim = htim;
    servo->channel = channel;
    servo->min_us = min_us;
    servo->max_us = max_us;
    servo->max_angle_deg = max_angle_deg;

    return HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

void Servo_SetPulseUs(Servo_t *servo, uint16_t pulse_us)
{
    if (servo == 0)
    {
        return;
    }

    pulse_us = Servo_ClampPulse(servo, pulse_us);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, pulse_us);
}

void Servo_SetAngle(Servo_t *servo, float angle_deg)
{
    if (servo == 0)
    {
        return;
    }

    if (angle_deg < 0.0f)
    {
        angle_deg = 0.0f;
    }

    if (angle_deg > servo->max_angle_deg)
    {
        angle_deg = servo->max_angle_deg;
    }

    float pulse =
        servo->min_us +
        (angle_deg / servo->max_angle_deg) *
        (servo->max_us - servo->min_us);

    Servo_SetPulseUs(servo, (uint16_t)pulse);
}
