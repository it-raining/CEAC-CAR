#ifndef PID_CONTROL_H_
#define PID_CONTROL_H_

#include <stdbool.h>

#define MAX_INTEGRAL 20000000 //
#define MAX_PID_VALUE 1000 // 


typedef struct
{
    float p_gain;
    float i_gain;
    float d_gain;
    int16_t pre_error;
    int32_t integral_error;
    int16_t output_PID;
    bool isSaturation;
} PID_instance;

void set_PID_gain(PID_instance *PID, float p, float i, float d);
void reset_PID_gain(PID_instance *PID);
void output_PID(PID_instance *PID, int16_t error_input, uint16_t sampling_rate);
void constrain(int32_t &value, int32_t min_value, int32_t max_value);

#endif 
/*PID_CONTROL_H_*/
