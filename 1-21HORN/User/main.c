#include "stm32f10x.h"                  // Device header
#include "delay.h"


int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIOB_Initstrucutre;
	GPIOB_Initstrucutre.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOB_Initstrucutre.GPIO_Pin = GPIO_Pin_12;
	GPIOB_Initstrucutre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_Initstrucutre);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while(1)
	{
//		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
//		Delay_us(100000);
//		GPIO_SetBits(GPIOB, GPIO_Pin_12);
//		Delay_us(100000); 
	}
}

