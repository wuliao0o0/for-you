#include <REGX51.H>
#include <string.h>
#include "uart.h"
#include "string.h"
#include "delay.h"
unsigned char receiveData[20];
void Esp8266_Init(void)
{
	
	delay(1000);
	Uart_SendCmd("\r\n");
	Uart_SendCmd("AT+CWMODE=3");
	Uart_SendCmd("AT+UART=9600,8,1,0,0");
//	Uart_SendCmd("AT+CWSAP=\"ESP8266\",\"12345678\",11,3");
//	Uart_SendCmd("AT+CIPMUX=1");
	Uart_SendCmd("AT+CWJAP=\"Shinobu\",\"qweasdzxc12345\"");
	delay(3000);
//	Uart_SendCmd("AT+CIPSTART=\"TCP\",\"192.168.0.103\",8080");
	Uart_SendCmd("AT+ATKCLDSTA=\"25277845249322331143\",\"12345678\"");
	delay(3000);
////	delay(3000);
//	Uart_SendCmd("AT+CIPSERVER=1,8080");
////	Uart_SendStr("AT+CWQAP\r\n");
////	delay(1000);


}
