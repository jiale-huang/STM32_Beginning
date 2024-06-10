#include "Drivers/W25Q64.h"

void W25Q64_Init(void)
{
    // init
    MySPI_Init();
}

uint32_t W25Q64_ReadID()
{
    // spi start
    MySPI_Start();
    // send read id cmd: 0x9F
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    // receive id
    uint32_t id = 0;
    for (uint8_t i = 0; i < 3; i++)
    {
        id |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
        if (i <= 1)
        {
            id <<= 8;
        }
    }
    MySPI_Stop();
    return id;
}

void W25Q64_WriteEnable(void)
{
    // spi start
    MySPI_Start();
    // send read id cmd: 0x06
    MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    // spi stop
    MySPI_Stop();
}

void W25Q64_WaitBusy(void)
{
    // spi start
    MySPI_Start();
    // send read id cmd: 0x05
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    // receive status
    int32_t timeOut = 100000;
    while (MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01)
    {
        // wait
        timeOut--;
        if (timeOut <= 0)
        {
            break;
        }
    }
    // spi stop
    MySPI_Stop();
}

void W25Q64_Read(uint32_t addr, uint8_t *data, uint32_t size)
{
    // wait busy
    W25Q64_WaitBusy();
    // spi start
    MySPI_Start();
    // send read cmd: 0x03
    MySPI_SwapByte(W25Q64_READ_DATA);
    // send addr, because of only send 1 byte one time, so need to send 3 times
    MySPI_SwapByte((addr & 0xFF0000) >> 16);
    MySPI_SwapByte((addr & 0xFF00) >> 8);
    MySPI_SwapByte(addr & 0xFF);
    // receive data
    for (uint8_t i = 0; i < size; i++)
    {
        data[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    }
    // spi stop
    MySPI_Stop();
}

// 4kb
void W25Q64_SectorErase(uint32_t addr)
{
    // wait busy
    W25Q64_WaitBusy();

    // write enable
    W25Q64_WriteEnable();
    // spi start
    MySPI_Start();
    // send erase cmd: 0x20
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    // send addr, because of only send 1 byte one time, so need to send 3 times
    MySPI_SwapByte((addr & 0xFF0000) >> 16);
    MySPI_SwapByte((addr & 0xFF00) >> 8);
    MySPI_SwapByte(addr & 0xFF);
    // spi stop
    MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint32_t size)
{
    if (size > 256)
    {
        return;
    }
    // wait busy
    W25Q64_WaitBusy();

    // write enable
    W25Q64_WriteEnable();
    // spi start
    MySPI_Start();
    // send write cmd: 0x02
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    // send addr, because of only send 1 byte one time, so need to send 3 times
    MySPI_SwapByte((addr & 0xFF0000) >> 16);
    MySPI_SwapByte((addr & 0xFF00) >> 8);
    MySPI_SwapByte(addr & 0xFF);
    // send data
    for (uint8_t i = 0; i < size; i++)
    {
        MySPI_SwapByte(data[i]);
    }
    // spi stop
    MySPI_Stop();
}
