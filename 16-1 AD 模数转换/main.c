#include "regx52.h"
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue;
void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "AD");
    LCD_ShowString(1, 6, "Temp");
    LCD_ShowString(1, 12, "light");
    while (1)
    {
        ADValue = XPT2046_ReadXP(XPT2046_XP8);//滑动电阻
        LCD_ShowNum(2, 1, ADValue, 3);

        ADValue = XPT2046_ReadXP(XPT2046_YP8);//热敏电阻
        LCD_ShowNum(2, 6, ADValue, 3);

        ADValue = XPT2046_ReadXP(XPT2046_VBAT8);//光敏电阻
        LCD_ShowNum(2, 12, ADValue, 3);
        Delay(10);
    }
}
