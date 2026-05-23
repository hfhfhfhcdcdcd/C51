#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include <STDIO.H> 

float Temperature;
void main()
{
	// Temperature = DS18B20_GetTemp();
	LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");
    while (1)
    {
        Temperature = DS18B20_GetTemp();
        LCD_ShowSignedNum(2,1,Temperature,2);		//显示温度整数部分
		LCD_ShowChar(2,4,'.');		//显示小数点
		LCD_ShowNum(2,5,(unsigned long)(Temperature*10000)%10000,4);
    }
}