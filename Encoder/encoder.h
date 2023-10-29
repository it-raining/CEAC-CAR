#ifndef _ENCODER_H_
#define _ENCODER_H_

#define MAX_COUNTER ((1 << 16) - 1)
#define PULSE_PER_REVOLUTION 98
#define TIME_SAMPLING  100//ms

typedef struct
{
    int16_t RPM;
    uint32_t pre_counter;
} Encoder;

/**
  * @brief  Reset all paramater in Encoder structure
  * @param  *en is pointer to the encoder structure
*/
void resetEncoder(Encoder *en);
/**
  * @brief  update all values of encoder
  * @param  htim Timer handle of encoder module
  * @param  *en is pointer to the encoder structure
*/
void updateEncoder(Encoder *en, TIM_HandleTypeDef *htim);

#endif