#ifndef SERVO_H
#define SERVO_H

#include "main.h"
#include <stdint.h>

typedef struct
{
  TIM_HandleTypeDef *htim;
  uint32_t channel;

  uint16_t min_us;
  uint16_t max_us;
  float max_angle_deg;
} Servo_t;

void Servo_Init(Servo_t* servo);
void Servo_SetPulseUs(Servo_t* servo, uint16_t pulse);
void Servo_SetAngle(Servo_t* servo, float angle);

#endif
