#include <regx52.h>

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
    while (xms)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);
        xms--;
    }
    
}

void main()
{
    int i = 0;
    while (1)
    {
        if ((P3_1 == 0)&&(i<8))
        {
            P2=0xff;
            Delay1ms(20);
            while (P3_1 == 0);
            Delay1ms(20);
            P2 &= ~(1 << i);
            i++;
            
        }
        if (i >= 8)
        {
            i = 0;
        }
    }
}