#include "regx52.h"
#include "LCD1602.h"
#include "delay.h"

void main()
{
    LCD_Init();
    LCD_ShowChar(1, 1, 'A');
    LCD_ShowString(1, 2, "\"hello\'\""); // 显示字符串
    LCD_ShowNum(1, 11, 6776, 4);
    LCD_ShowSignedNum(2, 1, -6699, 4);
    LCD_ShowHexNum(2, 7, 0xC3, 2);
    LCD_ShowBinNum(2, 9, 0xAA, 8);
    LCD_ShowChar(1, 16, 0xDF); // 显示特殊符号。
    LCD_ShowChar(1, 18, 0xE0); // 显示特殊符号α
    while (1)
    {
        LCD_WriteCmd(0x18); // 左移
        Delay750ms();

    }
}