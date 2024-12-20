#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "Delay.h"


void SCL_w(uint8_t x) 
{
	GPIO_WriteBit(SCL_port,SCL_pin,(BitAction)(x));
	Delay_us(10);
}

void SDA_w(uint8_t x) 
{
	GPIO_WriteBit(SDA_port,SDA_pin,(BitAction)(x));
	Delay_us(10);
}

uint8_t SDA_r(void)
{
	uint8_t readbit;
	readbit = GPIO_ReadInputDataBit(SDA_port,SDA_pin);
	Delay_us(10);
	return readbit;
}

void myI2C_init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef myI2C_init;
	myI2C_init.GPIO_Mode= GPIO_Mode_Out_OD;
	myI2C_init.GPIO_Pin= SCL_pin | SDA_pin;
	myI2C_init.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SCL_port,&myI2C_init);
}

void myI2C_start(void)
{
	SDA_w(1);
	SCL_w(1);
	SDA_w(0);
	SCL_w(0);
}

void myI2C_stop(void){
	SDA_w(0);
	SCL_w(1);
	SDA_w(1);
}

void myI2C_send(uint8_t data){
	uint8_t i;
	for (i=0;i<8;i++){
		SDA_w(data&(0x80>>i));
		SCL_w(1);
		SCL_w(0);
	}
}

uint8_t myI2C_read(void){
	uint8_t i,data,tem;
	data =0x00;
	SDA_w(1);  //释放SDA给从机控制
	for (i=0;i<8;i++)
	{
		SCL_w(1);
		tem = SDA_r();
		data = data|(tem<<(7-i));  //|=
		SCL_w(0);
	}
	return data;
}

void myI2C_sendack(uint8_t ack){
	SCL_w(0);
	SDA_w((BitAction)(ack));
	SCL_w(1);
	SCL_w(0);
}

uint8_t myI2C_receiveack(void){
	uint8_t ack1;
	SDA_w(1);
	SCL_w(1);
	ack1 = SDA_r();
	SCL_w(0);
	return ack1;
}




