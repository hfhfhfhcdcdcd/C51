#include "regx52.h"
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Num, Addr, Cmd;


void main()
{
    //初始化
    LCD_Init();
    IR_Init();
    //显示
    LCD_ShowString(1, 1, "Addr:");
    LCD_ShowString(1, 7, "Cmd:");
    LCD_ShowString(1, 12, "Num:");
    while (1)
    {
        if (IR_GetDataFlag)
        {
            Addr = IR_GetAddress(); //获取地址码
            Cmd = IR_GetCommand(); //获取命令码
            if (Cmd == 0x45)
            {
                Num = 50;
            }
            else if (Cmd == 0x46)
            {
                Num = 100;
                
            }
            else if (Cmd == 0x15)
            {
                Num --;
            }
            else if (Cmd == 0x09)
            {
                Num ++;
            }
            
            LCD_ShowHexNum(2, 1, Addr, 2);
            LCD_ShowHexNum(2, 7, Cmd, 2);
            LCD_ShowNum(2, 12, Num, 3);
            
                 
        }
        

    }
}
