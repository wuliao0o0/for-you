#ifndef __uart_H__
#define __uart_H__
void Uart_Init(void);
void Uart_SendChar(unsigned char Word);
void Uart_SendStr(unsigned char *Str);
void Uart_SendCmd(unsigned char *cmd);
#endif