#include "stm32f10x.h"                  // Device header
#include "Utilities/MyDMA.h"

uint16_t g_AD_Vaule[4] = {0, 0, 0, 0};

void MyDMA_Init(uint32_t srcAddr, uint32_t dstAddr, uint32_t size)
{
	
	// Enable DMA1 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// Configure DMA1 channel1
	DMA_InitTypeDef DMA1_InitStructure;
	DMA1_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA1_InitStructure.DMA_BufferSize = size; //transfer counter
	DMA1_InitStructure.DMA_M2M = DMA_M2M_Disable; // hardware trigger or software trigger
	DMA1_InitStructure.DMA_Mode = DMA_Mode_Circular;  // continuous move
	DMA1_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	DMA1_InitStructure.DMA_MemoryBaseAddr = dstAddr;
	DMA1_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA1_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA1_InitStructure.DMA_PeripheralBaseAddr = srcAddr;
	DMA1_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA1_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	
	
	DMA_Init(DMA1_Channel1, &DMA1_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
}

