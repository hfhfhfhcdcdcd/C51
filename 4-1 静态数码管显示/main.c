#include <regx52.h>

unsigned char NixieNumber[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f };

void Nixie(unsigned char Location, Number);
void main()
{
    while (1)
    {
        Nixie(1, 1);
        Nixie(2, 2);
        Nixie(3, 3);
        Nixie(4, 4);
        Nixie(5, 5);
        Nixie(6, 6);
        Nixie(7, 7);
        Nixie(8, 8);
    }
}

void Nixie(unsigned char Location, Number)
    {
        switch (Location)
        {
            case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;//实际是led7，但是从左往右第8,人为把他记为第一个，因为顺眼
            case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;//实际是led6，但是从左往右第7
            case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;//实际是led5，但是从左往右第6
            case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;//实际是led4，但是从左往右第5
            case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;//实际是led3，但是从左往右第4
            case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;//实际是led2，但是从左往右第3
            case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;//实际是led1，但是从左往右第2
            case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;//实际是led0，但是从左往右第1
            default:break;
        }
        P0 = NixieNumber[Number];
    }