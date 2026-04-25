#include <regx52.h>
#include "LCD1602.h"

void main()
{
    LCD_Init();
    LCD_ShowChar(1, 1, 'A');
    LCD_ShowString(1, 3, "LV LOVE YU");
    LCD_ShowNum(1, 14, 123, 3);
    LCD_ShowNum(2, 1, 2, 1);
    LCD_ShowSignedNum(2, 2, -5, 1);
    LCD_ShowString(2, 4, "=-3");
    LCD_ShowHexNum(2, 8, 0xff, 2);
    LCD_ShowBinNum(2, 11, 0x0C, 6);
    while (1)
    {
        
    }
}