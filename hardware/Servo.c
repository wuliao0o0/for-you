#include <REGX51.H>
#include "timer0.h"
sbit pwm=P0^0;
unsigned int counter;
float compare;
void Servo_Init(void)
{
	Timer0Init();
	compare=1;
	counter=0;
}
void Servo_set(float angle)
{
	
	compare=(angle/90+0.5)*2;
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0x48;	
	TH0 = 0xff;
	if(counter<compare)
	{
		pwm=1;
	}
	else
	{
		pwm=0;
	}
	counter++;
	counter%=40;//超过20ms计数器归零
	
}