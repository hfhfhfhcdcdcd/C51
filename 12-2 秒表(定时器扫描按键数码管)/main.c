#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "Nixie.h"

#define DELAY_MS 2
unsigned char KeyNum, Temp;
unsigned char En;
unsigned char Count100, Count_s, Count_min;


void CountClock(void)
{
    if (En == 1)
    {
        Count100++;
        if (Count100 == 100)
        {
            Count100 = 0;
            Count_s++;
            if (Count_s == 60)
            {
                Count_s = 0;
                Count_min++;
                if (Count_min == 60)
                {
                    Count_min = 0;
                }
            }
        }

    }
}

void main()
{
    Timer0Init();
    while (1)
    {
        KeyNum = Key();
        if (KeyNum)
        {
            switch (KeyNum)
            {
                case 1: En = !En;break;
                case 2:
                {
                    En = 0;
                    Count100 = 0;
                    Count_s = 0;
                    Count_min = 0;
                }break;

                case 3:
                {
                    AT24C02_WriteByte(0, Count_min);//分
                    Delay(5);
                    AT24C02_WriteByte(1, Count_s);//秒
                    Delay(5);
                    AT24C02_WriteByte(2, Count100);//ms
                    Delay(5);
                }break;
                
                case 4:
                {
                    En = 0;
                    Count_min = AT24C02_RandRead(0);
                    Count_s = AT24C02_RandRead(1);
                    Count100 = AT24C02_RandRead(2);
                }    break;
                default:break;
            }
        }
        Nixie_Set(1, Count_min / 10);
        Nixie_Set(2, Count_min % 10);
        Nixie_Set(3, 10);
        Nixie_Set(4, Count_s / 10);
        Nixie_Set(5, Count_s % 10);
        Nixie_Set(6, 10);
        Nixie_Set(7, Count100 / 10);
        Nixie_Set(8, Count100 % 10);

    }
    



}

void Timer0_Rountine() interrupt 1
{
    static unsigned int T0Count1,T0Count2,T0Count3;
    TH0 = 0xFC;
    TL0 = 0x18;
    T0Count1 ++;
    if (T0Count1 == 20)
    {
        T0Count1 = 0;
        Key_Loop();
    }

    T0Count2 ++;
    if (T0Count2 == 2)
    {
        T0Count2 = 0;
        Nixie_Loop();
    }
    T0Count3++;
    if (T0Count3 == 10)
    {
        T0Count3 = 0;
        CountClock();
    }
}
