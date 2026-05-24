#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data);

char AT24C02_RandRead(unsigned char WordAddress);

#endif 