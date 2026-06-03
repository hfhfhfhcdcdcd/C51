#include <regx52.h>

void Timer1Init()
{
    TMOD = TMOD & 0x0F;
    TMOD = TMOD | 0x10;
    TF1 = 0;
    TR1 = 1;
    TH1 = 0xFF;
    TL1 = 0x9C;
    ET1 = 1;
    EA = 1;
    PT1 = 0;
}

/*
void Timer1_Rountine() interrupt 3
{
    static unsigned int T1Count;
    TH1 = 0xFC;
    TL1 = 0x18;
    T1Count ++;
    if (T1Count == 1000)
    {
        T1Count = 0;
    }
}*/

