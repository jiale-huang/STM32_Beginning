#ifndef __INFRAREDSENSOR_H
#define __INFRAREDSENSOR_H
	
void InfraredSensor_IOInit(GPIO_TypeDef* Sensor_IO, uint16_t Sensor_Pin);
void InfraredSensor_AFIOInit(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void InfraredSensor_EXTIInit(uint32_t extiLinePort, EXTIMode_TypeDef mode, EXTITrigger_TypeDef triggerMode);
uint16_t InfraredSensor_GetCount(void);

void InfraredSensor_Init(void);

#endif
