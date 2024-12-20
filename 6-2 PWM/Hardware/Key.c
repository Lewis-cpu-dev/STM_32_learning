#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Key;
	GPIO_Key.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Key.GPIO_Pin=GPIO_Pin_9;
	GPIO_Key.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Key);
	
}
uint8_t read_Key(void){   //key pressed return 0, or return 1
	uint8_t number;
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) == 0)
	{
		Delay_ms(20);
		number = 1;
		
	}
	else
	{
		Delay_ms(20);
		number = 0;
	}
	return number;
}

void Keep_speed_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
	
	EXTI_InitTypeDef EXTI_Initstructure15;
	EXTI_Initstructure15.EXTI_Line= EXTI_Line15;
	EXTI_Initstructure15.EXTI_LineCmd=ENABLE ;
	EXTI_Initstructure15.EXTI_Mode= EXTI_Mode_Interrupt;
	EXTI_Initstructure15.EXTI_Trigger= EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstructure15);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef Keep_init;
	Keep_init.NVIC_IRQChannel = EXTI15_10_IRQn;
	Keep_init.NVIC_IRQChannelCmd =ENABLE; 
	Keep_init.NVIC_IRQChannelPreemptionPriority = 1;
	Keep_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&Keep_init);
	
}
