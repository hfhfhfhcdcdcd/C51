#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char Onewire_Init(void);
void OneWire_SendBit(bit Bit);
bit OneWire_ReceiveBit(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte(void);

#endif
