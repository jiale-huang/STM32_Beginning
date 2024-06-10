#include "stm32f10x.h" // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Drivers/W25Q64.h"

int main(void)
{
	OLED_Init(); // Clock enable has been done inside init function
	W25Q64_Init();

	W25Q64_SectorErase(0x000000);
	uint8_t sendData[3] = {0x00, 0x11, 0x22};
	W25Q64_PageProgram(0x000000, sendData, 3);

	uint8_t receiveData[3];
	W25Q64_Read(0x000000, receiveData, 3);

	while (1)
	{
		OLED_ShowHexNum(1, 1, receiveData[0], 8);
		OLED_ShowHexNum(2, 1, receiveData[1], 8);
		OLED_ShowHexNum(3, 1, receiveData[2], 8);


		Delay_ms(100);
	}
}
