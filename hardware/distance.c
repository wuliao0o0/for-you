#include <REGX51.H>
#include "delay.h"
#include "distance_timeCount.h"
#include "distance.H"
#include "OLED.h"
sbit trig=P1^2;//接收端
sbit echo=P1^3;//发射端
unsigned int Distance=0;
unsigned int Time,flag,flag_distance;
void SR04_Start()
{
	trig=1;
	Delay10us();
	trig=0;//拉高后延迟在拉低保证高电平的时间
}

unsigned int distance_Data()
{
	SR04_Start();
	while(!echo);
	TR0=1;
	while(echo);
	TR0=0;
	Time=TH0*256+TL0;//将TH0（8bit）与TL0(8bit)的值加起来，一个约为1us.如255*256+255=65535
	TH0=0;
	TL0=0;
	Distance=(Time*1.7)/100;//1.7为声速340m/s的一半s
	flag_distance=Distance;
	Distance=Distance+flag_distance/10+1;//这个是计算出的距离加上误差，可能是有温度造成的
	if(flag==1)
	{
		flag=0;
	}else
	{
		OLED_clear();
		OLED_ShowNum(2,2,Distance);
		OLED_print_char(2,5,'c',0);
		OLED_print_char(2,6,'m',0);

	}
	return Distance;
}
void Timer0_Routine() interrupt 1
{	
	flag=1;//当定时器满时触发中断后的操作

}