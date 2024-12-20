#include "stm32f10x.h"                  // Device header

void sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_sensor;
	GPIO_sensor.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_sensor.GPIO_Pin = GPIO_Pin_13;
	GPIO_sensor.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_sensor);
}

uint8_t read_sensor(void)
{
		return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

