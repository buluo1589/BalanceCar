#include "mpu6050.h"

float dt = 0.005;
float Q_Acc = 0.95238;

int16_t Acc_x, Acc_y, Acc_z, Groy_x, Groy_y, Groy_z;
uint8_t BUF[12];

float Roll_a, Pitch_a, Roll_g, Pitch_g, Yaw_g;

float Roll_temp = 0;
float Pitch_temp = 0;
float Yaw_temp = 0;

float Roll, Pitch, Yaw, G_Roll, G_Pitch, G_Yaw;

void MPU_Write(uint8_t addr, uint8_t data) // 写
{
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_Addr, addr, 1, &data, 1, HAL_MAX_DELAY);
}
uint8_t MPU_Read(uint8_t addr) // 读
{
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_Addr, addr, 1, &data, 1, HAL_MAX_DELAY);
    return data;
}

void MPU_Init(void) // 初始化
{
    if (MPU_Read(WHO) == 0x68)
    {
        MPU_Write(PWR_M1, 0x01);   // 关睡眠，改时钟
        MPU_Write(SMPL, 0x00);     // 输出频率设置
        MPU_Write(CONFIG, 0x04);   // 滤波
        MPU_Write(G_CONFIG, 0x18); // 角速度速率设置
        MPU_Write(A_CONFIG, 0x01); // 加速度设置
    }
}

void Read_Acc(void)
{
    BUF[0] = MPU_Read(AX_L);
    BUF[1] = MPU_Read(AX_H);

    BUF[2] = MPU_Read(AY_L);
    BUF[3] = MPU_Read(AY_H);

    BUF[4] = MPU_Read(AZ_L);
    BUF[5] = MPU_Read(AZ_H);

    Acc_x = (int16_t)((BUF[1] << 8) | BUF[0]) / LSB_A;
    Acc_y = (int16_t)((BUF[3] << 8) | BUF[2]) / LSB_A;
    Acc_z = (int16_t)((BUF[5] << 8) | BUF[4]) / LSB_A;
}

void Read_Gyro(void)
{
    BUF[6] = MPU_Read(GX_L);
    BUF[7] = MPU_Read(GX_H);

    BUF[8] = MPU_Read(GY_L);
    BUF[9] = MPU_Read(GY_H);

    BUF[10] = MPU_Read(GZ_L);
    BUF[11] = MPU_Read(GZ_H);

    Groy_x = (int16_t)((BUF[7] << 8) | BUF[6]) / LSB_G;
    Groy_y = (int16_t)((BUF[9] << 8) | BUF[8]) / LSB_G;
    Groy_z = (int16_t)((BUF[11] << 8) | BUF[10]) / LSB_G;
}

void Angle_Calcu()
{
    Read_Acc();
    Read_Gyro();

    Roll_a = (float)atan2(Acc_x, Acc_z) * 180.0f / 3.14159f;
    Pitch_a = -(float)atan2(Acc_y, Acc_z) * 180.0f / 3.14159f;

    Roll_g = Roll_temp + Groy_x * dt;
    Pitch_g = Pitch_temp + Groy_y * dt;
    Yaw_g = Yaw_temp + Groy_z * dt;

    Roll_temp = Q_Acc * Roll_a + (1 - Q_Acc) * Roll_g;
    Pitch_temp = Q_Acc * Pitch_a + (1 - Q_Acc) * Pitch_g;
    Yaw_temp = Yaw_g;
}

void Get_Angle()
{
    Angle_Calcu();
    Roll = Roll_temp;
    Pitch = Pitch_temp;
    Yaw = Yaw_temp;
    G_Roll = Roll_g;
    G_Pitch = Pitch;
    G_Yaw = Yaw_g;
}
