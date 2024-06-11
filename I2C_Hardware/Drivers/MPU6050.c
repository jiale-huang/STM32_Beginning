#include "stm32f10x.h"
#include "Drivers/MPU6050Reg.h"
#include "Drivers/MPU6050.h"

void MPU6050_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    int32_t timeout = 10000;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        timeout--;
        if (timeout <= 0)
        {
            break;
        }
    }
}

void MPU6050_Reg_WriteByte(uint8_t regAddr, uint8_t dataByte)
{
    // wait for start event, ev5
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    // send slave address, ev6
    I2C_Send7bitAddress(I2C2, MPU6050_Addr, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    // send register address, ev8
    I2C_SendData(I2C2, regAddr);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    // send data, ev8_2
    I2C_SendData(I2C2, dataByte);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    // stop
    I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_Reg_ReadByte(uint8_t regAddr)
{
    // wait for start event, ev5
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    // send slave address, ev6
    I2C_Send7bitAddress(I2C2, MPU6050_Addr, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    // send register address, ev8_2
    I2C_SendData(I2C2, regAddr);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    // restart
    // wait for start event, ev5
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    // send slave address, ev6
    I2C_Send7bitAddress(I2C2, MPU6050_Addr, I2C_Direction_Receiver);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    // disable ack, generate stop in advance
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    // wait for data receive, ev7
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    uint8_t dataByte = I2C_ReceiveData(I2C2);

    // enable ack
    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return dataByte;
}

void MPU6050_Init(void)
{
    // clock init
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    // config GPIOB pin 10, 11 as AF_Output_OD
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // config I2C2
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_Init(I2C2, &I2C_InitStructure);

    // I2C2 enable
    I2C_Cmd(I2C2, ENABLE);

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
