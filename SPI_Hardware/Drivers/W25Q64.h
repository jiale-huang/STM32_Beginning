#ifndef __W25Q64_H
#define __W25Q64_H

#include "Drivers/W25Q64_Cmd.h"
#include "stm32f10x.h"
#include "Drivers/MySPI.h"

void W25Q64_Init(void);

uint32_t W25Q64_ReadID(void);

void W25Q64_Read(uint32_t addr, uint8_t *data, uint32_t size);

void W25Q64_SectorErase(uint32_t addr);

void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint32_t size);

#endif
