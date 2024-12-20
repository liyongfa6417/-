#include "DS3231.h"
#include "myiic.h" 
#include "delay.h"   
#include "sys.h"  
     
_calendar_ds_obj calendar1;

#define DS3231_WriteAddress 0xD0   
#define DS3231_ReadAddress  0xD1

u8 BCD2HEX(u8 val)
{
    u8 i;
    i= val&0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;
    
    return i;
}

u16 B_BCD(u8 val)
{
  u8 i,j,k;
  i=val/10;
  j=val%10;
  k=j+(i<<4);
  return k;
}


void I2cByteWrite(u8 addr,u8 bytedata)
{
  IIC_Start();
  delay_us(5);
  IIC_Send_Byte(DS3231_WriteAddress);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(addr);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(bytedata);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Stop();
}	


u8 I2cByteRead(u8 addr)
{
  u8 Dat=0;
  
  IIC_Start();
  IIC_Send_Byte(DS3231_WriteAddress);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Send_Byte(addr);
  IIC_Wait_Ack();
  delay_us(5);
  IIC_Start();
  IIC_Send_Byte(DS3231_ReadAddress);
  IIC_Wait_Ack();
  delay_us(5);
  Dat=IIC_Read_Byte(1);
  IIC_Stop();
  return Dat;
} 



void DS3231_Init(void)
{
	IIC_Init();
	I2cByteWrite(0x0e,0);
	delay_ms(2); 
   I2cByteWrite(0x0f,0x0);
	delay_ms(2); 
}

void DS3231_Get(void)
{
  calendar1.w_year=I2cByteRead(0x06);  
  calendar1.w_month=I2cByteRead(0x05);  
  calendar1.w_date=I2cByteRead(0x04); 
  calendar1.hour=I2cByteRead(0x02);  
  calendar1.min=I2cByteRead(0x01);
  calendar1.sec=I2cByteRead(0x00);
}

void DS3231_Set(u8 yea,u8 mon,u8 da,u8 hou,u8 min,u8 sec)
{
  u8 temp=0;
  
  temp=B_BCD(yea);
  I2cByteWrite(0x06,temp);
  
  temp=B_BCD(mon);
  I2cByteWrite(0x05,temp);
   
  temp=B_BCD(da);
  I2cByteWrite(0x04,temp);
  
  temp=B_BCD(hou);
  I2cByteWrite(0x02,temp);
  
  temp=B_BCD(min);
  I2cByteWrite(0x01,temp);
  
  temp=B_BCD(sec);
  I2cByteWrite(0x00,temp);
}


void get_show_time(void)
{


calendar1.w_year=I2cByteRead(0x06);  
calendar1.w_year=BCD2HEX(calendar1.w_year);


calendar1.w_month=I2cByteRead(0x05); 
calendar1.w_month=BCD2HEX(calendar1.w_month);


calendar1.w_date=I2cByteRead(0x04);  
calendar1.w_date=BCD2HEX(calendar1.w_date);
 

calendar1.hour=I2cByteRead(0x02); 
calendar1.hour&=0x3f;                   
calendar1.hour=BCD2HEX(calendar1.hour);


calendar1.min=I2cByteRead(0x01);
calendar1.min=BCD2HEX(calendar1.min);
  
  
calendar1.sec=I2cByteRead(0x00);
calendar1.sec=BCD2HEX(calendar1.sec);
}


