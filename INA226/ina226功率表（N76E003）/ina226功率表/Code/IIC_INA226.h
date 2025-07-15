#ifndef __IIC_INA226__H
#define __IIC_INA226__H

#include "Common.h"


void IIC_Init(void);
void I2CStop(void);
bit I2CStart();
void I2CAck(void);
void I2CNoAck(void);
bit I2CWaitAck(void);
void I2CSendByte(unsigned char demand); //数据从高位到低位//
unsigned char I2CReceiveByte(void);

#endif

