#include "stm32f10x.h"                  // Device header


void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_LED;
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_LED.GPIO_Pin = GPIO_Pin_11;
	GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_LED);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
}


void LED_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
	{GPIO_SetBits(GPIOA, GPIO_Pin_11);}
	else if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 1)
	{GPIO_ResetBits(GPIOA, GPIO_Pin_11);}
}
