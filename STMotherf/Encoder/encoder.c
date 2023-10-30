#include "encoder.h"

void TimerInit(TIM_HandleTypeDef *h_time, uint32_t Channel)
{
    // Enable Output Compare Mode
    HAL_TIM_OC_Start_IT(h_time, Channel);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) // redeclare if active another channel
    {
        static byte firstCall = 0;
        uint16_t cur_counter = htim->Instance->CNT;
        int32_t diffPulse = 0;
        if (!firstCall)
        {
            left->_RPM = 0;
            right->_RPM = 0;
            firstCall++;
        }
        else
        {
            if (HAL_TIME_IS_TIM_COUNTING_DOWN(htim))
            {
                diffPulse = ((cur_counter - left->pre_counter + MAX_COUNTER) % MAX_COUNTER);
            }
            else
            {
                diffPulse = (cur_counter - left->pre_counter + MAX_COUNTER) % MAX_COUNTER;
            }
            left->_RPM = (diffPulse / PULSE) / (60 * TIME_SAMPLING * 0.1);
            left->_PWM = map(left->_RPM, 0, MAX_RPM, 0, MAX_PID_VALUE);
            left->pre_counter = htim->Instance->CNT;

            if (HAL_TIME_IS_TIM_COUNTING_DOWN(htim))
            {
                diffPulse = ((cur_counter - right->pre_counter + MAX_COUNTER) % MAX_COUNTER);
            }
            else
            {
                diffPulse = (cur_counter - right->pre_counter + MAX_COUNTER) % MAX_COUNTER;
            }

            right->_RPM = (diffPulse / PULSE) / (60 * TIME_SAMPLING * 0.1);
            right->_PWM = map(right->_RPM, 0, MAX_RPM, 0, MAX_PID_VALUE);
            right->pre_counter = htim->Instance->CNT;
    }
}

void Encoder_Init(Encoder *p1, TIM_HandleTypeDef *h_time_1, Encoder *p2, TIM_HandleTypeDef *h_time_2)
{
    // HAL_TIM_Encoder_Init(htim, sConfig);
    p1->pre_counter = 0;
    p1->htim = h_time_1;
    if (HAL_TIM_Encoder_Start(p1->htim, TIM_CHANNEL_ALL) != HAL_OK)
        Error_Handler(); // write in main.c, maybe turn some led on?

    p2->pre_counter = 0;
    p2->htim = h_time_2;
    if (HAL_TIM_Encoder_Start(p1->htim, TIM_CHANNEL_ALL) != HAL_OK)
        Error_Handler();
}

byte Direction(Encoder *p)
{
    return (p->htim->Instance->CNT - p->pre_counter) % 2;
}
