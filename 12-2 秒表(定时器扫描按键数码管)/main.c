#include "regx52.h"
#include "delay.h"
#include "LCD1602.h"
#include "key.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "Nixie.h"

#define DELAY_MS 2
unsigned char KeyNum,Temp;

void main()
{
    Timer0Init();
    while (1)
    {
        KeyNum = Key();
        Nixie_Set(1, 0);
        Nixie_Set(2, 0);
        Nixie_Set(3, 10);
        Nixie_Set(4, 0);
        Nixie_Set(5, 0);
        Nixie_Set(6, 10);
        Nixie_Set(7, 0);
        Nixie_Set(8, 0);
        if (KeyNum)
        {
            
            Nixie_Set(3, KeyNum);
        }

    }
    



}

void Timer0_Rountine() interrupt 1
{
    static unsigned int T0Count1,T0Count2;
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
}
