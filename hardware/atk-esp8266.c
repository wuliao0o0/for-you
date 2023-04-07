#include <REGX51.H>
#include <string.h>
#include "uart.h"

#include "delay.h"

void Esp8266_Init()
{
	Uart_SendStr("\r\n");
	delay(1000);                        //延时	
	Uart_SendStr("AT+CWMODE=3\r\n");        //设置ESP8266工作在AP+STA模式下
//	Uart_SendStr("\r\n");
	delay(1000);
	Uart_SendStr("AT+CWJAP=\"Shinobu\",\"qweasdzxc12345\"\r\n");
	delay(1000);
	Uart_SendStr("AT+CIFSR\r\n");
	delay(1000);
	Uart_SendStr("AT+CIPSTART=\"TCP\",\"192.168.0.103\",8080\r\n");
	delay(1000);
////	Uart_SendStr("AT+CIPMUX=1\r\n");        //允许多连接
//	delay(3000);
//	
////	Uart_SendStr("AT+CWQAP\r\n");
////	delay(1000);


}
