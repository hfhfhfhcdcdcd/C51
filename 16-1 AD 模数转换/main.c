#include "regx52.h"
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue0, ADValue1;
void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "AD_8:");
    LCD_ShowString(2, 1, "AD_12:");
    while (1)
    {
        ADValue0 = XPT2046_ReadXP(XPT2046_XP8);
        LCD_ShowNum(1, 7, ADValue0, 4);
        Delay(10);
        ADValue1 = XPT2046_ReadXP(XPT2046_XP12);
        LCD_ShowNum(2, 7, ADValue1, 4);
        Delay(10);
    }
}
