#include "stm32f10x.h"                  // Device header

void write_MO(uint8_t bit){
	GPIO_WriteBit(GPIOA, GPIO_Pin_7 , (BitAction) bit);
}

void write_CS(uint8_t bit){
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 , (BitAction) bit);
}

void write_CLK(uint8_t bit){
	GPIO_WriteBit(GPIOA, GPIO_Pin_5 , (BitAction) bit);
}

uint8_t read_MI(void){
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6); 
}


void mySPI_init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef mySPI_GPIO;
	mySPI_GPIO.GPIO_Mode= GPIO_Mode_Out_PP ;
	mySPI_GPIO.GPIO_Pin= GPIO_Pin_7|GPIO_Pin_4|GPIO_Pin_5;
	mySPI_GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&mySPI_GPIO);
	
	mySPI_GPIO.GPIO_Mode= GPIO_Mode_IPU;
	mySPI_GPIO.GPIO_Pin= GPIO_Pin_6;
	mySPI_GPIO.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&mySPI_GPIO);
	
	write_CS(1);
	write_CLK(0);
}

void MySPI_Start(void)
{
	write_CS(0);				//拉低SS，开始时序
}

/**
  * 函    数：SPI终止
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Stop(void)
{
	write_CS(1);				//拉高SS，终止时序
}


uint8_t mySPI_swapdata(uint8_t senddata)
{
	uint8_t i,receivedata = 0x00;
	
	for (i = 0; i<8; i++){
		write_MO(senddata & (0x80>>i));
		write_CLK(1);
		if (read_MI() == 1){receivedata |= (0x80>>i);}
		write_CLK(0);
	}
	return receivedata;
	
} 
