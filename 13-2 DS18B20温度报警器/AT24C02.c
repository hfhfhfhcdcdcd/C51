#include <REGX52.H>
#include "I2C.h"

#define SLAVE_ADDRESS_W 0xA0
#define SLAVE_ADDRESS_R 0xA1
/**
  * @brief: MCU把数据写给AT24C02
  * @param:写数据的地址：WordAddress；写的数据：Data；
  * @retval:无
  */
void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
    I2C_Start();
    I2C_SendByte(SLAVE_ADDRESS_W);
    I2C_RecieveAck();
    I2C_SendByte(WordAddress);
    I2C_RecieveAck();
    I2C_SendByte(Data);
    I2C_RecieveAck();
    I2C_Stop();
}
/**
  * @brief: MCU从AT24C02读出一字节数据
  * @param:所读的数据的地址：WordAddress
  * @retval:读出的数据：Data
  */
char AT24C02_RandRead(unsigned char WordAddress )
{
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(SLAVE_ADDRESS_W);
    I2C_RecieveAck();
    I2C_SendByte(WordAddress);
    I2C_RecieveAck();

    I2C_Start();
    I2C_SendByte(SLAVE_ADDRESS_R);
    I2C_RecieveAck();
    Data = I2C_RecieveByte();
    I2C_SendAck(1);
    I2C_Stop();

    return Data;
}