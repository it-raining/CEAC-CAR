#ifndef ADC_h
#define ADC_h
// Users define
#define _NUM_OF_SENSOR 8


typedef struct {
    uint16_t value[_NUM_OF_SENSOR];
    bool state = 0;
} ADC_sensor;

void ADC_Init(ADC_HandleTypeDef* hadc, ADC_sensor* sensor);

void ADC_DeInit(ADC_HandleTypeDef* hadc, ADC_sensor* sensor);

void PID_Servo_Init(
#endif