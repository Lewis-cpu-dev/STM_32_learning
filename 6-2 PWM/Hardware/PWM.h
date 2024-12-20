#ifndef __PWM_H
#define __PWM_H


void Timebase_init(void);
void motor_init(void);
void TIM_ENABLE(void);
void PWM1_Init(void);
void PWM2_Init(void);

void PWM1_set(uint16_t Compare);
void PWM2_set(uint16_t Compare);
void Motor_Speed(int8_t speed);





#endif
