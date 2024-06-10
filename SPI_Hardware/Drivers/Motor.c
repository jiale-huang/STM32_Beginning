#include "Drivers/Motor.h"
#include "Drivers/Timer.h"
#include "stm32f10x.h"                  // Device header


void Motor_Init(void)
{
	Timer_Init();
	
	// GPIOA_Pin4 初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	
	
	// GPIOA_Pin5 初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	
}

void Motor_ModifySpeed(uint8_t speed)
{
	uint16_t compare = speed*0.3*2000;
	Timer_SetDutyRatio(compare);
}
	
void Motor_SetDirection(int8_t direction)
{
	if (direction == 1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);		
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4 | GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
		
}
