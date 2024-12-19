#include "lcd1602.h"
#include "led.h"
#include "delay.h"

unsigned char CGRAM_data[]=
{
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//
	0x15,0x0a,0x15,0x0a,0x15,0x0a,0x15,0x0a,	//
	0x0a,0x15,0x0a,0x15,0x0a,0x15,0x0a,0x15,	//
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,	//
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,	//
	0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,	//
	0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,	//
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//
};
/*
*******************************************************************************
**函    数:IIC1602_Init()
**功    能:IIC型1602显示屏端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void IIC1602_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.11
 GPIO_SetBits(GPIOB,GPIO_Pin_11);						 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_10); 						
}

void transfer(int data1)
{
	int i;
	for(i=0;i<8;i++)
	{
	scl=0;
	delay_us(2);
	if(data1&0x80) sda=1;
	else sda=0;
	scl=1;
	delay_us(2);
	scl=0;
	data1=data1<<1;
	}
	sda=0;
  delay_us(2);
	scl=1;
  delay_us(2);
	scl=0;
}

void start_flag()
{
	scl=1; /*START FLAG*/
	delay_us(2);
	sda=1; /*START FLAG*/
	delay_us(2);
	sda=0; /*START FLAG*/
}

void stop_flag(void)
{
	scl=1; /*STOP FLAG*/
	delay_us(2);
	sda=0; /*STOP FLAG*/
	delay_us(2);
	sda=1; /*STOP FLAG*/
}


void initial_lcd(void)
{
	start_flag();   
	transfer(0x7C); 
	transfer(0x00); 
	transfer(0x28); 
	delay_ms(5);
	transfer(0x0c); 
	delay_ms(5);
	transfer(0x01); 
	delay_ms(10);
	transfer(0x06); 
	stop_flag();   
	
//	delay_ms(10);
//	write_CGRAM(CGRAM_data);
//	delay_ms(10); 
}

void write_CGRAM(unsigned char *puts)
{
	unsigned char i;
	start_flag();
	transfer(0x7C); 
	transfer(0x80); 
	transfer(0x40); 
	transfer(0x40); 
	for(i=0;i<64;i++)
	{
		transfer( puts[i] );
	}
	stop_flag();
}

void disp_CGRAM(unsigned char fillchar)
{
	unsigned char i;
	start_flag();
  transfer(0x7C); 
	transfer(0x80); 
	transfer(0x80); 
	transfer(0x40); 
	for(i=0;i<128;i++)	 
	{
		transfer(fillchar);
	}
	stop_flag();
}


void disp_char(int line,int column,char *dp)
{
	int i;
	start_flag();
	transfer(0x7C); 
	transfer(0x80); 
	transfer(0x80+(line-1)*0x40+(column-1)); 
	transfer(0x40); 
	for(i=0;i<16;i++)
	{
		transfer(*dp);
		dp=dp+1;
	}
	stop_flag();
}

void Disp_XY( char posx,char posy)
{
	u8 temp;
	temp=posx;                        
	posy&=0x1;
	if ( posy )
		temp|=0xc0;
	else 
		temp|=0x80;
		
	transfer(temp);
}

void DispOneChar(u8 x,u8 y,u8 Wdata)
{   
	start_flag();
	transfer(0x7C); 
	transfer(0x80); 
	Disp_XY( x, y );                            
	transfer(0x40); 
	transfer( Wdata );                  
	stop_flag();
}

void Lcd_show(u8 flag)
{
	u8 i=0,j=0;
	switch(flag)
	{
		case 1: 
		disp_char(1,1,"123456789ABCDEFG");
		disp_char(2,1,"123456789ABCDEFG");
			break;
		case 2:
			disp_char(1,1,"16X2 characters:");
		  disp_char(2,1,"*standard ascii*"); 
			break;
		case 3:
			for(i=0;i<2;i++)		
			{		
				for(j=0;j<0x28;j++)
				{
				 DispOneChar(j,i,j+0x41);  //A  0x41
				}
			}
			break;
		case 4:
			disp_CGRAM(0x00); 
			break;
		case 5:
			disp_CGRAM(0x01); 
			break;
		case 6:
			disp_CGRAM(0x02); 
			break;
		case 7:
			disp_CGRAM(0x03); 
			break;
		case 8:
			disp_CGRAM(0x04); 
			break;
		case 9:
			disp_CGRAM(0x05); 
			break;
		case 10:
			disp_CGRAM(0x06); 
			break;
	}
		
	
}

