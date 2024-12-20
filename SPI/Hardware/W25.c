#include "stm32f10x.h"                  // Device header
#include "mySPI.h"
#include "W25_command.h"
#include "OLED.h"

void W25Q64_Init(void)
{
	mySPI_init();					
}

void wait_busy(void){
	uint32_t Timeout;
	MySPI_Start();								//SPI start
	mySPI_swapdata(W25Q64_READ_STATUS_REGISTER_1);				//command to swap data
	Timeout = 100000;							//count for timeout
	while ((mySPI_swapdata(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	//busy flag
	{
		Timeout --;								
		if (Timeout == 0)					
		{
			break;								
		}
	}
	MySPI_Stop();								
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
	MySPI_Start();								
	mySPI_swapdata(W25Q64_WRITE_ENABLE);		//command to enable the writing
	MySPI_Stop();								
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
	MySPI_Stop();								
	wait_busy();							

}

void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();						//ENABLE write
	
	MySPI_Start();								
	mySPI_swapdata(W25Q64_SECTOR_ERASE_4KB);	//command to exchange the sector
	mySPI_swapdata(Address >> 16);				
	mySPI_swapdata(Address >> 8);				
	mySPI_swapdata(Address);					
	MySPI_Stop();								
	
	wait_busy();							
}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();								
	mySPI_swapdata(W25Q64_READ_DATA);			//command to read the data
	mySPI_swapdata(Address >> 16);				//
	mySPI_swapdata(Address >> 8);				//
	mySPI_swapdata(Address);					//
	for (i = 0; i < Count; i ++)				//
	{
		DataArray[i] = mySPI_swapdata(W25Q64_DUMMY_BYTE);	//read data from initial address in loop
	}
	MySPI_Stop();								
}

