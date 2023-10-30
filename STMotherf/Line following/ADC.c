// 
#include "ADC.h"
void ADC_Init(ADC_HandleTypeDef* hadc, ADC_sensor* sensor) {
    sensor->state = 1;
    HAL_ADC_Start_DMA(&hadc, sensor, _NUM_OF_SENSOR);
}

void ADC_DeInit(ADC_HandleTypeDef* hadc, ADC_sensor* sensor) {
    sensor->state = 0;
    HAL_ADC_Stop_DMA(&hadc);
}
