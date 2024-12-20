#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Initstructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_us(100000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_us(100000); 
	}
}

