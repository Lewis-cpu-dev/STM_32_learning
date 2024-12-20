#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Timebase_init(void){
	//Time base
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef Timebase_TIM2;
	Timebase_TIM2.TIM_ClockDivision = TIM_CKD_DIV1 ;
	Timebase_TIM2.TIM_CounterMode = TIM_CounterMode_Up;
	Timebase_TIM2.TIM_Period = 20000-1;
	Timebase_TIM2.TIM_Prescaler = 72-1;
	Timebase_TIM2.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &Timebase_TIM2);

}


void TIM_ENABLE(void){
	TIM_Cmd(TIM2, ENABLE);
}

void PWM1_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//GPIO
	GPIO_InitTypeDef GPIO_PWM1;
	GPIO_PWM1.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_PWM1.GPIO_Pin=GPIO_Pin_0;
	GPIO_PWM1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_PWM1);
	//OC
	TIM_OCInitTypeDef OC1_Init;
	TIM_OCStructInit(&OC1_Init);
	OC1_Init.TIM_OCMode = TIM_OCMode_PWM1;
	OC1_Init.TIM_OutputState = TIM_OutputState_Enable;
	OC1_Init.TIM_Pulse = 0;
	OC1_Init.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2,&OC1_Init); 
	
}

void PWM2_Init(void){
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//GPIO
	GPIO_InitTypeDef GPIO_PWM2;
	GPIO_PWM2.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_PWM2.GPIO_Pin=GPIO_Pin_1;
	GPIO_PWM2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_PWM2);
	//OC
	TIM_OCInitTypeDef OC1_Init;
	TIM_OCStructInit(&OC1_Init);
	OC1_Init.TIM_OCMode = TIM_OCMode_PWM1;
	OC1_Init.TIM_OutputState = TIM_OutputState_Enable;
	OC1_Init.TIM_Pulse = 0;
	OC1_Init.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2,&OC1_Init); 
}



void PWM1_set(int16_t Compare){
	if (Compare<=10000 && Compare>=0)
	TIM_SetCompare1(TIM2,Compare);
}
void PWM2_set(uint16_t Compare){
	
	TIM_SetCompare2(TIM2,Compare);
}
void motor_init(void){
	//Time base
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef Timebase_TIM3;
	Timebase_TIM3.TIM_ClockDivision = TIM_CKD_DIV1 ;
	Timebase_TIM3.TIM_CounterMode = TIM_CounterMode_Up;
	Timebase_TIM3.TIM_Period = 100-1;
	Timebase_TIM3.TIM_Prescaler = 720-1;
	Timebase_TIM3.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &Timebase_TIM3);
	// configure GPIO
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Initstructure);

	
	//GPIO PWM
	GPIO_InitTypeDef GPIO_PWM3;
	GPIO_PWM3.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_PWM3.GPIO_Pin=GPIO_Pin_6;
	GPIO_PWM3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_PWM3);
	
	TIM_OCInitTypeDef TIM_motor;
	TIM_OCStructInit(&TIM_motor);
	TIM_motor.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_motor.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_motor.TIM_Pulse = 0;
	TIM_motor.TIM_OutputState = ENABLE;
	TIM_OC1Init(TIM3,&TIM_motor);
	TIM_Cmd(TIM3, ENABLE);
}
void Motor_Speed(int8_t speed){
	if (speed >=0&& speed <= 100){
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare1(TIM3,speed);
	}
	else if(speed <0 && speed >= -100){
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare1(TIM3,-speed);
	}
	

}






