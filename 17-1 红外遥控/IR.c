#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"


#define STARTP  	(13500/1.085)+500 //开始信号所需的计数次数的下限
#define STARTN  	(13500/1.085)-500

#define REPEATP 	(11250/1.085)+500 //重复信号所需的计数次数的下限
#define REPEATN 	(11250/1.085)-500

#define ZEROP		(1032/1.085)+500  //检测低电平所需的计数次数的下限  
#define ZERON		(1032/1.085)-500

#define ONEP		(2074/1.085)+500  //检测高电平所需的计数次数的下限
#define ONEN 		(2074/1.085)-500


unsigned int  IR_Time;        //两次中断间隔
unsigned char IR_State;       //红外数据处理到那个阶段，所对应的状态码
     
unsigned char IR_Data[4];     //存储4个字节的红外数据，0->3
unsigned char IR_pData;       //指向下一个要存的字节，0->31

unsigned char IR_DataFlag;    //数据是否接收完毕
unsigned char IR_RepeatFlag;  //是否重复接收数据
unsigned char IR_Address;     //红外地址
unsigned char IR_Command;     //红外命令


/**
  * @brief: 红外初始化
  * @param: 无
  * @retval: 无
  */
void IR_Init(void)
{
	Timer0Init();
	Int0_Init();
}

/**
  * @brief: 判断是否接收到接收完毕的信号
  * @param: 无
  * @retval: 1->接收完毕 0->尚未接收完毕
  */
unsigned char IR_GetDataFlag(void)
{
	if (IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief: 判断是否接收到重复信号
  * @param: 无
  * @retval: 1->重复信号 0->无需重复
  */
unsigned char IR_GetRepeatFlag(void)
{
	if (IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;

}

/**
  * @brief:  红外地址  数据接收
  * @param: 无
  * @retval: IR_Address 红外地址
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

/**
  * @brief: 红外命令  数据接收
  * @param: 无
  * @retval: IR_Command 红外命令
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

/**
  * @brief: 红外信号处理中断服务程序
  * @param: 无
  * @retval: 无
  */
void Int0_Routin(void) interrupt 0
{
	if (IR_State == 0)//空闲状态
	{
		Timer0_SetCounter(0);//计数器清零
		Timer0_Run(1);//计数器开始计时
		IR_State = 1;//进入下一个状态
	}
	else if (IR_State == 1)//等待开始信号或者重复信号
	{
		IR_Time = Timer0_GetCounter();//获取计数器值
		Timer0_SetCounter(0);//计数器清零
		if ((IR_Time>STARTN) && (IR_Time<STARTP))//判断是否是开始信号
		{
			IR_State = 2;//进入下一个状态
		}
		else if (IR_Time>REPEATN && IR_Time<REPEATP)//判断是否是重复信号
		{
			IR_RepeatFlag = 1;//重复信号标志
			Timer0_Run(0);//计数器停止计时
			IR_State = 0;//回到空闲状态
		}
		else
		{
			IR_State = 1;//回到空闲状态
		}
	}

	else if (IR_State == 2)//解码0、1码
	{
		IR_Time = Timer0_GetCounter();//获得上一次中断到这一次中断的间隔
		Timer0_SetCounter(0);//获取到时间之后就立马清零，为下一次进中断时做准备

		if ((IR_Time > ZERON) && (IR_Time < ZEROP))
		{
			IR_Data[IR_pData / 8] &= ~(0x01 << (IR_pData % 8));//将应该是0的位--置零
			IR_pData++;//指针后移
		}
		else if ((IR_Time > ONEN) && (IR_Time < ONEP))
		{
			IR_Data[IR_pData/8]|= (0x01 << (IR_pData % 8));//将应该是1的位 置1
			IR_pData++;//指针后移
		}
		else
		{
			IR_pData = 0;//指针清零
			IR_State = 1;//解码失败，重新开始
		}
		if (IR_pData >= 32)
		{
			IR_pData = 0;
			if ((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))//判断校验码是否正确,(高) ---- 命令反码_3 + 命令码_2 + 地址反码_1 + 地址码_0 -----（低）
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);//解码成功，停止计时器
			IR_State = 0;//解码成功，进入空闲状态
		}
	}

}