#include <intrins.h>
#include "public.h"
#include "OLED.h"
#include "ASCII.h"
#include "text.h"
#include "port.h"
#include "delay.h"
#include "i2c.h"

//使用位操作加快iic读取速度
u8 bdata Byte_data;
sbit Byte_data7=Byte_data^7;
sbit Byte_data6=Byte_data^6;
sbit Byte_data5=Byte_data^5;
sbit Byte_data4=Byte_data^4;
sbit Byte_data3=Byte_data^3;
sbit Byte_data2=Byte_data^2;
sbit Byte_data1=Byte_data^1;
sbit Byte_data0=Byte_data^0;


void OLED_delay500ms()//11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




//IIC写入一个字节(字节)
void IIC_write_Byte(u8 Byte)
{
	I2C_SCL=0;
	Byte_data=Byte;
	I2C_SDA=Byte_data7;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data6;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data5;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data4;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data3;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data2;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data1;I2C_SCL=1;I2C_SCL=0;
	I2C_SDA=Byte_data0;I2C_SCL=1;I2C_SCL=0;                                               
	I2C_SCL=1;//IIC应答
	I2C_SCL=0;
}

//MCU向OLED写入一个字节(字节数据,选择字节为命令还是数据)
void MCU_write_OLED_Byte(u8 Byte,u8 command_or_data)
{
	IIC_start();//IIC通信开始
	IIC_write_Byte(0x78);//从机地址
	IIC_write_Byte(command_or_data);
	IIC_write_Byte(Byte);
	IIC_stop();//IIC通信停止
}

//光标的位置,0到7行,0到127列(行,列)
void OLED_cursor_location(u8 row,u8 column)
{
	MCU_write_OLED_Byte(0xB0+row,OLED_COMMAND);//设置行(0~7)

	MCU_write_OLED_Byte(0x10|(column&0xF0)>>4,OLED_COMMAND);//设置显示位置大列(0~7)

	MCU_write_OLED_Byte(0x00|(column&0x0F),OLED_COMMAND);//设置显示位置小列(0~7)

}

//设置内存地址模式(使用水平地址模式:0x00或垂直地址模式:0x01)
void OLED_set_memory_address_mode(u8 mode)
{
	MCU_write_OLED_Byte(0x20,OLED_COMMAND);//设置内存地址模式(使用水平地址模式或垂直地址模式)
	MCU_write_OLED_Byte(mode,OLED_COMMAND);//水平地址模式:0x00,垂直地址模式:0x01,页地址模式:0x02
	MCU_write_OLED_Byte(0x21,OLED_COMMAND);//设置显示位置列初始地址和终止地址
	MCU_write_OLED_Byte(0x00,OLED_COMMAND);//列初始地址
	MCU_write_OLED_Byte(0x7F,OLED_COMMAND);//列终止地址
	MCU_write_OLED_Byte(0x22,OLED_COMMAND);//设置显示位置页初始地址和终止地址
	MCU_write_OLED_Byte(0x00,OLED_COMMAND);//页初始地址
	MCU_write_OLED_Byte(0x07,OLED_COMMAND);//页终止地址
}

//清屏
void OLED_clear()
{  
	u16 i;
	for(i=0;i<1024;++i) MCU_write_OLED_Byte(0x00,OLED_DATA);
}

//打印BMP图片(图片数组,选择图片的取模方式(水平取模:0x00或垂直取模:0x01),是否反色(填0或1))
void OLED_print_BMP(u8 *p,u8 mode,u8 invert_color)
{
	u16 i;
	OLED_set_memory_address_mode(mode);
	if(invert_color) for(i=0;i<1024;++i) MCU_write_OLED_Byte(~*(p+i),OLED_DATA);
	else for(i=0;i<1024;++i) MCU_write_OLED_Byte(*(p+i),OLED_DATA);
}

//OLED打印单个字符(行(0到3),列(0到15),字符,是否反色(填0或1))
void OLED_print_char(u8 row,u8 column,u8 _char,u8 invert_color)
{
	u8 i;
	if(invert_color)
	{
		//光标的位置,0到7行,0到127列(行,列)
		OLED_cursor_location(2*row,8*column);
		for(i=0;i<8;++i) MCU_write_OLED_Byte(~ASCII[_char-32][i],OLED_DATA);//因为ASCII码0到31位去除了,所以减32
		//光标的位置,0到7行,0到127列(行,列)
		OLED_cursor_location(2*row+1,8*column);
		for(i=0;i<8;++i) MCU_write_OLED_Byte(~ASCII[_char-32][i+8],OLED_DATA);//因为ASCII码0到31位去除了,所以减32
	}
	else
	{
		//光标的位置,0到7行,0到127列(行,列)
		OLED_cursor_location(2*row,8*column);
		for(i=0;i<8;++i) MCU_write_OLED_Byte(ASCII[_char-32][i],OLED_DATA);//因为ASCII码0到31位去除了,所以减32
		//光标的位置,0到7行,0到127列(行,列)
		OLED_cursor_location(2*row+1,8*column);
		for(i=0;i<8;++i) MCU_write_OLED_Byte(ASCII[_char-32][i+8],OLED_DATA);//因为ASCII码0到31位去除了,所以减32
	}
}

