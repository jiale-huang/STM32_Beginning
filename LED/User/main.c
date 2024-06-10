#include "stm32f10x.h"                  // Device header

int main(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能外设时钟
	
	// 使用结构体初始化GPIO口
	GPIO_InitTypeDef PA0_InitStructure;
	PA0_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	PA0_InitStructure.GPIO_Pin = GPIO_Pin_0;
	PA0_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &PA0_InitStructure);
	
	// 操作具体的IO端口
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	while (1)
	{
		
	}
}
