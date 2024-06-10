#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Drivers/ADC.h"

int main(void)
{	
	
	OLED_Init();  // Clock enable has been done inside init function
	AD_Init();
	
	uint16_t voltageADCNum = 0;
	
	while (1)
	{
		voltageADCNum = AD_GetValue();
		OLED_ShowNum(1, 1, voltageADCNum, 4);
		
		Delay_ms(100);	
	}
}



