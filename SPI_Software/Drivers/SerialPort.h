#ifndef __SERIALPORT_H
#define __SERIALPORT_H
	
extern uint16_t SerialPort_ReceiveData;	
void SerialPort_Init(void);
void SerialPort_Send(uint16_t data);

#endif
