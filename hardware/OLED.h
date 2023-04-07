#ifndef _OLED_H
#define _OLED_H

//替换关键字
#define OLED_COMMAND 0x00
#define OLED_DATA 0x40

//函数声明
void OLED_delay500ms();

//IIC通信开始
void IIC_start();

//IIC通信停止
void IIC_stop();

//IIC写入一个字节(字节)
void IIC_write_Byte(unsigned char Byte);

//MCU向OLED写入一个字节(字节数据,选择字节为命令还是数据)
void MCU_write_OLED_Byte(unsigned char Byte,unsigned char command_or_data);

//清屏
void OLED_clear();

//初始化OLED(内存地址模式默认使用水平地址模式,可在初始化程序中更改)
void OLED_init();

//光标的位置,0到7行,0到127列(行,列)
void OLED_cursor_location(unsigned char row,unsigned char column);

//设置内存地址模式(使用水平地址模式:0x00或垂直地址模式:0x01)
void OLED_set_memory_address_mode(unsigned char mode);

//打印BMP图片(图片数组,选择图片的取模方式(水平取模:0x00或垂直取模:0x01),是否反色(填0或1))
void OLED_print_BMP(unsigned char *p,unsigned char mode,unsigned char invert_color);

//OLED打印单个字符(行(0到3),列(0到15),字符,是否反色(填0或1))
void OLED_print_char(unsigned char row,unsigned char column,unsigned char _char,unsigned char invert_color);

//OLED打印单个文字(行(0到3),列(0到15),单个所在文字的数组,是否反色(填0或1))
void OLED_print_single_word(unsigned char row,unsigned char column,unsigned char *word,unsigned char invert_color);

//OLED打印文本(行(0到3),列(0到15),所打印的文本,是否反色(填0或1))
void OLED_print_text(unsigned char row,unsigned char column,unsigned char *p,unsigned char invert_color);
unsigned int OLED_Pow(unsigned int X, unsigned int Y);
void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned int Num);
#endif