#include "stm32f10x.h"                  // Device header
#include "mySPI.h"
#include "W25_command.h"
#include "OLED.h"

void W25Q64_Init(void)
{
	mySPI_init();					//先初始化底层的SPI
}

void wait_busy(void){
	uint32_t Timeout;
	MySPI_Start();								//SPI起始
	mySPI_swapdata(W25Q64_READ_STATUS_REGISTER_1);				//交换发送读状态寄存器1的指令
	Timeout = 100000;							//给定超时计数时间
	while ((mySPI_swapdata(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	//循环等待忙标志位
	{
		Timeout --;								//等待时，计数值自减
		if (Timeout == 0)						//自减到0后，等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			break;								//跳出等待，不等了
		}
	}
	MySPI_Stop();								//SPI终止
}

void read_device_id(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	mySPI_swapdata(W25Q64_JEDEC_ID);
	*MID = mySPI_swapdata(W25Q64_DUMMY_BYTE);
	*DID = mySPI_swapdata(W25Q64_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= mySPI_swapdata(W25Q64_DUMMY_BYTE);
	MySPI_Stop();
}

void W25Q64_WriteEnable(void)
{
	MySPI_Start();								//SPI起始
	mySPI_swapdata(W25Q64_WRITE_ENABLE);		//交换发送写使能的指令
	MySPI_Stop();								//SPI终止
}

void write_page_program(uint32_t address, uint8_t *array, uint16_t count){
	
	
	uint16_t i;
	W25Q64_WriteEnable();
	MySPI_Start();
	mySPI_swapdata(W25Q64_PAGE_PROGRAM);
	mySPI_swapdata(address>>16);
	mySPI_swapdata(address>>8);
	mySPI_swapdata(address);
	
	for (i =0;i<count; i++)
	{
		mySPI_swapdata(array[i]);
	}
	MySPI_Stop();								//SPI终止
	wait_busy();							//等待忙

}

void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();						//写使能
	
	MySPI_Start();								//SPI起始
	mySPI_swapdata(W25Q64_SECTOR_ERASE_4KB);	//交换发送扇区擦除的指令
	mySPI_swapdata(Address >> 16);				//交换发送地址23~16位
	mySPI_swapdata(Address >> 8);				//交换发送地址15~8位
	mySPI_swapdata(Address);					//交换发送地址7~0位
	MySPI_Stop();								//SPI终止
	
	wait_busy();							//等待忙
}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();								//SPI起始
	mySPI_swapdata(W25Q64_READ_DATA);			//交换发送读取数据的指令
	mySPI_swapdata(Address >> 16);				//交换发送地址23~16位
	mySPI_swapdata(Address >> 8);				//交换发送地址15~8位
	mySPI_swapdata(Address);					//交换发送地址7~0位
	for (i = 0; i < Count; i ++)				//循环Count次
	{
		DataArray[i] = mySPI_swapdata(W25Q64_DUMMY_BYTE);	//依次在起始地址后读取数据
	}
	MySPI_Stop();								//SPI终止
}

