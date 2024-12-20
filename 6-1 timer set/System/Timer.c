#include "stm32f10x.h"                  // Device header


void Timer_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	TIM_InternalClockConfig(TIM2);//默认使用内部时钟，这一步不些也没关系
	
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x04);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	//configure GPIO
	GPIO_InitTypeDef GPIO;
	GPIO.GPIO_Mode= GPIO_Mode_IPD;
	GPIO.GPIO_Pin= GPIO_Pin_0;
	GPIO.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO);
	GPIO.GPIO_Pin= GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO);
	
	// init time base
	TIM_TimeBaseInitTypeDef TIMbase_initstruct;
	TIMbase_initstruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMbase_initstruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIMbase_initstruct.TIM_Period = 10-1;  //ARR
	TIMbase_initstruct.TIM_Prescaler = 1-1; //分频器
	TIMbase_initstruct.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM2,&TIMbase_initstruct);
	
	//enable 中断输出控制
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Struct;
	NVIC_Struct.NVIC_IRQChannel= TIM2_IRQn;
	NVIC_Struct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority= 1;
	NVIC_Struct.NVIC_IRQChannelSubPriority= 1;
	NVIC_Init(&NVIC_Struct);
	
	TIM_Cmd(TIM2,ENABLE);
	
		
}

/*void TIM2_IRQHandler(void)
{
	if (TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET){
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		}
	}
*/


