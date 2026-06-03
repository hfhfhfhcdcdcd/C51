#include "regx52.h"
#include "Timer1.h"


sbit Motor = P1 ^ 0;
unsigned char Counter, Compare;

void Motor_Init(void)
{
    Timer1Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
    Compare = Speed;
}
void Timer1_Rountine() interrupt 3
{
    TH1 = 0xFF;
    TL1 = 0x9C;
    Counter++;
    Counter %= 100;
    if (Counter < Compare)
    {
        Motor = 1;
    }
    else
    {
        Motor = 0;
    }
}
