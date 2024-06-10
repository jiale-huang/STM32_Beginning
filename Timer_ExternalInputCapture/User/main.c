#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/LED.h"
#include "Drivers/OLED.h"
#include "Drivers/NVICConfig.h"
#include "Drivers/Timer.h"
#include "Drivers/InfraredSensor.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Config();
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能外设时钟, OLED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟, TIM2_ETR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	OLED_Init();
	Timer_Init();		

	while (1)
	{
		OLED_ShowNum(1,1, Timer_Get(), 5);
		OLED_ShowNum(2,1, Timer_GetCNT(), 5);
	}
}



