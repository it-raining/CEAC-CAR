#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "../PID/PID.h"
#include "../AVERAGE FILTER/average_filter.h"

#define NUMS_OF_ENC 2

#define MAX_COUNTER ((1 << 16) - 1)
#define TIME_SAMPLING  100 // ms
// set based on Specification of your motor
#define MAX_RPM 5000 
#define PULSE_PER_REVOLUTION 98


typedef struct
{
    int16_t _RPM;
    int16_t _PWM;
    uint32_t pre_counter;
    TIM_HandleTypeDef *htim;
} Encoder;

Encoder *left, *right;


void updateDiffPulse(Encoder* en, TIM_HandleTypeDef *htim, uint16_t cur_counter, int32_t *diffPulse);
/**
  * @brief  Reset all paramater in Encoder structure
  * @param  *en is pointer to the encoder structure
*/
void Encoder_Init(Encoder *p1, TIM_HandleTypeDef *h_time_1, Encoder *p2, TIM_HandleTypeDef *h_time_2);
/**
  * @brief  update all values of encoder
  * @param  htim Timer handle of encoder module
  * @param  *en is pointer to the encoder structure
*/
void TimerInit(TIM_HandleTypeDef *h_time, uint32_t Channel);


byte Direction(Encoder *p);

#endif