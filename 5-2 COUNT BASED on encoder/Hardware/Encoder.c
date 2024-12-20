#include "stm32f10x.h"                  // Device header


int16_t Encoder_count;


void Encoder_init(void){
	// configure clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	// configure GPIO
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Initstructure);
	// configure AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	// congifure EXIT
	EXTI_InitTypeDef EXTI_Initstructure0;
	EXTI_Initstructure0.EXTI_Line= EXTI_Line0|EXTI_Line1;
	EXTI_Initstructure0.EXTI_LineCmd=ENABLE ;
	EXTI_Initstructure0.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_Initstructure0.EXTI_Trigger= EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstructure0);

	
	// congifure NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel= EXTI0_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_Initstructure);
	
	NVIC_Initstructure.NVIC_IRQChannel= EXTI1_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_Initstructure);
}

int16_t get_count(void)
{
	int16_t tem;
	tem = Encoder_count;
	Encoder_count = 0;
	return tem;
}

void EXTI0_IRQHandler(void){
	 if (EXTI_GetITStatus(EXTI_Line0) == SET){
		 if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			Encoder_count --;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line0);
	 }


}
void EXTI1_IRQHandler(void){
	 if (EXTI_GetITStatus(EXTI_Line1) == SET){
		 if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
			Encoder_count ++;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line1);
	 }


}
