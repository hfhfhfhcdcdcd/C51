#include <regx52.h>
#include "Delay.h"
/**
  * @brief: 0、1、2、3、4、5、6、7、8、9、-、不显示
  */
unsigned char NixieNumber[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40,0x00 };
/**
  * @brief: 定时器扫描loop函数，loop函数里面调用scan函数，scan函数把Nixie_Buf里面的数字当作自己参数number，而这个number就是Nixie_number数组的索引。也就是把NixieNumber里面的第11位取出来，并让定时器把这个索引对应的数字扫描在数码管上。
  */
unsigned char Nixie_Buf[9] = { 0,11,11,11,11,11,11,11,11 };


/**
  * @brief: 设置Nixie_Buf缓存器的数字。这些数字是要被显示在数码管上的。在主循环里面调用这个函数就可以更改缓存器里面的数字。而数码管的动态显示是由定时器来控制的。定时器主管扫描这个缓存器里面的数字，并把它显示在数码管上。
  * @param:要显示的位置Location，要显示的数字Number
  * @retval:无
  */
void Nixie_Set(unsigned char Location, unsigned char Number)
{
    Nixie_Buf[Location] = Number;
}



/**
  * @brief: 用主循环来扫描数码管的函数再出去花了一年再用这个函数就可以扫描数码管
  * @param:要显示的位置Location，要显示的数字Number
  * @retval:无
  */
void Nixie_Scan(unsigned char Location, unsigned char Number)
{
    P0 = 0x00;
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



/**
  * @brief: 在定时器里面调用内科两毫秒调用一次就可以实现扫描数码管的功能了.一里面调用了Nixie_Scan这个函数这个函数第一位是数码管的位,第二位是需要显示的数字。Nixie_Buf是一个缓存器，里面存着想要显示的数字。默认不显示。
  * @param:无
  * @retval:无
  */
void Nixie_Loop(void)
{
    static unsigned char i=1;
    Nixie_Scan(i, Nixie_Buf[i]);
    i++;
    if (i == 9)i = 1;
}