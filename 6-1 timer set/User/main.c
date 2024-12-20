#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "Timer.h"

int16_t num;

int main(void)
{
	Timer_init();
	OLED_Init();
	OLED_ShowString(1,1,"Num: ");
	while(1)
	{
		OLED_ShowSignedNum(1,5,num,5);
		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET){
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==SET )
			num++;
		else if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==RESET )
			num--;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		}
	}
