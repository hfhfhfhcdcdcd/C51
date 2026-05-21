#ifndef __I2C_H__
#define __I2C_H__

void I2C_Start(void);

void I2C_Stop(void);

void I2C_SendByte(unsigned char Byte);

unsigned char I2C_RecieveByte(void);

void I2C_SendAck(unsigned char SEN_ACK);

unsigned char I2C_RecieveAck(void);


#endif 