//OLED打印单个文字(行(0到3),列(0到15),单个所在文字的数组,是否反色(填0或1))
void OLED_print_single_word(u8 row,u8 column,u8 *word,u8 invert_color)
{
	u16 i;
	u8 j;
	for(i=0;i<(sizeof(text))/35;++i)
	{
		if((*word==text[i].name[0])&&(*(word+1)==text[i].name[1]))//对比汉字区码位码
		{
			//光标的位置,0到7行,0到127列(行,列)
			OLED_cursor_location(2*row,8*column);
			for(j=0;j<32;++j)
			{
				if(j==16) OLED_cursor_location(2*row+1,8*column);//光标的位置,0到7行,0到127列(行,列)
				if(invert_color) MCU_write_OLED_Byte(~text[i].array[j],OLED_DATA);
				else MCU_write_OLED_Byte(text[i].array[j],OLED_DATA);
			}
		}
	}
}

//OLED打印文本(行(0到3),列(0到15),所打印的文本,是否反色(填0或1))
void OLED_print_text(u8 row,u8 column,u8 *p,u8 invert_color)
{
	//设置内存地址模式(使用水平地址模式:0x00或垂直地址模式:0x01)
	OLED_set_memory_address_mode(0x00);
	while(*p!='\0')
	{
		if(*p&0x80)//判断是否为汉字
		{
			//OLED打印单个文字(行(0到3),列(0到15),单个所在文字的数组,是否反色(填0或1))
			OLED_print_single_word(row,column,p,invert_color);
			p=p+2;
			column=column+2;
		}
		else
		{
			//OLED打印单个字符(行(0到3),列(0到15),字符,是否反色(填0或1))
			OLED_print_char(row,column,*p,invert_color);
			++p;
			++column;
		}
		
		if(*p&0x80)//判断下一个字符是中文还是英文,防止在末尾显示的位置不够
		{
			if(column>=15)
			{
				++row;
				column=0;
			}
		}
		else
		{
			if(column==16)
			{
				++row;
				column=0;
			}
		}
		
		if(row==4) return;//第四行不存在,显示到第四行直接退出(从第零行开始算)
	}
}

void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned int Num)
{
	int Length,result,flag=Num;
	unsigned char i;
	if(Num==0)
	{
		OLED_print_char(Line,Column,0+'0',0);
	}else
	{
			for(Length=0;Num>0;Length++)
		{
			result=Num;
			result%=10;
			Num/=10;
		}
		for (i = 0; i < Length; i++)							
		{
//			OLED_ShowChar(Line, Column + i, flag/ OLED_Pow(10, Length - i - 1) % 10 + '0');
			OLED_print_char(Line, Column++,flag/OLED_Pow(10, Length - i - 1) % 10 + '0',0);
		}
	}
	
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
unsigned int OLED_Pow(unsigned int X, unsigned int Y)
{
	unsigned int Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

//初始化OLED(内存地址模式默认使用水平地址模式,可在初始化程序中更改)
void OLED_init()
{
	OLED_delay500ms();

	MCU_write_OLED_Byte(0xAE,OLED_COMMAND);//关闭显示
	MCU_write_OLED_Byte(0x00,OLED_COMMAND);//设置低列地址
	MCU_write_OLED_Byte(0x10,OLED_COMMAND);//设置高列地址
	MCU_write_OLED_Byte(0x40,OLED_COMMAND);//设置显示起始行
	
	MCU_write_OLED_Byte(0xB0,OLED_COMMAND);//设置页地址
	MCU_write_OLED_Byte(0x81,OLED_COMMAND);//
	MCU_write_OLED_Byte(0xFF,OLED_COMMAND);//
	
	MCU_write_OLED_Byte(0xA1,OLED_COMMAND);//设置细分重映射(0xA1正常,0xA0左右反置)
	MCU_write_OLED_Byte(0xA6,OLED_COMMAND);//设置正常/反向(0xA6正常显示,0xA7反向显示)
	MCU_write_OLED_Byte(0xA8,OLED_COMMAND);//设置多路比率
	MCU_write_OLED_Byte(0x3F,OLED_COMMAND);
	MCU_write_OLED_Byte(0xC8,OLED_COMMAND);//设置列输出扫描方向(0xC8正常,0xC0上下反置)
	MCU_write_OLED_Byte(0xD3,OLED_COMMAND);//设置显示偏移(垂直偏移)
	MCU_write_OLED_Byte(0x00,OLED_COMMAND);
	MCU_write_OLED_Byte(0xD5,OLED_COMMAND);//设置显示时钟分频
	MCU_write_OLED_Byte(0x80,OLED_COMMAND);
	MCU_write_OLED_Byte(0xD9,OLED_COMMAND);//设置预充电周期
	MCU_write_OLED_Byte(0xF1,OLED_COMMAND);//将预充电设置为15个时钟加上其放电设置为1个时钟
	MCU_write_OLED_Byte(0xDA,OLED_COMMAND);//设置COM口硬件配置
	MCU_write_OLED_Byte(0x12,OLED_COMMAND);//启用备用COM向导配置
	MCU_write_OLED_Byte(0xDB,OLED_COMMAND);//设置Vcomh取消选择等级
	MCU_write_OLED_Byte(0x30,OLED_COMMAND);//
	MCU_write_OLED_Byte(0x8D,OLED_COMMAND);//充电凹凸设置
	MCU_write_OLED_Byte(0x14,OLED_COMMAND);//在显示期间启用血浆泵
	MCU_write_OLED_Byte(0xAF,OLED_COMMAND);//开启显示
	
	//光标的位置,0到7行,0到127列(行,列)
	OLED_cursor_location(0,0);
	
	//设置内存地址模式(使用水平地址模式:0x00或垂直地址模式:0x01)
	OLED_set_memory_address_mode(0x00);
	
	//清屏
	OLED_clear();
} 