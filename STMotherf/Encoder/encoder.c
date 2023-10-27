#include "encoder.h"
#define PULSE 98
#define MAX_LENGTH 65535
void Encoder::Encoder_Init()
{
    // HAL_TIM_Encoder_Init(htim, sConfig);
    // check parameters
    if (HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL) != HAL_OK)
        Error_Handler(); // write in main.c, maybe turn some led on?
    //

    // notice that we using 2 phase encoder
    HAL_TIM_Encoder_Start_DMA(htim, TIM_CHANNEL_ALL, value_1, value_2, 16);
}

int Encoder::RPM()
{
    uint32_t prev_count = value_1;
    uint16_t prev_time = htim->->Instance->CNT;
    asm("");
    int rpm = (((value_1 - prev_count + MAX_LENGTH*2) % (MAX_LENGTH*2))/PULSE)*60 / (((htim->->Instance->CNT - prev_time + MAX_LENGTH)/MAX_LENGTH)/16e6);
    return rpm;
}

byte Encoder::Direction()
{
    return (byte)(value_1 - value_2);
}