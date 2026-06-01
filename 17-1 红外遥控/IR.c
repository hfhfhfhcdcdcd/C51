#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"
#define STARTP (13500/1.085)+500
#define STARTN (13500/1.085)-500

#define REPEATP (11250/1.085)+500
#define REPEATN (11250/1.085)-500

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init(void)
{
	Timer0Init();
	Int0_Init();
}

void Int0_Routin(void) interrupt 0
{
	if (IR_State == 0)
	{
		
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if (IR_State == 1)
	{
		
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if ((IR_Time>STARTN) && (IR_Time<STARTP))
		{
			P2 = 0x00;
			IR_State = 2;
		}
		else if (IR_Time>REPEATN && IR_Time<REPEATP)
		{
			P2=0xcc;
			IR_RepeatFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}
		else
		{
			IR_State = 1;
		}
	}
	
}