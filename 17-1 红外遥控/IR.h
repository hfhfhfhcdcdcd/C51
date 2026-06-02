#ifndef __IR_H__
#define __IR_H__

void IR_Init(void);
unsigned char IR_GetDataFlag(void);
unsigned char IR_GetRepeatFlag(void);
unsigned char IR_GetAddress(void);
unsigned char IR_GetCommand(void);
#endif
