#include <regx52.h>
#include "Delay.h"

unsigned char Key_Number;

unsigned char Key(void)
{
    unsigned char Temp;
    Temp = Key_Number;
    Key_Number = 0;
    return Temp;
}

unsigned char Key_GetState()
{
    unsigned char KeyNumber = 0;
    if (P3_1 == 0) { KeyNumber = 1; }
    if (P3_0 == 0) { KeyNumber = 2; }
    if (P3_2 == 0) { KeyNumber = 3; }
    if (P3_3 == 0) { KeyNumber = 4; }
    return KeyNumber;
}

void Key_Loop(void)
{
    static unsigned char Nowstate, Lastsate;
    Lastsate = Nowstate;
    Nowstate = Key_GetState();

    if (Lastsate == 1 && Nowstate == 0)
    {
        Key_Number = 1;
    }
    if (Lastsate == 2 && Nowstate == 0)
    {
        Key_Number = 2;
    }
    if (Lastsate == 3 && Nowstate == 0)
    {
        Key_Number = 3;
    }
    if (Lastsate == 4 && Nowstate == 0)
    {
        Key_Number = 4;
    }

}