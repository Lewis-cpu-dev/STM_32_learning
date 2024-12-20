#include "stm32f10x.h"

/**
  * @brief   us delay
  * @param   us, region: 0~233015
  * @retval 
  */
void Delay_us(uint32_t xus)
{
SysTick->LOAD = 72 * xus;				//reload
SysTick->VAL = 0x00;					  // clear the count
SysTick->CTRL = 0x00000005;				//SET the clock HCLK, start
	while(!(SysTick->CTRL & 0x00010000));	//count to 0
	SysTick->CTRL = 0x00000004;				// close
}

/**
  * @brief  ms delay
  * @param  xms delay，region：0~4294967295
  * @retval 
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  s delay
  * @param  s ,region：0~4294967295
  * @retval 
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
