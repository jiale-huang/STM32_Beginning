#include "Drivers/MySPI.h"

void MySPI_CS_WriteBit(uint8_t dataBit)
{
    GPIO_WriteBit(SPI_Port, SPI_CS_PIN, (BitAction)dataBit);
}

void MySPI_MOSI_WriteBit(uint8_t dataBit)
{
    GPIO_WriteBit(SPI_Port, SPI_MOSI_PIN, (BitAction)dataBit);
}

void MySPI_SLK_WriteBit(uint8_t dataBit)
{
    GPIO_WriteBit(SPI_Port, SPI_SLK_PIN, (BitAction)dataBit);
}

uint8_t MySPI_MISO_ReadBit()
{
    return GPIO_ReadInputDataBit(SPI_Port, SPI_MISO_PIN);
}

void MySPI_Init()
{
    // init clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // GPIO configuration
    // output pin should be configured as push-pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN | SPI_SLK_PIN | SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Port, &GPIO_InitStructure);
    // input pin should be configured as pull-up
    GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Port, &GPIO_InitStructure);

    // default state
    MySPI_CS_WriteBit(1);
    MySPI_SLK_WriteBit(0);
}

void MySPI_Start()
{
    MySPI_CS_WriteBit(0);
}

void MySPI_Stop()
{
    MySPI_CS_WriteBit(1);
}

// mode 0
uint8_t MySPI_SwapByte(uint8_t byteSend)
{
    MySPI_Start();
    MySPI_SLK_WriteBit(0);
    uint8_t byteReceive = 0x00;
    for (uint8_t i = 0; i < 8; i++)
    {
        MySPI_MOSI_WriteBit(byteSend & (0x80>>i));
        MySPI_SLK_WriteBit(1);
        if (MySPI_MISO_ReadBit() == 1)
        {
            byteReceive |= (0x80 >> i);
        }
        MySPI_SLK_WriteBit(0);
    }
    return byteReceive;
}
