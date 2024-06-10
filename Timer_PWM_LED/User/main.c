#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/Timer.h"

int main(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟, OLED
	
	Timer_Init();		

	while (1)
	{
		for (uint8_t i = 0; i<101; ++i)
		{
			Timer_SetDutyRatio(i);
			Delay_ms(20);
		}
		
		for (uint8_t i = 100; i>0; --i)
		{
			Timer_SetDutyRatio(i);
			Delay_ms(20);
		}
	
	}
}



