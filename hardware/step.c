#include  "reg51.h"
#include <intrins.h>
#include "delay.h"
#define uint unsigned int
#define uchar unsigned char
uchar mark;
sbit MA=P1^0;
sbit MB=P1^1;
sbit MC=P1^2;
sbit MD=P1^3;

/*
angle：角度，范围[0,360]
drct：旋转方向，0：顺时针，1：逆时针
speed：转速，范围[1,100]
*/
void MotorRun(uint angle,uint drct,uint speed)
{
	uint step=0;
	uint nangle;
	nangle=(long)512*angle/45;//将角度换算成拍数，计算结果自动取整
	if(drct==0)
	{
		while(nangle--)
		{
			switch(step)//8拍方式驱动，每拍转(5.265/64)度
			{
				case 0:MA=1;MB=0;MC=0;MD=0;break;
				case 1:MA=1;MB=1;MC=0;MD=0;break;
				case 2:MA=0;MB=1;MC=0;MD=0;break;
				case 3:MA=0;MB=1;MC=1;MD=0;break;
				case 4:MA=0;MB=0;MC=1;MD=0;break;
				case 5:MA=0;MB=0;MC=1;MD=1;break;
				case 6:MA=0;MB=0;MC=0;MD=1;break;
				case 7:MA=1;MB=0;MC=0;MD=1;break;
			}
			
			step%=7;
			step++;
			delay(speed);//这里可以适当改动，延时时间短则转速快，但是时间太短会造成电机堵转（不转了）
		}
		mark=1;
	}
	else if(drct==1)
	{
		while(nangle--)
		{
			switch(step)
			{
				case 0:MA=1;MB=0;MC=0;MD=1;break;
				case 1:MA=0;MB=0;MC=0;MD=1;break;
				case 2:MA=0;MB=0;MC=1;MD=1;break;
				case 3:MA=0;MB=0;MC=1;MD=0;break;
				case 4:MA=0;MB=1;MC=1;MD=0;break;
				case 5:MA=0;MB=1;MC=0;MD=0;break;
				case 6:MA=1;MB=1;MC=0;MD=0;break;
				case 7:MA=1;MB=0;MC=0;MD=0;break;
			}
			step%=7;
			step++;
			delay(speed);//这里可以适当改动，延时时间短则转速快，但是时间太短会造成电机堵转（不转了）			
		}
		mark=0;
	}
	
}
void MotoStop()
{
MA=0;MB=0;MC=0;MD=0;
}