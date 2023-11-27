#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "../PID/PID.h"
#include "../AVERAGE FILTER/average_filter.h"
#include "../PWM control/PWMcontrol.h"

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
    int8_t Direction;
    TIM_HandleTypeDef *htim;
} Encoder;

/*just extension function for update encoder function*/
void updateDiffPulse(Encoder* en, int32_t *diffPulse);

/**
  * @brief  Reset all paramater in Encoder structure
  * @param  *en is pointer to the encoder structure
  * @param  *h_time is timer used for Encoder
*/
void Encoder_Init(Encoder *en, TIM_HandleTypeDef *h_time);

/**
  * @brief  update all values of encoder
  * @param  *enc is pointer to the encoder structure
  * @param  mode4X used to check encoder mode 
  * If the first three bits of SMCR register are set to 0x3
  * then the timer is set in X4 mode (TIM_ENCODERMODE_TI12)
  * and we need to divide the pulses counter by two, because
  * they include the pulses for both the channels
  * example checking ((TIM3->SMCR & 0x3) == 0x3)
  * above example is checking TIM3 is X4 mode or not
*/
void updateEncoder(Encoder *enc, bool mode4X);

/**
  * @brief  Init timer for period sampling time
  * @param  *h_time is timer used for sampling time
  * @param  Channel which you choose 
*/
void TimerInitENC(TIM_HandleTypeDef *h_time, uint32_t Channel);


#endif
