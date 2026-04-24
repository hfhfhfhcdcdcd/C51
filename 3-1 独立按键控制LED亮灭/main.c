#include <regx52.h>

void main()
{
    while (1)
    {
        if (P3_1 == 0)
        {
            P2_0 = 0;
        }
        else
        {
            P2_0 = 1;//led off
        }
    }
    
}
