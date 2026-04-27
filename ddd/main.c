#include <regx52.h>
#include "stdio.h"
#include "LCD1602.h"


void main()
{
    LCD_Init();
    while (1)
    {
        
        LCD_ShowString(2, 1, "lvlvlv");
        LCD_ShowNum(1, 1, 123, 3);
        P2_0 = 0;

    }
}
	