#ifndef __I2C_H__
#define __I2C_H__

void IIC_start(void);
void IIC_stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);


#endif
