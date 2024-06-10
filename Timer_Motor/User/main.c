#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/Timer.h"
#include "Drivers/Key.h"
#include "Drivers/OLED.h"
#include "Drivers/Motor.h"

int main(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟, OLED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 按键外设时钟
	
	Motor_Init();		
	OLED_Init();
	Key_Init(GPIOB, GPIO_Pin_1);
	uint16_t speed = 0;
	int8_t direction = 1;
	Motor_SetDirection(direction);
	
	while (1)
	{
		if (Key_GetKeyState(GPIOB, GPIO_Pin_1))
		{ speed++; }
		
		if (speed > 2) 
		{	
			speed = 0;
			direction = -direction;
		}
		Motor_SetDirection(direction);		
		Motor_ModifySpeed(speed);
		
		OLED_ShowNum(1, 1, speed, 2);
		OLED_ShowNum(2, 1, Timer_GetCNT(), 5);
	
	}
}



