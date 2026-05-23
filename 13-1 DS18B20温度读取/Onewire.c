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

bit OneWire_RecieveBit(void)
{
     bit b;
    OneWire_DQ = 0;
    _nop_(); _nop_();   // 拉低约2µs
    OneWire_DQ = 1;     // 释放总线
    _nop_(); _nop_();   // 稍延时，等待DS18B20输出
    b = OneWire_DQ;
    Delay50us();        // 保证读时隙总长至少60µs
    return b;
}

void OneWire_SendByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        OneWire_SendBit(Byte & (0x01 << i));
    }
}

unsigned char OneWire_RecieveByte(void)
{
    unsigned char i;
    unsigned char Byte = 0x00;
    for (i = 0;i < 8;i++)
    {
        if(OneWire_RecieveBit())
        {
            Byte |= (0x01 << i);
        }
    }
    return Byte;
}