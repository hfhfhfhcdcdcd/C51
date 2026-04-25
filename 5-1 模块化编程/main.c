#include <regx52.h>
#include "Delay.h"
#include "Nixie.h"

void main()
{
    while (1)
    {
        // Delay(500);
        // P2 = 0xfe;
        // Delay(700);
        // P2 = 0xff;
        Nixie(1, 1);
        Delay(1);
        Nixie(2, 2);
        Delay(1);
        Nixie(3, 3);
        Delay(1);
        Nixie(4, 4);
        Delay(1);
        Nixie(5, 5);
        Delay(1);
        Nixie(6, 6);
        Delay(1);
        Nixie(7, 7);
        Delay(1);
        Nixie(8, 8);
        Delay(1);
    }
}