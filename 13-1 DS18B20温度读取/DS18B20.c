#include "Onewire.h"
#include "Delay.h"

int DS18B20_GetTemp(void)
{
    unsigned char LSB, MSB;
    int Raw, Temp;
    Onewire_Init();
    OneWire_SendByte(0xcc);//跳过Rom
    OneWire_SendByte(0x44);
    Delay750ms();

    Onewire_Init();
    OneWire_SendByte(0xcc);//跳过Rom
    OneWire_SendByte(0xBE);//MCD发送BE给DS18说明马上要读温度了
    LSB = OneWire_RecieveByte();
    MSB = OneWire_RecieveByte();
    Raw = (MSB << 8) | LSB;
    Temp = Raw * 0.0625;

    return Temp;
}
