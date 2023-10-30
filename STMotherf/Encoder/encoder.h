#ifndef encoder_h
#define encoder_h

#define PULSE 98
#define MAX_COUNTER ((1 << 16) - 1)
#define TIME_SAMPLING 1
#define MAX_RPM 1
#define MAX_PID_VALUE 1

typedef struct
{
    uint16_t pre_counter;
    uint16_t _RPM;
    uint16_t _PWM;
    TIM_HandleTypeDef *htim;
}Encoder;

Encoder *left, *right;

/**
  * @brief  Initializes the encoder in DMA mode
  * @param  p1 The destination Buffer address for encoder left
  * @param  p2 The destination Buffer address for encoder right
  * @param  htim Timer handle of encoder module
  *          This parameter can be one of the following values:
  *         @arg htm3: Timer handle 3, can shorten when known fixed pins
  *         @arg htm4: Timer handle 4, can shorten when known fixed pins
*/
void Encoder_Init(Encoder *p1,TIM_HandleTypeDef *htim1, Encoder *p2,TIM_HandleTypeDef *htim);

/**
  * @brief  Get direction of motor
  * @param  p pointer to the encoder structure
*/
byte Direction(Encoder *p);

#endif
