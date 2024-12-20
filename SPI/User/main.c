#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25.h"

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite1[] = {0x01, 0x02, 0x03, 0x04};
uint8_t ArrayWrite2[] = {0x05, 0x06, 0x07, 0x08};
uint8_t ArrayWrite3[] = {0x09, 0x10, 0x11, 0x12};
uint8_t ArrayRead1[4];					
uint8_t ArrayRead2[4];	
uint8_t ArrayRead3[4];	


int main(void)
{
	OLED_Init();
	W25Q64_Init();
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	/*显示ID号*/
	read_device_id(&MID, &DID);			//获取W25Q64的ID号
	OLED_ShowHexNum(1, 5, MID, 2);		//显示MID
	OLED_ShowHexNum(1, 12, DID, 4);		//显示DID
	
	/*W25Q64功能函数测试*/
	W25Q64_SectorErase(0x000000);
	W25Q64_SectorErase(0x000100);//扇区擦除
	write_page_program(0x000000, ArrayWrite1, 4);	//将写入数据的测试数组写入到W25Q64中
	write_page_program(0x000700, ArrayWrite2, 4);
	write_page_program(0x001110, ArrayWrite3, 4);
	W25Q64_SectorErase(0x000710);
	W25Q64_ReadData(0x000000, ArrayRead1, 4);		//读取刚写入的测试数据到读取数据的测试数组中
	W25Q64_ReadData(0x000700, ArrayRead2, 4);		
	W25Q64_ReadData(0x001110, ArrayRead3, 4);		
	/*显示数据*/
	OLED_ShowHexNum(2, 3, ArrayWrite1[1], 2);		//显示写入数据的测试数组
	OLED_ShowHexNum(2, 6, ArrayWrite2[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite2[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite3[2], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead1[1], 2);			//显示读取数据的测试数组
	OLED_ShowHexNum(3, 6, ArrayRead2[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead2[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead3[2], 2);

	
	
	
	
	while (1)
	{
		
	}
}
