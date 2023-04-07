#include <REGX51.H>
#include <intrins.h>
void delay(int xms)
{
	unsigned char i, j;
	while(xms!=0)
	{
	 _nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	 xms--;
 } 

}
void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 10;
	while (--i);
}


void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}


