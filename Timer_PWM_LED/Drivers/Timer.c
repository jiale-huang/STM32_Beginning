#include "stm32f10x.h"                  // Device header
#include "Drivers/Timer.h"

static int16_t NUM = 0;

void Timer_Init(void)
{
	// 定时器时钟源选择
	TIM_InternalClockConfig(TIM2);
		
	// GPIOA_Pin0 初始化
	// PA0也是TIM2的channel 1复用的IO口，必须使用AF模式才能启用该功能
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 时基初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;  // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;  // 计数器采用720分频  PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure); // 函数中会默认进入中断一次，需要手动避免
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除TIM2触发中断标志位，避免初始化后进入中断
	
	// 输出比较器初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure); //给默认值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;  // CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	// 开始计时
	TIM_Cmd(TIM2, ENABLE);
}

void Timer_SetDutyRatio(uint16_t dutyRatio)
{
	TIM_SetCompare1(TIM2, dutyRatio);
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

