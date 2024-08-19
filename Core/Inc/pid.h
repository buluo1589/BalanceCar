#ifndef PID_H
#define PID_H

#include "main.h"

int PID_Upright(float angle, float gyro);
int PID_Speed(int16_t expect_speed, int16_t speed);
int PID_Steering(int16_t expect_yaw, float angle, float gyro);
void Set_PID(float n);

#endif
