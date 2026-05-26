#include "regx52.h"
// #include "Delay.h"
sbit LED = P2 ^ 0;

void delay1(unsigned char i)
{
    while (i--);
}

void main()
{
    unsigned char Time,i;
    while (1)
    {
        for (Time = 0;Time < 100;Time++)
        {
            for (i = 0;i < 30;i++)
            {
                LED = 0;
                delay1(Time);
                LED = 1;
                delay1(100 - Time);
            }
        }

        for (Time = 100;Time > 0;Time--)
        {
            for (i = 0;i < 30;i++)
            {
                LED = 0;
                delay1(Time);
                LED = 1;
                delay1(100 - Time);
            }
        }
    }
}