#include <REGX52.H>
#include <intrins.h>

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
   
    while (1)
    {
        /*
        1111 1110
        1111 1101
        1111 1011
        1111 0111
        1110 1111
        1101 1111
        1011 1111
        0111 1111
转化成十六进制为：
        0xFE、0xFD、0xFB、0xF7、0xEF、0xDF、0xBF、0x7F 
        */
        P2 = 0xFE;
        Delay500ms();
        P2 = 0xFD;
        Delay500ms();
        P2 = 0xFB;
        Delay500ms();
        P2 = 0xF7;
        Delay500ms();
        P2 = 0xEF;
        Delay500ms();
        P2 = 0xDF;
        Delay500ms();
        P2 = 0xBF;
        Delay500ms();
        P2 = 0xF7F;
        Delay500ms();
    }
}