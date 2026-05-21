#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "Nixie.h"

#define DELAY_MS 2
unsigned char KeyNum;
unsigned char Count_10ms, Count60,Count_s,Count_min;
bit En=0;
void ClockInit(void)
{
    Nixie(1, 0);
    Delay(DELAY_MS);
    Nixie(2, 0);
    Delay(DELAY_MS);
    Nixie(3, 10);
    Delay(DELAY_MS);

    Nixie(4, 0);
    Delay(DELAY_MS);
    Nixie(5, 0);
    Delay(DELAY_MS);
    Nixie(6, 10);
    Delay(DELAY_MS);
    Nixie(7, 0);
    Delay(DELAY_MS);
    Nixie(8, 0);
    Delay(DELAY_MS);
}

void CountClock(void)
{
    if (En == 1)
    {
        Count60++;
        if (Count60 == 60)
        {
            Count60 = 0;
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
    LCD_Init();
    Timer0Init();

    while (1)
    {
        // ClockInit();
        CountClock();
        Nixie(1, Count_min / 10);
        Delay(2);
        Nixie(2, Count_min % 10);
        Delay(2);
        Nixie(3, 10);
        Delay(2);
        Nixie(4, Count_s / 10);
        Delay(2);
        Nixie(5, Count_s % 10);
        Delay(2);
        Nixie(6, 10);
        Delay(2);
        Nixie(7, Count60 / 10);
        Delay(2);
        Nixie(8, Count60 % 10);
        Delay(2);

    }
}

void Timer0_Rountine() interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x18;
    KeyNum = Key();
    switch (KeyNum)
    {
        case 1:En = 1; break;
        case 2:En = 0; break;
        case 3:
        {
            AT24C02_WriteByte(0, Count_min);//分
            Delay(5);
            AT24C02_WriteByte(1, Count_s);//秒
            Delay(5);
            AT24C02_WriteByte(2, Count60);//ms
            Delay(5);
        }break;
        case 4:
        {
            En = 0;
            Count_min = AT24C02_RandRead(0);
            Count_s = AT24C02_RandRead(1);
            Count60 = AT24C02_RandRead(2);
        }break;
        default:;break;
    }


}