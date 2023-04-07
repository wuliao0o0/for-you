#include <REGX51.H>
#include "delay.h"
void Uart_Init(void)
{		
	PCON &= 0x7F;		//æ³¢ç‰¹ç‡ä¸å€é€Ÿ
	SCON = 0x50;		//8ä½æ•°æ®,å¯å˜æ³¢ç‰¹ç‡
	TMOD &= 0x0F;		//æ¸…é™¤å®šæ—¶å™¨1æ¨¡å¼ä½
	TMOD |= 0x20;		//è®¾å®šå®šæ—¶å™¨1ä¸º8ä½è‡ªåŠ¨é‡è£…æ–¹å¼
	TL1 = 0xfd;		//è®¾å®šå®šæ—¶åˆå€¼
	TH1 = 0xfd;		//è®¾å®šå®šæ—¶åˆå€¼
	ET1 = 0;		//ç¦æ­¢å®šæ—¶å™¨1ä¸­æ–­
	TR1 = 1;		//å¯åŠ¨å®šæ—¶å™¨1
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

	receiveData=SBUF;//³öÈ¥½ÓÊÕµ½µÄÊı¾İ
	RI = 0;//Çå³ı½ÓÊÕÖĞ¶Ï±êÖ¾Î»
	SBUF=receiveData;//½«½ÓÊÕµ½µÄÊı¾İ·ÅÈëµ½·¢ËÍ¼Ä´æÆ÷
	while(!TI);			 //µÈ´ı·¢ËÍÊı¾İÍê³É
	TI=0;						 //Çå³ı·¢ËÍÍê³É±êÖ¾Î»
}
*/



