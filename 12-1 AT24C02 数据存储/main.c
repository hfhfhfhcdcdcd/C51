#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"

unsigned char KeyNum;
signed char  Count, Data;

void main()
{
    LCD_Init();
    while (1)
    { 
        KeyNum = Key();
        switch (KeyNum)
        {
        case 1:{LCD_Init();Count++; LCD_ShowSignedNum(1, 1, Count, 3);}break;
        case 2:{LCD_Init();Count--; LCD_ShowSignedNum(1, 1, Count, 3);}break;
        case 3:
        {
            AT24C02_WriteByte(0, Count);
            Delay(5);
            // AT24C02_WriteByte(1, Count % 256);
            // Delay(5);
            LCD_ShowSignedNum(1, 1, Count, 3);
            LCD_ShowString(1, 10, "Write");
        }break;
        case 4:
        {
            Data = AT24C02_RandRead(0);
                // * 10 + AT24C02_RandRead(1);
            LCD_ShowSignedNum(1, 1, Data, 3);
            LCD_ShowString(1, 10, "read");
        }break;
        default:break;
        }
    }
}