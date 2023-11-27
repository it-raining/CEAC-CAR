#ifndef _ULTRA_SONIC_
#define _ULTRA_SONIC_

#include "..\util\DWT_Delay.h"
#include "..\AVERAGE FILTER\average_filter.h"

#define SOUND_SPEED 34320
#define STEP_TIMER1 4e-6 // prescalers / SysClk = 32 / 8Mhz
#define TIMER1_STEP_CYCLE (1 << 16)-1 // 65526
#define SAMPLING_TIME 25 // ms

typedef struct
{
    TIM_HandleTypeDef *htim;
    uint16_t pre_time;
    uint16_t distance; // in cm
    GPIO_TypeDef *TrigPort;
    uint16_t TrigPin;
    boolean echoHigh;
    average_filter *filter;
} ultraSonic;

/**
  * @brief  Init ultra sonic sensor
  * @param  *sensor is pointer to the ultra sonic structure
  * @param  *htim is timer used for edge detect echo pin
  * @param  *TrigPort, TrigPin is port and pin of trig pin
*/
void ultraSonic_Init(ultraSonic *sensor, TIM_HandleTypeDef *htim, GPIO_TypeDef *TrigPort, uint16_t TrigPin);

/**
  * @brief  update all paramater in ultra sonic structure
  * @param  *sensor is pointer to the ultra sonic structure
*/
void updateDistance(ultraSonic *sensor);

/**
  * @brief  set trig pin
  * @param  *sensor is pointer to the ultra sonic structure
*/
void activeTrigger(ultraSonic *sensor);

#endif