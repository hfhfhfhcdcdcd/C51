#include "regx52.h"
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Num, Addr, Cmd;


void main()
{
    //初始化
    IR_Init();
    LCD_Init();
    //显示
    LCD_ShowString(1, 1, "Addr:");
    LCD_ShowString(1, 7, "Cmd:");
    LCD_ShowString(1, 12, "Num:");
    while (1)
    {
        if (IR_GetDataFlag() || IR_GetRepeatFlag())
        {
            Addr = IR_GetAddress(); //获取地址码
            Cmd = IR_GetCommand(); //获取命令码
            if (Cmd == 0x45)
            {
                Num = 50;
            }
            if (Cmd == 0x46)
            {
                Num = 100;
                
            }
            if (Cmd == IR_VOL_MINUS)
            {
                Num--;
                if (Num == 255) { Num = 100; }
            }
            if (Cmd == IR_VOL_ADD)
            {
                Num++;
                if (Num == 101) { Num = 0; }
            }
            
            LCD_ShowHexNum(2, 1, Addr, 2);
            LCD_ShowHexNum(2, 7, Cmd, 2);
            LCD_ShowNum(2, 12, Num, 3);
        }
    }
}
