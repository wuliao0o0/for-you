#include <REGX51.H>


void Timer0Init()		//@11.0592MHz
{
	TMOD =0x01;		//设置定时器模式
	TL1 = 0;		//设置定时初值
	TH1 = 0;		//设置定时初值
	ET0=1;
	TR0 = 0;
    EA=1;
}