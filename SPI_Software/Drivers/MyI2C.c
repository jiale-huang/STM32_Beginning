#include "stm32f10x.h" // Device header
#include "Drivers/MyI2C.h"
#include "Utilities/Delay.h"

void MyI2C_Init(void)
{
	// init clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// GPIO config
	// config SCL, SDA pin as OD output
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruture.GPIO_Pin = I2C_SCL_Pin | I2C_SDA_Pin;
	GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_Port, &GPIO_InitStruture);

	// set SCL, SDA high
	GPIO_SetBits(I2C_Port, I2C_SCL_Pin | I2C_SDA_Pin);
}

void MyI2C_SCL_WriteBit(uint8_t bit)
{
	GPIO_WriteBit(I2C_Port, I2C_SCL_Pin, (BitAction)bit);
	Delay_us(10);
}

void MyI2C_SDA_WriteBit(uint8_t bit)
{
	GPIO_WriteBit(I2C_Port, I2C_SDA_Pin, (BitAction)bit);
	Delay_us(10);
}

uint8_t MyI2C_SDA_ReadBit(void)
{
	uint8_t bit = GPIO_ReadInputDataBit(I2C_Port, I2C_SDA_Pin);
	Delay_us(10);
	return bit;
}

void MyI2C_Start(void)
{
	MyI2C_SDA_WriteBit(1);
	MyI2C_SCL_WriteBit(1);
	MyI2C_SDA_WriteBit(0); // when SCL is high, SDA is falling edge, start condition happens

	MyI2C_SCL_WriteBit(0); // hold SCL, prepare for next operation
}

void MyI2C_Stop(void)
{
	MyI2C_SDA_WriteBit(0);
	MyI2C_SCL_WriteBit(1);
	MyI2C_SDA_WriteBit(1); // when SCL is high, SDA is rising edge, stop condition happens
}

void MyI2C_SendByte(uint8_t dataByte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		MyI2C_SDA_WriteBit(dataByte & (0x80 >> i)); // send 1 bits, high position first
		MyI2C_SCL_WriteBit(1);						// when SCL is high, data on SDA is tranmmited

		MyI2C_SCL_WriteBit(0); // hold SCL, prepare for next operation
	}
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t ackBit = 0;
	MyI2C_SDA_WriteBit(1); // release SDA, wait for slave to send ACK bit
	MyI2C_SCL_WriteBit(1);
	ackBit = MyI2C_SDA_ReadBit(); // read ACK bit
	MyI2C_SCL_WriteBit(0);		  // hold SCL, prepare for next operation
	return ackBit;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_SDA_WriteBit(AckBit); // send ACK bit
	MyI2C_SCL_WriteBit(1);		// when SCL is high, data on SDA is tranmmited
	MyI2C_SCL_WriteBit(0);		// hold SCL, prepare for next operation
}

uint8_t MyI2C_ReceiveByte(void)
{
	MyI2C_SDA_WriteBit(1); // release SDA, wait for slave to send data

	uint8_t dataByte = 0x00;
	for (uint8_t i = 0; i < 8; i++)
	{
		MyI2C_SCL_WriteBit(1);				  // when SCL is high, data on SDA is tranmmited
		dataByte |= MyI2C_SDA_ReadBit() << (8-1-i); // read 1 bits, high position first
		MyI2C_SCL_WriteBit(0);				  // hold SCL, prepare for next operation
	}
	
	return dataByte;
}
