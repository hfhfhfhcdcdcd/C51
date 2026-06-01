#include "regx52.h"

void Int0_Init(void)
{
    //初始化外部中断0
    // P3 = 0xFF;
    IT0 = 1;    //下降沿触发
    IE0 = 0;    //
    EX0 = 1;    //允许外部中断0
    PX0 = 1;    //外部中断0优先级
    EA  = 1;     //开总中断
    
}    

/*
void Int0_Routin(void) interrupt 0
{
	 
}
*/
