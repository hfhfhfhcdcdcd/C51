#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"

float T;
void main()
{
	// DS18B20_Convert();
	T = DS18B20_GetTemp();
	Delay(1000);
    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");
    while (1)
    {
        // DS18B20_Convert();
		T = DS18B20_GetTemp();
        if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(2,1,'-');	//显示负号
			T=-T;			//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(2,1,'+');	//显示正号
		}
		LCD_ShowNum(2,2,T,3);		//显示温度整数部分
		LCD_ShowChar(2,5,'.');		//显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);//显示温度小数部分
    }
}
