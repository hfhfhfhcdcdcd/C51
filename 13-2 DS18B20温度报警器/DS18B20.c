#include <REGX52.H>
#include "OneWire.h"
#include "Delay.h"

//DS18B20指令
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE

float DS18B20_GetTemp(void)
{
    
    unsigned char LSB, MSB;
    int Raw;
    float Temp;
    EA = 0; //关闭总中断
    Onewire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);//跳过Rom
    OneWire_SendByte(DS18B20_CONVERT_T);

    Onewire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);//跳过Rom
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);//MCD发送BE给DS18说明马上要读温度了
    LSB = OneWire_ReceiveByte();
    MSB = OneWire_ReceiveByte();
    Raw = (MSB << 8) | LSB;
    Temp = Raw /16.0;
    EA = 1; //开启总中断
    return Temp;
}
