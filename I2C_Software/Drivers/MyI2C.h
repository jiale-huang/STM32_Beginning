#ifndef __MYI2C_H
#define __MYI2C_H

#define I2C_Port GPIOB
#define I2C_SCL_Pin GPIO_Pin_10
#define I2C_SDA_Pin GPIO_Pin_11
#define I2C_WriteBit 0
#define I2C_ReadBit 1

void MyI2C_Init(void);

void MyI2C_Start(void);

void MyI2C_Stop(void);

void MyI2C_SendByte(uint8_t dataByte);

uint8_t MyI2C_ReceiveAck(void);

void MyI2C_SendAck(uint8_t AckBit);

uint8_t MyI2C_ReceiveByte(void);

#endif
