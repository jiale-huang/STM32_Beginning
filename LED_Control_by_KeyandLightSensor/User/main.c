#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/LED.h"
#include "Drivers/Key.h"

int main(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能外设时钟
	
	GPIO_TypeDef* LED_IO = GPIOA;
	uint16_t LED_Pin = GPIO_Pin_1;
	
	GPIO_TypeDef* Key1_IO = GPIOB;
	uint16_t Key1_Pin = GPIO_Pin_1;

	LED_Init(LED_IO, LED_Pin);
	Key_Init(Key1_IO, Key1_Pin);

	uint8_t keyState = 0;
	
	while (1)
	{
		keyState = Key_GetKeyState(Key1_IO, Key1_Pin);
		if ( keyState == 1)
		{
			LED_Turn(LED_IO, LED_Pin);  
		}			
	}
}
