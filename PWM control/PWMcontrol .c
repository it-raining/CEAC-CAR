#include "PWMcontrol.h"

void Motor_Init(PWMcontrol *PWMcontrol, TIM_HandleTypeDef *htim, uint16_t Channel1, uint16_t Channel2)
{
    PWMcontrol->htim = htim;
    PWMcontrol->Channel1 = Channel1;
    PWMcontrol->Channel2 = Channel2;
    __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, 0);
    __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel2, 0);
    return;
}

void Servo_Init(PWMcontrol *PWMcontrol, TIM_HandleTypeDef *htim, uint16_t PWM_middle)
{
    PWMcontrol->htim = htim;
    __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, PWM_middle);
    return;
}

void set_motor(PWMcontrol *PWMcontrol, byte direction, uint16_t PWM)
{
    if (direction == BACKWARD)
    {
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, PWM);
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel2, 0);
    }
    else if (direction == FORWARD)
    {
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, 0);
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel2, PWM);
    }
    else 
    {
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, 0);
        __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel2, 0);
    }
    return;
}

void set_servo(PWMcontrol *PWMcontrol, uint16_t PWM)
{
    if (PWM > SERVO_MAX_PULSE)
    {
        PWM = SERVO_MAX_PULSE;
    }
    else if (PWM < SERVO_MIN_PULSE)
    {
        PWM = SERVO_MIN_PULSE;
    } 
    __HAL_TIM_SET_COMPARE(PWMcontrol->htim, PWMcontrol->Channel1, PWM);
    return;
}

void control_motor(PWMcontrol *motorLeft, PWMcontrol *motorRight, uint16 leftPWM, uint16_t rightPWM)
{
    
}