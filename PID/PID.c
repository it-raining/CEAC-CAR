#include "PID.h"

void set_PID_gain(PID_instance *PID, float p, float i, float d)
{
    PID->p_gain = p;
    PID->i_gain = i;
    PID->d_gain = d;
    return;
}

void reset_PID_gain(PID_instance *PID)
{
    PID->p_gain = 0.0;
    PID->i_gain = 0.0;
    PID->d_gain = 0.0;
    return;
}

void constrain(int32_t &value, int32_t min_value, int32_t max_value)
{
    if (value > max_value)
    {
        value = max_value;
    }
    if (value < min_value)
    {
        value = min_value;
    }
    return;
}

void output_PID(PID_instance *PID, int16_t error_input, uint16_t sampling_rate)
{
    PID->integral_error += error_input;
    
    constrain(PID->integral_error, -MAX_INTEGRAL, MAX_INTEGRAL);
    
    PID->output_PID = PID->p_gain * error_input 
                    + PID->i_gain * PID->integral_error / sampling_rate
                    + PID->d_gain * (error_input - PID->pre_error) * sampling_rate;

    constrain(PID->output_PID, -MAX_PID_VALUE, MAX_PID_VALUE);

    PID->pre_error = error_input;
    return;
}