#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t count;

int main(void)
{
	Encoder_init();
	OLED_Init();
	OLED_ShowString(1,2, "Hello!");
	OLED_ShowString(2,2, "Count:");
	while(1)
	{
		count+= get_count();
		OLED_ShowSignedNum(2,3,count,5);
	}
}

