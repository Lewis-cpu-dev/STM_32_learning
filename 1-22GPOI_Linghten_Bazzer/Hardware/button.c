#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void button_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_button;
	GPIO_button.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_button.GPIO_Pin = GPIO_Pin_9;
	GPIO_button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_button);
}

uint8_t read_button(void)
{
	uint8_t button_number;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==0);
		Delay_ms(20);
		button_number = 0;
	}
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==1)
	{
		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)==1);
		Delay_ms(20);
		button_number = 1;
	}
	return button_number;
}
