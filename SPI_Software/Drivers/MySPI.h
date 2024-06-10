#ifndef __MYSPI_H__
#define __MYSPI_H__

#include "stm32f10x.h"

#define SPI_CS_PIN          GPIO_Pin_4
#define SPI_SLK_PIN         GPIO_Pin_5
#define SPI_MOSI_PIN        GPIO_Pin_7
#define SPI_MISO_PIN        GPIO_Pin_6
#define SPI_Port            GPIOA

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif /* __MYSPI_H__ */
