#include "stm32f10x.h"                  // Device header
#include "Drivers/SerialPort.h"

uint16_t SerialPort_ReceiveData = 0;

void SerialPort_Init(void)
{
	// init clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIOA pin 9, usart 1 tx port
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
	// GPIOA pin 10, usart 1 rx port
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	// serial port init
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate = 9600;
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Initstructure.USART_Parity = USART_Parity_No; //odd or even verify
	USART_Initstructure.USART_StopBits = USART_StopBits_1;
	USART_Initstructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_Initstructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// interrupt channel config
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// enable USART1 receive interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	// prevent transmit 60 FE when init
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	//enable serial port
	USART_Cmd(USART1, ENABLE);	
}

void SerialPort_Send(uint16_t data)
{
	USART_SendData(USART1, data);
	// wait for send register empty
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}

void USART1_IRQHandler()
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		SerialPort_ReceiveData = USART_ReceiveData(USART1);
	}
}
