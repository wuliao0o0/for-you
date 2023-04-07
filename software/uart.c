#include <REGX51.H>
#include "delay.h"
void Uart_Init(void)
{		
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xfd;		//设定定时初值
	TH1 = 0xfd;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	REN=1;
	ES=1;
	EA=1;
}

void Uart_SendChar(unsigned char Word)
{
	SBUF=Word;
	while(TI==0);
	TI=0;
}

void Uart_SendStr(unsigned char *Str)
{	
	while(*Str!='\0')
	{
		Uart_SendChar(*Str);
		Delay5us();
		Str++;
	}
}

void Uart_SendCmd(unsigned char *cmd)
{
	while(*cmd!='\0')
	{
		Uart_SendChar(*cmd);
		Delay5us();
		cmd++;
	}
	Uart_SendChar('\r');
	Delay5us();
	Uart_SendChar('\n');
	delay(3000);
}
/*
void Usart() interrupt 4
{
	u8 receiveData;

	receiveData=SBUF;//��ȥ���յ�������
	RI = 0;//��������жϱ�־λ
	SBUF=receiveData;//�����յ������ݷ��뵽���ͼĴ���
	while(!TI);			 //�ȴ������������
	TI=0;						 //���������ɱ�־λ
}
*/



