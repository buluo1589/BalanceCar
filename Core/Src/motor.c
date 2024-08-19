#include "motor.h"

void Motor_Set(int side, int speed)
{
    if (speed > 400 || speed < -400)
    {
        if (side == 0)
        {
            if (speed >= 0)
            {
                Pwm_Set_PA0(speed);
                Pwm_Set_PA1(0);
            }
            else
            {
                Pwm_Set_PA0(0);
                Pwm_Set_PA1(-speed);
            }
        }
        if (side == 1)
        {
            if (speed >= 0)
            {
                Pwm_Set_PB10(speed);
                Pwm_Set_PB11(0);
            }
            else
            {
                Pwm_Set_PB10(0);
                Pwm_Set_PB11(-speed);
            }
        }
    }
}

float Get_Speed(int side)
{
    int16_t temp;
    float speed;
    if (side == 0)
    {
        temp = -__HAL_TIM_GetCounter(&htim3);
        __HAL_TIM_SetCounter(&htim3, 0);
    }
    else if (side == 1)
    {
        temp = __HAL_TIM_GetCounter(&htim4);
        __HAL_TIM_SetCounter(&htim4, 0);
    }
    speed = temp;
    return speed;
}
