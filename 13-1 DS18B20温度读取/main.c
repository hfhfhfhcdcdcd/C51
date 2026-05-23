#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "DS18B20.h"
unsigned char AckFlag;
int Temperature;
void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");
    while (1)
    {
        Temperature = DS18B20_GetTemp();
        LCD_ShowSignedNum(2, 1, Temperature, 2);
    }
}
