#include <regx52.h>

void Timer0Init()
{
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x01;
    TF0 = 0;
    TR0 = 1;//定时器开启
    TH0 = 0xFC;
    TL0 = 0x18;
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}

/*void Timer0_Rountine() interrupt 1
{
    static unsigned int T0Count;
    TH0 = 0xFC;
    TL0 = 0x18;
    T0Count ++;
    if (T0Count == 1000)
    {
        T0Count = 0;
    }
}*/