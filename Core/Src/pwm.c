#include "pwm.h"

void Pwm_Set_PA0(int Output)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Output);
}

void Pwm_Set_PA1(int Output)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Output);
}
void Pwm_Set_PB10(int Output)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, Output);
}
void Pwm_Set_PB11(int Output)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, Output);
}