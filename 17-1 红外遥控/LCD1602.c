#include <REGX52.H>

sbit LCD_E  = P2 ^ 7;
sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5; // 1 读 0 写
#define LCD_DATAPORT P0


void LCD_Delay()		//@12.000MHz  1ms
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCmd(unsigned char cmd)
{
	LCD_RS = 0; // 写命令
	LCD_RW = 0; // 写数据
	LCD_DATAPORT = cmd; // 并行写
	LCD_E = 1; // 使能
	LCD_Delay();// 延时1ms
	LCD_E = 0; // 使能
	LCD_Delay();// 延时1ms
}

void LCD_WriteData(unsigned char cmd)
{
	LCD_RS = 1; // 写命令
	LCD_RW = 0; // 写数据
	LCD_DATAPORT = cmd; // 并行写
	LCD_E = 1; // 使能
	LCD_Delay();// 延时1ms
	LCD_E = 0; // 使能
	LCD_Delay();// 延时1ms
}
/**
  * @brief: Result = x^y;
  * @param:x,y: x的y次方
  * @retval:Result 
  */
int LCD_Pow(int x,int y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0;i < y;i++)
	{
		Result *= x;
	}
	return Result;
}
void LCD_Init(void)
{
	LCD_WriteCmd(0x38);// 2行显示，5*7点阵
	LCD_WriteCmd(0x0c);// 显示开，光标关闭
	LCD_WriteCmd(0x06);//光标右移
	LCD_WriteCmd(0x01);//清屏
}
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1)
	{
		LCD_WriteCmd(0x80 | (Column - 1)); // 第一行地址
	}
	else
	{
		LCD_WriteCmd(0x80 | (Column - 1 + 0x40));// 第二行地址
	}
}
void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

void LCD_ShowString (unsigned char Line, unsigned char Column, unsigned char* String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = 0;String[i] != '\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Len)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Len;i > 0;i--)
	{
		LCD_WriteData(0x30+(Number / LCD_Pow(10, i - 1) % 10 )); // 逐位取出数字
	}
}

void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Len)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line, Column);
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for (i = Len;i > 0;i--)
	{
		LCD_WriteData(0x30+(Number1 / LCD_Pow(10, i - 1) % 10 )); // 逐位取出数字
	}
}

void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Len)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line, Column);
	for (i = Len;i > 0;i--)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData(0x30 + SingleNumber); // 逐位取出数字
		}
		else
		{
			LCD_WriteData('A' + SingleNumber-10);
		}
	}
}

void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Len)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Len;i > 0;i--)
	{
		LCD_WriteData(0x30+(Number / LCD_Pow(2, i - 1) % 2 )); // 逐位取出数字
	}
}