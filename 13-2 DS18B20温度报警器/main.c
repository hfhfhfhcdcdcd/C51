#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
#include <STDIO.H> 
#include "key.h"
#include "Timer0.h"

#define LEDTL P2_7
#define LEDTH P2_3
#define BEEP  P2_5 //蜂鸣器

float Temperature;
unsigned char KeyNum;
char TH = 33;
char TL = 22;//按键值
void main()
{
    Temperature = DS18B20_GetTemp();
    Delay750ms();//延时750ms这时候才能转化完。
    LCD_Init();
    Timer0Init();
    LCD_ShowString(1, 1, "Temp:");

    while (1)
    {
        KeyNum = Key();
        Temperature = DS18B20_GetTemp();
        LCD_ShowSignedNum(1,6,Temperature,2);		//显示温度整数部分
		LCD_ShowChar(1,9,'.');		//显示小数点
        LCD_ShowNum(1, 10, (unsigned long)(Temperature * 100) % 100, 2);

        LCD_ShowString(2, 1, "TH:");
        LCD_ShowString(2, 9, "TL:");
        LCD_ShowSignedNum(2, 4, TH, 3);
        LCD_ShowSignedNum(2, 12, TL, 3);
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
        }
        if(Temperature<TL)
        {
            LCD_ShowString(1,13,"ER!");
        }
        else if(Temperature>TH)
        {
            LCD_ShowString(1,14,"ER!");
        }
        else
        {
            LCD_ShowString(1,14,"0K!");
        }
    }
}

