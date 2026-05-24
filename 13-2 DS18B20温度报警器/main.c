#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include <STDIO.H> 
#include "key.h"
#include "Timer0.h"
#include "AT24C02.h"

float Temperature;
unsigned char KeyNum;
char TH , TL ; //温度报警值
void main()
{
    /*-------------------初始化-------------------*/
    Temperature = DS18B20_GetTemp();
    Delay750ms();//延时750ms这时候才能转化完。
    LCD_Init();
    Timer0Init();
    LCD_ShowString(1, 1, "Temp:");
    LCD_ShowString(2, 1, "TH:");
    LCD_ShowString(2, 9, "TL:");


    /*--------------读取保存的报警值---------------*/ 
    TH = AT24C02_RandRead(0);
    TL = AT24C02_RandRead(1);
    if ((TH > 125) || (TL < -55) || (TH <= TL))
    {   // 简单的有效性检查
        TH = 31;
        TL = 26;
        // 将有效值写回 EEPROM
        AT24C02_WriteByte(0, TH);
        Delay(5);
        AT24C02_WriteByte(1, TL);
        Delay(5);
    }


    while (1)
    {
        /*-----------------------获取温度----------------------*/
        
        Temperature = DS18B20_GetTemp();
        /*-----------------------LCD显示-----------------------*/
        LCD_ShowSignedNum(1, 6, Temperature, 2);		//显示温度整数部分
		LCD_ShowChar(1,9,'.');		//显示小数点
        LCD_ShowNum(1, 10, (unsigned long)(Temperature * 100) % 100, 2);
        LCD_ShowSignedNum(2, 4, TH, 3);
        LCD_ShowSignedNum(2, 12, TL, 3);
        /*----------------------获取按键-----------------------*/
        KeyNum = Key();
        if (KeyNum)
        {
            if (KeyNum == 1)
            {
                TH++;
                if (TH > 125)
                {
                    TH = 125;
                }
            }
            if (KeyNum == 2)
            {
                TH--;
                if (TH <= TL)
                {
                    TH++;
                }
            }
            if (KeyNum == 3)
            {
                TL++;
                if (TL >= TH)
                {
                    TL--;
                }
            }
            if (KeyNum == 4)
            {
                TL--;
                if (TL <= -55)
                {
                    TL = -55;
                }
            }
            /*-------------------范围存入AT24C02中-------------------*/
            AT24C02_WriteByte(0, TH);
            Delay(5);
            AT24C02_WriteByte(1, TL);
            Delay(5);
        }
        /*----------------------温度状态提示-----------------------*/
        if (Temperature < TL)
        {
            LCD_ShowString(1,13,"OV:L");
        }
        else if(Temperature>TH)
        {
            LCD_ShowString(1,13,"OV:H");
        }
        else
        {
            LCD_ShowString(1,13,"0K! ");
        }
    }
}

