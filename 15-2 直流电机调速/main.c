#include "regx52.h"
#include "Delay.h"
#include "key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor = P1 ^ 0;
unsigned char Counter, Compare,KeyNum,Speed; //计数器和比较值

void main()
{
    Timer0Init();
    Compare = 5; //占空比
    while (1)
    {
        KeyNum = Key();
        if (KeyNum == 1)
        {
            Speed++;//速度加
            Speed %= 4;
            if (Speed == 0) { Compare = 0; }
            if (Speed == 1) { Compare = 55; }
            if (Speed == 2) { Compare = 80; }
            if (Speed == 3) { Compare = 100; }
        }
            Nixie_Scan(1, Speed);
    }
}

void Timer0_Rountine() interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0x9C;
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