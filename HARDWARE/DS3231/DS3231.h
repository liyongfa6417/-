#include "sys.h"
#ifndef __DS3231_H__
#define __DS3231_H__


typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;			
	u32 w_year;
	u8  w_month;
	u8  w_date;
	u8  week;		 
}_calendar_ds_obj;					 
extern _calendar_ds_obj calendar1;	//日历结构体

extern u8 const mon_table[12];	//月份日期数据表

void DS3231_Init(void);
void get_show_time(void);   
void DS3231_Get(void);
//u8 RTC_Get_Week(u16 year,u8 month,u8 day);
void DS3231_Set(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间	

#endif

