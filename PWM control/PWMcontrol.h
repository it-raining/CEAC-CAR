#ifndef _PWM_CONTROL_H_
#define _PWM_CONTROL_H_

#define SERVO_MAX_PULSE 500
#define SERVO_MIN_PULSE 2400

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


void Motor_Init(PWMcontrol *PWMcontrol, TIM_HandleTypeDef *htim, uint16_t Channel);
void Servo_Init(PWMcontrol *PWMcontrol, TIM_HandleTypeDef *htim, uint16_t PWM);

void set_motor(PWMcontrol *PWMcontrol, byte direction, uint16_t PWM);
void set_servo(PWMcontrol *PWMcontrol, uint16_t PWM);

#endif
