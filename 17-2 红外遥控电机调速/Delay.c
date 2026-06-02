#include "INTRINS.H"

void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
    while (xms)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);
        xms--;
    }
    
}

void Delay500us(unsigned int xum)		//@12.000MHz
{
    while (xum)
    {
        unsigned char i;
        _nop_();
        i = 247;
        while (--i);
        xum--;
    }
}

void Delay750ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 6;
	j = 180;
	k = 26;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void Delay10us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 2;
	while (--i);
}


void Delay15us()		//@12.000MHz
{
	unsigned char i;

	i = 5;
	while (--i);
}

void Delay480us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 237;
	while (--i);
}


void Delay80us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 37;
	while (--i);
}

void Delay50us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 22;
	while (--i);
}

void Delay5us()		//@12.000MHz
{
	_nop_();
}

