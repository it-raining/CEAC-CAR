#include "ultraSonic.h"

void ultraSonic_Init(ultraSonic *sensor, TIM_HandleTypeDef *htim, GPIO_TypeDef *TrigPort, uint16_t TrigPin)
{
    sensor->htim = htim;
    sensor->pre_time = 0;
    sensor->distance = 0;
    sensor->TrigPort = TrigPort;
    sensor->TrigPin = TrigPin;
    sensor->echoHigh = false;
    DWT_Delay_Init();
    reset_buffer(sensor->filter);
}

void updateDistance(ultraSonic *sensor)
{
    if (sensor->echo == true)
    {
        sensor->pre_time = sensor->htim->Instance->CNT;
    }
    else 
    {   
        apply_filter(sensor->filter, sensor->htim->Instance->CNT - sensor->pre_time);
        sensor->distance = ((SOUND_SPEED * STEP_TIMER1) * (sensor->filter->out)) / 2; 
    }
    sensor->echoHigh = !sensor->echoHigh;
}

void activeTrigger(ultraSonic *sensor)
{
    HAL_GPIO_WritePin(sensor->TrigPort, sensor->TrigPin, 1);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(sensor->TrigPort, sensor->TrigPin, 0);
}