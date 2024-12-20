#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Bazzer.h"
#include "LED.h"
#include "button.h"
#include "sensor.h"



uint8_t button_number;

int main(void)
	
{
	LED_Init();
	Bazzer_Init();
	button_Init();
	sensor_Init();
	while(1){
		if (read_sensor()==1)
		{
			Bazzer_On();
		}
		else if (read_sensor()==0)
		{
			Bazzer_down();
		}

		if (read_button() == 0)
		{	LED_Turn();
			Delay_ms(20);}
		
		};
	}
