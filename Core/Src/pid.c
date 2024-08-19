#include "pid.h"

float PID_Upright_Kp = 600; //直立环Kp 
float PID_Upright_Kd = 0; //直立环Kd
float expect_angle = 8;
float PID_Speed_Kp = 0;       //速度环Kp
float PID_Speed_Ki = 0; //速度环Ki
float PID_Steering_Kp = 0; //转向环Kp
float PID_Steering_Kd = 0; //转向环Kd

// float PID_Upright_Kp = 400; //直立环Kp 
// float PID_Upright_Kd = 2; //直立环Kd
// float expect_angle = 8;
// float PID_Speed_Kp = 200;       //速度环Kp
// float PID_Speed_Ki = 200 / 200; //速度环Ki
// float PID_Steering_Kp = 0; //转向环Kp
// float PID_Steering_Kd = 5; //转向环Kd


int PID_Upright(float angle, float gyro)
{
    int PWM_out;
    PWM_out = (int)(PID_Upright_Kp * (angle - expect_angle) + PID_Upright_Kd * gyro);
    return PWM_out;
}

int PID_Speed(int16_t expect_speed, int16_t speed)
{
    static int Speed_Integral, Speed_Err_Last;
    int PWM_out, Speed_Err;
    float a = 0.7;

    Speed_Err = speed - expect_speed;                           //误差计算
    Speed_Err = (1 - a) * Speed_Err + a * Speed_Err_Last; //低通滤波
    Speed_Err_Last = Speed_Err;                           //更新上次误差

    Speed_Integral += Speed_Err; //积分计算

    if (Speed_Integral > 10000)
        Speed_Integral = 0;
    if (Speed_Integral < -10000)
        Speed_Integral = 0; //积分限幅

    PWM_out = PID_Speed_Kp * Speed_Err + PID_Speed_Ki * Speed_Integral; //计算输出
    return PWM_out;
}

int PID_Steering(int16_t expect_yaw, float angle, float gyro)
{
    int PWM_out;
    float a = 0.7;
    static float gyro_Last;
    gyro = (1 - a) * gyro + a * gyro_Last; //低通滤波
    PWM_out = PID_Steering_Kp * (angle - expect_yaw) + PID_Steering_Kd * gyro;
    return PWM_out;
}

void Set_PID(float n)
{
    PID_Upright_Kp = n;
}
