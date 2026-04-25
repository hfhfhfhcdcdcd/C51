#include <regx52.h>
#include "LCD1602.h"
#include "delay.h"

int Result=0;
void main()
{
    LCD_Init();
    
    while (1)
    {
        if (Result==15)
        {
            Result = 0;
        }
				
        LCD_ShowSignedNum(1, 1, Result, 3);
        Result++;
        Delay(900);
    }
}