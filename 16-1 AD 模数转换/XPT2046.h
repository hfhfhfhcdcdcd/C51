#ifndef __XPT2046_H__
#define __XPT2046_H__ 

#define XPT2046_XP8     0x9C
#define XPT2046_YP8     0xDC
#define XPT2046_VBAT8   0xAC
#define XPT2046_AUX8    0xEC

#define XPT2046_XP12     0x94
#define XPT2046_YP12     0xD4
#define XPT2046_VBAT12   0xA4
#define XPT2046_AUX12    0xE4

unsigned int XPT2046_ReadXP(unsigned char Cmd);

#endif
