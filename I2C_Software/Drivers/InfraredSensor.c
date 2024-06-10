#include "stm32f10x.h"                  // Device header
#include "Drivers/InfraredSensor.h"

static uint16_t InfraredSensor_Count = 0;

// 将输入IO设为输入浮空模式
void InfraredSensor_IOInit(GPIO_TypeDef* Sensor_IO, uint16_t Sensor_Pin)
{
	// 使用结构体初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = Sensor_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(Sensor_IO, &GPIO_InitStructure);
}


// AFIO中断引脚选择
void InfraredSensor_AFIOInit(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
}


// EXTI中断触发方式配置
void InfraredSensor_EXTIInit(uint32_t extiLinePort, EXTIMode_TypeDef mode, EXTITrigger_TypeDef triggerMode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = extiLinePort;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = mode;
	EXTI_InitStructure.EXTI_Trigger = triggerMode;
	
	EXTI_Init(&EXTI_InitStructure);
}


void InfraredSensor_Init()
{
	// GPIOB GPIO_Pin_14初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	// AFIO中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	// EXTI中断触发方式配置
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
}

uint16_t InfraredSensor_GetCount()
{
	return InfraredSensor_Count;
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET) // 判断触发中断的端口
	{
		InfraredSensor_Count++;
	}
	EXTI_ClearITPendingBit(EXTI_Line14); //软件清除中断标志位，否则会判断一直进入中断
}





