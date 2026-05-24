#ifndef __DS18B20_H__
#define __DS18B20_H__

float DS18B20_GetTemp(void);
bit DS18B20_SetAlarmThreshold(signed char th, signed char tl);

#endif
