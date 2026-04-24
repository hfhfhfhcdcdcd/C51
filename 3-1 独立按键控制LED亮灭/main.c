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
        if (i <= 7)
        {
            if (P3_1 == 0)
            {
                P2 &= ~(1 << i);
                
            }
            else
            {
                P2 |= ~(1 << i);//led off
                
            }
            
            
        }
        else
        {
            i = 0;
        }
        
    }
    i = i + 1;
        Delay1ms(1000);
}
