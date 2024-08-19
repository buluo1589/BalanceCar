#ifndef MOTOR_H
#define MOTOR_H

#include "pwm.h"

void Motor_Set(int side, int speed);
float Get_Speed(int side);

#endif
