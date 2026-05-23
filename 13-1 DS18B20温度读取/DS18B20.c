#include <REGX52.H>
#include "OneWire.h"

//DS18B20指令
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE

/**
  * @brief  DS18B20开始温度变换
  * @param  无
  * @retval 无
  */
// void DS18B20_Convert(void)
// {
// 	OneWire_Init();
// 	OneWire_SendByte(DS18B20_SKIP_ROM);
// 	OneWire_SendByte(DS18B20_CONVERT_T);
// }

// /**
//   * @brief  DS18B20读取温度
//   * @param  无
//   * @retval 温度数值
//   */
// float DS18B20_ReadT(void)
// {
// 	unsigned char TLSB,TMSB;
// 	int Temp;
// 	float T;
// 	OneWire_Init();
// 	OneWire_SendByte(DS18B20_SKIP_ROM);
// 	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
// 	TLSB=OneWire_ReceiveByte();
// 	TMSB=OneWire_ReceiveByte();
// 	Temp=(TMSB<<8)|TLSB;
// 	T=Temp/16.0;
// 	return T;
// }


float DS18B20_GetTemp(void)
{
    unsigned char LSB, MSB;
    int Raw;
    float Temp;
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

    return Temp;
}