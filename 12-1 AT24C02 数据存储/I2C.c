#include <regx52.h>

sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;

/**
  * @brief: I2C开始
  * @param:无
  * @retval:无
  */
void I2C_Start(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}
/**
  * @brief: I2C停止
  * @param:无
  * @retval:无
  */
void I2C_Stop(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1;
}
/**
  * @brief: I2C发送一字节
  * @param:发送的一字节数据：Byte
  * @retval:无
  */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        I2C_SDA = Byte & (0x80 >> i);
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}
/**
  * @brief: I2C接收一字节
  * @param:接收的一字节数据Rec_Byte
  * @retval:无
  */
unsigned char I2C_RecieveByte(void)
{
    unsigned char i, Rec_Byte = 0x00;
    I2C_SDA = 1;
    for (i = 0;i < 8;i++)
    {
        I2C_SCL = 1;
        if (I2C_SDA)
        {
            Rec_Byte |= (0x80 >> i);
        }
        I2C_SCL = 0;
    }
    return Rec_Byte;
}
/**
  * @brief: I2C发送应答
  * @param:应答信号：SEN_ACK
  * @retval:无
  */
void I2C_SendAck(unsigned char SEN_ACK)
{
    I2C_SDA = SEN_ACK;
    I2C_SCL = 1;
    I2C_SCL = 0;
}
/**
  * @brief: I2C接收应答
  * @param:无
  * @retval:接收的应答信号：REC_ACK
  */
unsigned char I2C_RecieveAck(void)
{
    unsigned char REC_ACK;
    I2C_SDA = 1;
    I2C_SCL = 1;
    REC_ACK = I2C_SDA;
    I2C_SCL = 0;
    return REC_ACK;
}