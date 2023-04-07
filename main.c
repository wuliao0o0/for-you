#include <REGX51.H>
#include "step.h"
#include "delay.h"
#include "ESP8266.H"
#include "uart.h"
#include "OLED.h"
#include "BMP.H"
#include "distance.H"
#include "distance_timeCount.h"

unsigned char Recive_table[4];
unsigned int commodityNum =10;//货物总量
unsigned int i=0;//distance是用来接收超声波测距的数据的变量
unsigned char stepFlag=0;//步进电机的启停信号标志
unsigned char cnFlag=0;//货物是否位空标记


void print()
{
	OLED_print_single_word(1,2,"现",0);
	OLED_print_single_word(1,4,"有",0);
	OLED_print_single_word(1,6,"货",0);
	OLED_print_single_word(1,8,"物",0);
	OLED_print_text(1,10,":",0);
}

void main (void)
{
	unsigned int distance;
	Uart_Init();
	Timer0Init();
	OLED_init();
	Esp8266_Init();

	while(1)
	{
		distance=distance_Data();
//		if(P3_3==0)
//		{
//			stepFlag=0;
//			MotoStop();
//			if(commodityNum!=0)
//			{
//				commodityNum--;
//			}else{cnFlag=1;OLED_clear();}
//			
//		}
//		if(stepFlag==1)
//		{
//			MotorRun(360,0,2);
//			delay(10);
//		}
//		if(cnFlag==1)
//		{
//			OLED_print_text(1,2,"N U L L !",0);
//		}else 
//		{
//			print();
//			OLED_ShowNum(1,12,commodityNum);	
//		}


	}
}

void UART_Routine(void) interrupt 4
{

	if(RI==1)
	{
		RI = 0;
		if(i>3){i=0;}else{Recive_table[i++] = SBUF;}
		if(Recive_table[0]=='o' && Recive_table[1]=='p' && Recive_table[2]=='e'&& Recive_table[3]=='n')
		{
			stepFlag=1;
			Uart_SendStr("123");
		}

	}
} 
