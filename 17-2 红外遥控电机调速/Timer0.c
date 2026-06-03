#include <regx52.h>

void Timer0Init()
{
    TMOD = TMOD & 0xF0;
    TMOD = TMOD | 0x01;
    TF0 = 0;
    TR0 = 0;
    TH0 = 0;
    TL0 = 0;
}

void Timer0_SetCounter(unsigned int Value)
{
    TH0 = Value / 256;
    TL0 = Value % 256;
}

unsigned int Timer0_GetCounter(void)
{
    return (TH0 << 8) | TL0;
}

void Timer0_Run(unsigned char Flag)
{
    TR0 = Flag;
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

