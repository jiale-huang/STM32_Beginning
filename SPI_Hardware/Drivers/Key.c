#include "stm32f10x.h"                  // Device header
#include "Drivers/Key.h"
#include "Utilities/Delay.h"

// 指定key的GPIOx端口，以及对应Pin引脚，配置为上拉输入
// 当按键未按下时，引脚为高电平，当按键按下时，引脚为低电平
void Key_Init(GPIO_TypeDef* key_IO, uint16_t pin)
{
	GPIO_InitTypeDef GPIO_Structure;
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Structure.GPIO_Pin = pin;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(key_IO, &GPIO_Structure);
}


// 获得按键状态，0为未按下，1为按下
uint8_t Key_GetKeyState(GPIO_TypeDef* key_IO, uint16_t pin)
{
	uint8_t keyState = 0;
	if (GPIO_ReadInputDataBit(key_IO, pin) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(key_IO, pin) == 0);
		Delay_ms(20);
		keyState = 1;			
	}	
	return keyState;
}
