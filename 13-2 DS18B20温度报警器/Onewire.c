#include "REGX52.H"
#include "Delay.h"
#include <intrins.h>  

sbit OneWire_DQ = P3 ^ 7;

unsigned char Onewire_Init(void)
{
    bit AckBit;
    OneWire_DQ = 1;
    OneWire_DQ = 0;
    Delay480us();
    OneWire_DQ = 1;
    Delay80us();
    AckBit = OneWire_DQ;
    OneWire_DQ = 1;
    Delay480us();

    return AckBit;
}

void OneWire_SendBit(bit Bit)
{
    OneWire_DQ = 0;
    Delay10us();
    OneWire_DQ = Bit;
    if (Bit)
    {
        OneWire_DQ = 1;
        Delay50us();
    }
    else
    {
        Delay50us();
        OneWire_DQ = 1;
    }
}

bit OneWire_ReceiveBit(void)
{
	bit Bit;
	OneWire_DQ = 0;
	Delay10us();         // 主机拉低10us
	OneWire_DQ = 1;
	Bit = OneWire_DQ;    // 读取
	
	Delay50us();
}

void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        OneWire_SendBit(Byte & (0x01 << i));
    }
}

unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte = 0x00;
    for (i = 0;i < 8;i++)
    {
        if(OneWire_ReceiveBit())
        {
            Byte |= (0x01 << i);
        }
    }
    return Byte;
}