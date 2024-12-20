#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyI2C.h"
#include "MPU.h"
#include "MPU_Reg.h"

#define MPU_address 0xD0
int main(void)
{
	int16_t AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
	OLED_Init();
	MPU6050_Init(MPU_address);
	
	while (1)
	{
		MPU_getdata(MPU_address, &AccX, &AccY, &AccZ, 
&GyroX, &GyroY, &GyroZ);
		OLED_ShowSignedNum(2, 1, AccX, 5);
		OLED_ShowSignedNum(3, 1, AccY, 5);
		OLED_ShowSignedNum(4, 1, AccZ, 5);
		OLED_ShowSignedNum(2, 8, GyroX, 5);
		OLED_ShowSignedNum(3, 8, GyroY, 5);
		OLED_ShowSignedNum(4, 8, GyroZ, 5);
	}
}
