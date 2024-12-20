#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void Bazzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Bazzer;
	GPIO_Bazzer.GPIO_Mode = GPIO_Mode_Out_OD ;
	GPIO_Bazzer.GPIO_Pin = GPIO_Pin_12;
	GPIO_Bazzer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Bazzer);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}


void Bazzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13) == 0)
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	else if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13) == 1)
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Bazzer_On(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Bazzer_down(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}
