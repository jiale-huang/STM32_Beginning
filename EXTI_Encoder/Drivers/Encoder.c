#include "stm32f10x.h"                  // Device header
#include "Drivers/Encoder.h"

int16_t Encoder_Count = 0;

void Encoder_Init()
{
	// 初始化IO口，默认上拉输入
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// AFIO指定中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	// EXTI指定中断触发方式
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);	
}


int16_t Encoder_Get()
{
	int16_t tempCount = Encoder_Count;
	Encoder_Count = 0;
	return tempCount;		
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0 )
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0 )
			{ Encoder_Count--; }
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}	
}


void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
			{ Encoder_Count++; }
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}	
}

