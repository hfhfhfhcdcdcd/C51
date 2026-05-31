#include "regx52.h"
#include "Delay.h"
#include "key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit DA = P2 ^ 1;
unsigned char Counter, Compare,i; //计数器和比较值

void main()
{
    Timer0Init();
    Compare = 5; //占空比
    while (1)
    {
        for (i = 0;i < 100;i++)
        {
            Compare = i;
            Delay(5);
        }
        for (i = 100;i > 0;i--)
        {
            Compare = i;
            Delay(5);
        }

    }
}

void Timer0_Rountine() interrupt 1
{
    TH0 = 0xFF;//1us来一次中断
    TL0 = 0x9C;
    Counter++;
    Counter %= 100;
    if (Counter < Compare)
    {
        DA = 0;
    }
    else
    {
        DA = 1;
    }
}