#ifndef __LCD1602_H
#define __LCD1602_H	 
#include "sys.h"

#define scl PBout(11)	
#define sda PBout(10)		

extern unsigned char CGRAM_data[];

void transfer(int data1);
void start_flag(void);
void stop_flag(void);
void initial_lcd(void);
void write_CGRAM(unsigned char *puts);
void disp_CGRAM(unsigned char fillchar);
void disp_char(int line,int column,char *dp);
void Disp_XY( char posx,char posy);
void DispOneChar(u8 x,u8 y,u8 Wdata);
void IIC1602_Init(void);
void Lcd_show(u8 flag);

#endif

