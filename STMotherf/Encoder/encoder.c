#include "encoder.h"
#define PULSE 98
#define MAX_LENGTH 65535
void Encoder_Init(Encoder *left, Encoder *right)
{
    // HAL_TIM_Encoder_Init(htim, sConfig);
    TIM_HandleTypeDef htim3;
    TIM_HandleTypeDef htim4;

    if (HAL_TIM_Encoder_Start_DMA(htim3, TIM_CHANNEL_ALL, value_1, value_2, 16) != HAL_OK)
        Error_Handler(); // write in main.c, maybe turn some led on?
    if (HAL_TIM_Encoder_Start_DMA(htim4, TIM_CHANNEL_ALL, value_1, value_2, 16) != HAL_OK)
        Error_Handler();
}

int RPM(TIM_HandleTypeDef *htim, Encoder *p)
{
    uint32_t prev_count = p->value_1;
    uint16_t prev_time = htim->Instance->CNT;
    asm("");
    int rpm = (((p->value_1 - prev_count + MAX_LENGTH*2) % (MAX_LENGTH*2))/PULSE)*60 / (((htim->Instance->CNT - prev_time + MAX_LENGTH)/MAX_LENGTH)/16e6);
    return rpm;
}

byte Direction(Encoder *p)
{
    return (p->value_1-p->value_2)%2;
}