#include "stm32f10x.h"                  // Device header
#include "Utilities/MyDMA.h"

static uint32_t g_size = 0;

void MyDMA_Init(uint32_t srcAddr, uint32_t dstAddr, uint32_t size)
{
	g_size = size;
	
	// Enable DMA1 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// Configure DMA1 channel1
	DMA_InitTypeDef DMA1_InitStructure;
	DMA1_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA1_InitStructure.DMA_BufferSize = g_size;
	DMA1_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA1_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA1_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	DMA1_InitStructure.DMA_MemoryBaseAddr = dstAddr;
	DMA1_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA1_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA1_InitStructure.DMA_PeripheralBaseAddr = srcAddr;
	DMA1_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA1_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;	
	
	DMA_Init(DMA1_Channel1, &DMA1_InitStructure);
	
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, g_size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);	
}