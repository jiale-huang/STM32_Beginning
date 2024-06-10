#include "stm32f10x.h"                  // Device header
#include "Drivers/LED.h"

// 初始化指定GPIOx端口，并配置为推挽输出，默认给定高电平
// 输入的GPIO_Pin_xx可以通过|运算来同时指定多个Pin脚
void LED_Init(GPIO_TypeDef* SpecificGPIO, uint16_t Pins)
{
	// 使用结构体初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Pins;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(SpecificGPIO, &GPIO_InitStructure);
	
	// 拉高IO端口
	GPIO_SetBits(SpecificGPIO, Pins);
}

// LED采用低电平点亮电路
void LED_On(GPIO_TypeDef* SpecificGPIO, uint16_t Pins)
{
	// 拉低IO端口
	GPIO_ResetBits(SpecificGPIO, Pins);
}

// LED采用低电平点亮电路
void LED_Off(GPIO_TypeDef* SpecificGPIO, uint16_t Pins)
{
	// 拉高IO端口
	GPIO_SetBits(SpecificGPIO, Pins);
}

// 翻转LED状态
void LED_Turn(GPIO_TypeDef* SpecificGPIO, uint16_t Pin)
{
	if (GPIO_ReadInputDataBit(SpecificGPIO, Pin)==1)
	{
		GPIO_ResetBits(SpecificGPIO, Pin);
	}
	else
	{
		GPIO_SetBits(SpecificGPIO, Pin);
	}	
}
