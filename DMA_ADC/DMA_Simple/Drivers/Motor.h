#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"                  // Device header

	
void Motor_Init(void);	
	
void Motor_SetDirection(int8_t direction);

void Motor_ModifySpeed(uint8_t speed);


#endif
