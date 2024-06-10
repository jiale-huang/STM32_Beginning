#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Utilities/MyDMA.h"

int main(void)
{	
	uint8_t A[] = {0x01, 0x02, 0x03, 0x04};
	uint8_t B[] = {0x05, 0x06, 0x07, 0x08};
	
	OLED_Init();  // Clock enable has been done inside init function
	MyDMA_Init((uint32_t)A, (uint32_t)B, 4);
	
	while (1)
	{
		
		OLED_ShowNum(1, 1, A[0], 2);
		OLED_ShowNum(1, 3, A[1], 2);
		OLED_ShowNum(1, 5, A[2], 2);
		OLED_ShowNum(1, 7, A[3], 2);
		
		OLED_ShowNum(2, 1, B[0], 2);
		OLED_ShowNum(2, 3, B[1], 2);
		OLED_ShowNum(2, 5, B[2], 2);
		OLED_ShowNum(2, 7, B[3], 2);
		
		Delay_s(5);
		
		
		MyDMA_Transfer();
		
	}
}



