#ifndef encoder_h
#define encoder_h

typedef struct
{
    uint32_t value_1, value_2;
    TIM_HandleTypeDef *htim;
}Encoder;

/**
  * @brief  Initializes the encoder in DMA mode
  * @param  left The destination Buffer address for encoder left
  * @param  right The destination Buffer address for encoder right
*/
void Encoder_Init(Encoder *left, Encoder *right);

/**
  * @brief  Get value of encoder in rpm
  * @param  htim Timer handle of encoder module
  *          This parameter can be one of the following values:
  *            @arg htm3: Timer handle 3, can shorten when known fixed pins
  *            @arg htm4: Timer handle 4, can shorten when known fixed pins
  * @param  p pointer to the encoder structure
*/
int RPM(TIM_HandleTypeDef *htim, Encoder *p);

/**
  * @brief  Get direction of motor
  * @param  p pointer to the encoder structure
*/
byte Direction(Encoder *p);

#endif
