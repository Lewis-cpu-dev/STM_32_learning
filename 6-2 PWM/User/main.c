#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Encoder.h"
#include "Key.h"

int8_t count1,count2,flag;
int8_t Encoder_count = 0;
int main(void)
{
	Key_init();
	OLED_Init();
	motor_init();
	Keep_speed_init();
	Delay_ms(20);
	OLED_ShowString(1,1,"Speed:");
	count1 = count2 = flag = 0;

	while(1)
	{
		if (read_Key()==SET && flag == 0)
			{
			if (Encoder_count <= 99){
					Motor_Speed(Encoder_count++);
					OLED_ShowSignedNum(1,7,Encoder_count,3);
			}
			else 
				Motor_Speed(Encoder_count);
		Delay_ms(50);
		}
		else if (read_Key() == RESET && flag == 0){
			if (Encoder_count >= 1){
				--Encoder_count;
				Motor_Speed(Encoder_count);
				OLED_ShowSignedNum(1,7,Encoder_count,3);
				}
		}
		else if (flag == 1){
				Motor_Speed(Encoder_count);
				OLED_ShowSignedNum(1,7,Encoder_count,3);
			Delay_ms(50);
		}
	}

}

void EXTI15_10_IRQHandler(void){
	 if (EXTI_GetITStatus(EXTI_Line15) == SET){

		 if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0){
				if (flag == 0)
					flag = 1;
				else if (flag == 1)
					flag = 0;
		 }
		 EXTI_ClearITPendingBit(EXTI_Line15);
	 }
 }

//}
//void EXTI1_IRQHandler(void){
//	 if (EXTI_GetITStatus(EXTI_Line1) == SET){
//		 if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
//			Encoder_count ++;
//			OLED_ShowSignedNum(1,2,Encoder_count,5);
//			PWM1_set(2500*Encoder_count/100);
//			Delay_ms(20);
//		 }
//		 EXTI_ClearITPendingBit(EXTI_Line1);
//	 }
//}
