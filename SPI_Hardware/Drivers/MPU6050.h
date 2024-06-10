#ifndef __MPU6050_H
#define __MPU6050_H
	
void MPU6050_Reg_WriteByte(uint8_t regAddr, uint8_t dataByte);

uint8_t MPU6050_Reg_ReadByte(uint8_t regAddr);

void MPU6050_Init(void);

void MPU6050_ReadAccel(int16_t *xAccel, int16_t *yAccel, int16_t *zAccel);

void MPU6050_ReadGyro(int16_t *xGyro, int16_t *yGyro, int16_t *zGyro);


#endif
