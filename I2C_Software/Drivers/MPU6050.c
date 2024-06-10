#include "stm32f10x.h"
#include "Drivers/MyI2C.h"
#include "Drivers/MPU6050Reg.h"
#include "Drivers/MPU6050.h"

void MPU6050_Reg_WriteByte(uint8_t regAddr, uint8_t dataByte)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_Addr | I2C_WriteBit);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return;
    }

    MyI2C_SendByte(regAddr);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return;
    }

    MyI2C_SendByte(dataByte);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return;
    }

    MyI2C_Stop();
}

uint8_t MPU6050_Reg_ReadByte(uint8_t regAddr)
{
    uint8_t dataByte;

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_Addr | I2C_WriteBit);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return 0;
    }

    MyI2C_SendByte(regAddr);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return 0;
    }

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_Addr | I2C_ReadBit);
    if (MyI2C_ReceiveAck()) // slave not answer
    {
        MyI2C_Stop();
        return 0;
    }

    dataByte = MyI2C_ReceiveByte();
    MyI2C_SendAck(1); // master not answer
    MyI2C_Stop();

    return dataByte;
}

void MPU6050_Init(void)
{
    MyI2C_Init();

    // MPU6050 config
    MPU6050_Reg_WriteByte(MPU6050_PWR_MGMT_1, 0x01);   // wake up, choose x axis clock
    MPU6050_Reg_WriteByte(MPU6050_PWR_MGMT_2, 0x00);   // disable standby mode
    MPU6050_Reg_WriteByte(MPU6050_SMPLRT_DIV, 0x09);   // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    MPU6050_Reg_WriteByte(MPU6050_CONFIG, 0x06);       // disable DLPF, set sample rate to 8kHz
    MPU6050_Reg_WriteByte(MPU6050_GYRO_CONFIG, 0x18);  // set gyro range to +/- 250 deg/s
    MPU6050_Reg_WriteByte(MPU6050_ACCEL_CONFIG, 0x18); // set accel range to +/- 2 g
}

void MPU6050_ReadAccel(int16_t *xAccel, int16_t *yAccel, int16_t *zAccel)
{
    uint8_t dataHigh = 0;
    uint8_t dataLow = 0;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_ACCEL_XOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_ACCEL_XOUT_L);
    *xAccel = (dataHigh << 8) | dataLow;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_ACCEL_YOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_ACCEL_YOUT_L);
    *yAccel = (dataHigh << 8) | dataLow;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_ACCEL_ZOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_ACCEL_ZOUT_L);
    *zAccel = (dataHigh << 8) | dataLow;
}

void MPU6050_ReadGyro(int16_t *xGyro, int16_t *yGyro, int16_t *zGyro)
{
    uint8_t dataHigh = 0;
    uint8_t dataLow = 0;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_GYRO_XOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_GYRO_XOUT_L);
    *xGyro = dataHigh << 8 | dataLow;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_GYRO_YOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_GYRO_YOUT_L);
    *yGyro = dataHigh << 8 | dataLow;

    dataHigh = MPU6050_Reg_ReadByte(MPU6050_GYRO_ZOUT_H);
    dataLow = MPU6050_Reg_ReadByte(MPU6050_GYRO_ZOUT_L);
    *zGyro = dataHigh << 8 | dataLow;
}
