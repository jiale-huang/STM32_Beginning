#include "stm32f10x.h"                  // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Drivers/SerialPort.h"


int main(void)
{	
	OLED_Init();  // Clock enable has been done inside init function
	
	SerialPort_Init();
	SerialPort_Send(0x44);
	
	while (1)
	{		
		Delay_s(1);		
		OLED_ShowHexNum(1, 1, SerialPort_ReceiveData, 2);
	}
}



