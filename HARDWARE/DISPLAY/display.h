#ifndef _DISPALY_H
#define _DISPALY_H
#include "stm32f10x.h"


#define DELAY_DISplay			    60


struct LUYIN_CONFG
{
	u8 ly_start_flag; //录音开始标志位
	u8 ly_time_num;   //录音时间长度
};
extern struct LUYIN_CONFG  LUYIN_SYS;

extern void modbus_rec(void);
extern void Statu_display(void) ;
extern void Statu_display1(void) ;
extern void Statu_display2(void)  ;
extern void Config_display(u8 conf_num);
extern void Systime_display(void);
extern void Sysconf_display(void);
extern void Sysid_display(void);
extern void Sysluyin_display(void);
extern void Change_pic(u16 addr,u8 pic_num) ;
extern void Biling_pic(u16 addr,u8 show) ;
extern void Auto_display(void);

extern void Test_display(char *txt) ;

extern void Syspeiw_display(void);

extern void luyin_task(void);

extern u8 mypri_flag;
extern u8 delay_time;
extern u8 sys_flag;
extern u8 chum_run_flag;
extern u8 chum_vol_num;
extern u8 chum_error_num;
extern u16 drum_time_count;
extern u8 start_flag;


#endif

