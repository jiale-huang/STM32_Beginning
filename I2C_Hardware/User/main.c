#include "stm32f10x.h" // Device header
#include "Utilities/Delay.h"
#include "Drivers/OLED.h"
#include "Drivers/MPU6050.h"
#include "Drivers/MPU6050Reg.h"

int main(void)
{
	OLED_Init(); // Clock enable has been done inside init function

	MPU6050_Init();

	int16_t xAccel, yAccel, zAccel;
	int16_t xGryo, yGryo, zGryo;

	while (1)
	{
		MPU6050_ReadAccel(&xAccel, &yAccel, &zAccel);
		MPU6050_ReadGyro(&xGryo, &yGryo, &zGryo);

		OLED_ShowSignedNum(1, 1, xAccel, 5);
		OLED_ShowSignedNum(2, 1, yAccel, 5);
		OLED_ShowSignedNum(3, 1, zAccel, 5);

		OLED_ShowSignedNum(1, 8, xGryo, 5);
		OLED_ShowSignedNum(2, 8, yGryo, 5);
		OLED_ShowSignedNum(3, 8, zGryo, 5);

		Delay_ms(100);
	}
}
