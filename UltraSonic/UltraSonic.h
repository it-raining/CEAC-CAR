#ifndef _ULTRA_SONIC_
#define _ULTRA_SONIC_

#include "..\util\DWT_Delay.h"
#include "..\AVERAGE FILTER\average_filter.h"

#define SOUND_SPEED 34320
#define STEP_TIMER1 4e-6 // sysClk / (Precaler + Period)
#define TIMER1_STEP_CYCLE (1 << 16)-1
#define SAMPLING_TIME 25

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

void ultraSonic_Init(ultraSonic *sensor, TIM_HandleTypeDef *htim, GPIO_TypeDef *TrigPort, uint16_t TrigPin);
void updateDistance(ultraSonic *sensor);
void activeTrigger(ultraSonic *sensor);

#endif