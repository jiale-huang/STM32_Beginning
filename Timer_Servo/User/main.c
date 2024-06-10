#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/Timer.h"
#include "Drivers/Key.h"
#include "Drivers/OLED.h"

int main(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟, OLED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 按键外设时钟
	
	Timer_Init();		
	OLED_Init();
	Key_Init(GPIOB, GPIO_Pin_1);
	uint16_t angle = 0;
	
	while (1)
	{
		if (Key_GetKeyState(GPIOB, GPIO_Pin_1))
		{ angle+=30; }
		
		if (angle > 180) angle = 0;
		
		Timer_SetAngle(angle);
		
		OLED_ShowNum(1, 1, angle, 2);
	
	}
}



