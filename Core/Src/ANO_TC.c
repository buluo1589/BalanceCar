#include "ANO_TC.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp)) 
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))  
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

unsigned char ANO_BUFF[17];

int a11;
short x1,x2;
void Send_Angle()
{
    unsigned i,sum;
    ANO_BUFF[0] = 0xAA;
    ANO_BUFF[1] = 0xAA;
    ANO_BUFF[2] = 0x01;
    ANO_BUFF[3] = 0x0C;

    x1=(short)Roll;
    ANO_BUFF[4] = BYTE0(x1);
    ANO_BUFF[5] = BYTE1(x1);
    x1=(short)Pitch;
    ANO_BUFF[6] = BYTE0(x1);
    ANO_BUFF[7] = BYTE1(x1);

    x1=(short)Yaw;
    ANO_BUFF[8] = BYTE0(x1);
    ANO_BUFF[9] = BYTE1(x1);

    ANO_BUFF[10] = 0x00;
    ANO_BUFF[11] = 0x00;
    ANO_BUFF[12] = 0x00;
    ANO_BUFF[13] = 0x00;

    ANO_BUFF[14] = 0x00;

    ANO_BUFF[15] = 0x01;
    sum = 0;
    for(i=0;i<16;i++)
    {
        sum=ANO_BUFF[i]+sum;
    }
    ANO_BUFF[16] = sum;

    for(i=0;i<17;i++)
    {
        a11++;
        HAL_UART_Transmit(&huart2,(uint8_t *)&ANO_BUFF[i],1,100);
    }

}
