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

// throw into void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef* htim)
void updateDistance(ultraSonic *sensor)
{
    if (sensor->echo == true)
    {
        sensor->pre_time = sensor->htim->Instance->CNT; // ? or CCR ?
    }
    else 
    {   
        apply_filter(sensor->filter, sensor->htim->Instance->CNT - sensor->pre_time);
        sensor->distance = ((SOUND_SPEED * STEP_TIMER1) * (sensor->filter->out)) / 2; 
    }
    sensor->echoHigh = !sensor->echoHigh;
}

// throw into void SysTick_CallBack(void)
// {
//     //for example
//     static time = 0;
//     time++;
//     if (time == 25) //25ms
//     {
//         activeTrigger(&sensor);
//         time = 0;
//     }
// }

void activeTrigger(ultraSonic *sensor)
{
    HAL_GPIO_WritePin(sensor->TrigPort, sensor->TrigPin, 1);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(sensor->TrigPort, sensor->TrigPin, 0);
}

