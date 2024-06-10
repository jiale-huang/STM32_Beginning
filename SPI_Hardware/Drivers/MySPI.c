#include "Drivers/MySPI.h"

void MySPI_CS_WriteBit(uint8_t dataBit)
{
    GPIO_WriteBit(SPI_Port, SPI_CS_PIN, (BitAction)dataBit);
}

void MySPI_Init()
{
    // init clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    // GPIO configuration
    // config cs as output-pull-down
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Port, &GPIO_InitStructure);

    // config slk, mosi as AF_output-push-pull
    GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN | SPI_SLK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Port, &GPIO_InitStructure);

    // config miso as input-pull-up
    GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_Port, &GPIO_InitStructure);

    // SPI configuration
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    // enable SPI
    SPI_Cmd(SPI1, ENABLE);

    // default state
    MySPI_CS_WriteBit(1);
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
    uint8_t byteReceive = 0x00;
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    SPI_I2S_SendData(SPI1, byteSend);

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    byteReceive = SPI_I2S_ReceiveData(SPI1);
    
    return byteReceive;
}
