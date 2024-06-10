#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Utilities/MyDMA.h"
#include "Drivers/ADC.h"


int main(void)
{	
	OLED_Init();  // Clock enable has been done inside init function
	AD_Init();
	MyDMA_Init((uint32_t)&ADC1->DR, (uint32_t)g_AD_Vaule, 4);
	
	while (1)
	{
		
		OLED_ShowNum(1, 1, g_AD_Vaule[0], 8);
		OLED_ShowNum(2, 1, g_AD_Vaule[1], 8);
		OLED_ShowNum(3, 1, g_AD_Vaule[2], 8);
		OLED_ShowNum(4, 1, g_AD_Vaule[3], 8);
		
		Delay_s(1);				
	}
}



