#ifndef __LED_H
#define __LED_H

void LED_Init(GPIO_TypeDef* SpecificGPIO, uint16_t Pins);
void LED_On(GPIO_TypeDef* SpecificGPIO, uint16_t Pins);
void LED_Off(GPIO_TypeDef* SpecificGPIO, uint16_t Pins);
void LED_Turn(GPIO_TypeDef* SpecificGPIO, uint16_t Pins);

#endif
