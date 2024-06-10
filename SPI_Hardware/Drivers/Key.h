#ifndef __Key_H
#define __Key_H

void Key_Init(GPIO_TypeDef* key_IO, uint16_t pin);	
uint8_t Key_GetKeyState(GPIO_TypeDef* key_IO, uint16_t pin);

#endif
