#include "encoder.h"

void resetEncoder(Encoder *en)
{
    en->RPM = 0;
    en->PWM = 0;
    en->pre_counter = 0;
}

void updateEncoder(Encoder *en, TIM_HandleTypeDef *htim)
{
    static byte firstCall = 0;
    uint16_t cur_counter = htim->Instance->CNT;
    int32_t diffPulse = 0;
    if (!firstCall)
    {
        en->RPM = 0;
        firstCall++;
    }
    else 
    {
        if (cur_counter > en->pre_counter)
        {
            if (HAL_TIME_IS_TIM_COUNTING_DOWN(htim))
            {
                diffPulse = -((en->pre_counter - cur_counter + MAX_COUNTER) % MAX_COUNTER); 
            }
            else 
            {
                diffPulse = cur_counter - en->pre_counter;
            }
        }
        else 

        {
            if (HAL_TIME_IS_TIM_COUNTING_DOWN(htim))
            {
                diffPulse = en->pre_counter - cur_counter;
            }
            else 
            {
                diffPulse = (cur_counter - en->pre_counter + MAX_COUNTER) % MAX_COUNTER;
            }
        }
    }
    en->RPM = (diffPulse / PULSE_PER_REVOLUTION) / (60 * TIME_SAMPLING * 0.1); 
    en->PWM = map(en->RPM, 0, MAX_RPM, 0, MAX_PID_VALUE);
    en->pre_counter = cur_counter; 
}