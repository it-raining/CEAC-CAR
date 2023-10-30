#ifndef _PWM_CONTROL_H_
#define _PWM_CONTROL_H_

#include "../AVERAGE FILTER/average_filter.h"

#define SERVO_MAX_PULSE 500  //ums
#define SERVO_MIN_PULSE 2400 //ums
#define MAX_PULSE_WIDTH 255  // tim->ARR

enum DIRECTION 
{
    BACKWARD = -1,
    STOP = 0,
    FORWARD = 1
};

typedef struct
{
    TIM_HandleTypeDef *htim;    
    uint16_t Channel1;
    uint16_t Channel2;
} PWMcontrol;

/**
  * @brief  Init Motor 
  * @param  htim Timer handle of encoder module
  * @param  Channel 
  *         This parameter can be one of the following values:
  *            @arg Channel1 : channel handle to go forward, can shorten when known fixed pins
  *            @arg Channel2 : channel handle to go backward, can shorten when known fixed pins
  *  
*/
void Motor_Init(PWMcontrol *motor, TIM_HandleTypeDef *htim, uint16_t Channel1, uint16_t Channel2);

/**
  * @brief  Init Motor 
  * @param  htim Timer handle of encoder module
*/
void Servo_Init(PWMcontrol *servo, TIM_HandleTypeDef *htim, uint16_t PWM);

/**
  * @brief  Set speed and direction of motor 
  * @param  direction is direction of rotation of the wheel
  * @param  PWM is duty cycle 
*/
void set_motor(PWMcontrol *motor, byte direction, uint16_t PWM);
/**
  * @brief  Set angle of servo
  * @param  PWM is duty cycle 
*/
void set_servo(PWMcontrol *servo, uint16_t PWM);

void control_motor(PWMcontrol *motorLeft, PWMcontrol *motorRight, uint16 leftPWM, uint16_t rightPWM);
// void HandleCar(PWMcontrol *MotorLeft, PWMcontrol *MotorRight, PWMcontrol *Servo);
#endif
