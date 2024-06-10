#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/LED.h"
#include "Drivers/OLED.h"
#include "Drivers/Key.h"
#include "Drivers/NVICConfig.h"
#include "Drivers/Encoder.h"


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Config();
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   // 使能外设时钟 
	
	OLED_Init();
	Encoder_Init();
	
	
	int16_t Encoder_Num;
	while (1)
	{
		Encoder_Num += Encoder_Get();
		OLED_ShowSignedNum(1, 5, Encoder_Num, 5);		
	}
}
