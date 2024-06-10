#include "stm32f10x.h"                  // Device header
#include "Drivers/Timer.h"

static int16_t NUM = 0;

void Timer_Init(void)
{	
	// GPIOA_Pin2 初始化
	// PA1也是TIM2的channel 3复用的IO口，必须使用AF模式才能启用该功能
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
	// 定时器时钟源选择
	TIM_InternalClockConfig(TIM2);
	
	// 时基初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 2000 - 1;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元
	
	// 输出比较器初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure); //给默认值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;  // CCR
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  // 注意这里是OC2	

	// 开始计时
	TIM_Cmd(TIM2, ENABLE);
}

void Timer_SetDutyRatio(uint16_t compare)
{
	TIM_SetCompare3(TIM2, compare);
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

