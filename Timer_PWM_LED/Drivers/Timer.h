#ifndef __Timer_H
#define __Timer_H
	
void Timer_Init(void);
uint16_t Timer_Get(void);
uint16_t Timer_GetCNT(void);
void Timer_SetDutyRatio(uint16_t dutyRatio);

#endif
