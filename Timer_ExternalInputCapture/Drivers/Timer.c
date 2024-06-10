#include "stm32f10x.h"                  // Device header
#include "Drivers/Timer.h"

static int16_t NUM = 0;

void Timer_Init(void)
{
	// 定时器时钟源选择
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
		
	// GPIOA_Pin0 初始化
	// TIM2的ETR是固定的，为PA0
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 时基初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 2-1;  // 计数器采用1分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure); // 函数中会默认进入中断一次，需要手动避免
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除TIM2触发中断标志位，避免初始化后进入中断
	
	// 使能对应定时器的中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// 开始计时
	TIM_Cmd(TIM2, ENABLE);
}


uint16_t Timer_Get(void)
{
	return NUM;
}

uint16_t Timer_GetCNT(void)
{
	return TIM_GetCounter(TIM2);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		++NUM;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

