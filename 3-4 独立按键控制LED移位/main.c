#include <regx52.h>

void Delay1ms(unsigned int xms);
unsigned char LEDNum;
void main()
{
    P2 = 0xFE;
    
    while (1)
    {
        if (P3_1 == 0)
        {
            Delay1ms(20);
            while (P3_1 == 0);
            Delay1ms(20);

            LEDNum++;
            if (LEDNum >= 8)
            {
                LEDNum = 0;
            }
            P2 = ~(0x01 << LEDNum);
        }
        if (P3_0 == 0)
        {
            Delay1ms(20);
            while (P3_0 == 0);
            Delay1ms(20);

            if (LEDNum == 0)
                LEDNum = 7;
            // 当处于最低位，也就是第一个灯亮无法右移的时候。就直接把它变成最后一个灯。第八个灯亮。
            else
                LEDNum--;
            // LED Nam减减就相当于。 11111110少向左移一个单位。
            P2 = ~(0x01 << LEDNum);
        }
    }
}

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