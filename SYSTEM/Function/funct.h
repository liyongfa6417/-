#ifndef __funct_H
#define __funct_H

//包涵各个模块的头文件
#include "stm32f10x.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h" 
#include "string.h"
#include "stdarg.h"	  
#include "sys.h"
#include "led.h"
#include "tim2.h"
#include "init.h"
#include "delay.h"
#include "adc.h"
#include "wdg.h"
//#include "Relay.h"
#include "uart.h"
//#include "key.h" 
#include "display.h" 
#include "24cxx.h" 
#include "rtc.h"  
//#include "DS3231.h"
#include "adc.h"
#include "myiic.h"
#include "usb12.h"
#include "can.h"

//==========宏定义=============//

#define   sys_soft_ver      0x37

#define   B_O3O            1

#define MAIN_SYSTEM        0
#define NODE_SYSTEM        1
#define AHT10_ENABLE       1
#define FLASH_ADR          0x08001000

#define TEST_ENABLE        0
#define TEMP_ENABLE        0

#define CONFIG_NUM_MAX     3


#define EE_INIT_FLAG					     0xAA							// 初始化标志

#define EE_INIT_FLAG_ADDR				   0x00							// 初始化标志地址

#define EE_LOCK_ID			        0x20


#define EE_SYS_ID			          0x24

#define EE_SYS_ID_YEAR			    0x26

#define EE_BOARD_ID			        0x27

#define EE_FY_SET_ADD             0x40
#define REC_FY_SET_ADD            50



#define REC_sys_id         00001

#define REC_sys_year       21 

#define REC_NODE_NUM     6


#define HUM_LOW       20
#define HUM_UP       50

#define BAT_NUM     18//

#define speed_zy    25    //速度的增益

#define TEMP_ADDR    0x0C  //温湿度模块地址

#define ZTSYS_ADDR   0x20  //姿态模块地址
#define ZF_ADDR   0x20  //张力模块地址

#define sys_33_vol    33

#define CS_TIME_SET   3

#define SYS_COM_OUT    10
typedef struct 
{
	
	u8 s11_set_open_hour;
	u8 s11_set_open_min;
	
	u8 s11_set_close_hour;
	u8 s11_set_close_min;
	
	u8 s12_set_open_hour;
	u8 s12_set_open_min;
	
	u8 s12_set_close_hour;
	u8 s12_set_close_min;
	
	u8 s13_set_open_hour;
	u8 s13_set_open_min;
	
	u8 s13_set_close_hour;
	u8 s13_set_close_min;
	
	u8 s14_set_open_hour;
	u8 s14_set_open_min;
	
	u8 s14_set_close_hour;
	u8 s14_set_close_min;
	
	u8 s10_set_open_hour;
	u8 s10_set_open_min;
	
	u8 s10_set_close_hour;
	u8 s10_set_close_min;
	
	
	//f0	
	u8 f0_set_open_hour;
	u8 f0_set_open_min;
	
	u8 f0_set_close_hour;
	u8 f0_set_close_min;
	//f1
	u8 f1_set_open_hour;
	u8 f1_set_open_min;
	
	u8 f1_set_close_hour;
	u8 f1_set_close_min;
	//f2
	u8 f2_set_open_hour;
	u8 f2_set_open_min;
	
	u8 f2_set_close_hour;
	u8 f2_set_close_min;
	//f3
	u8 f3_set_open_hour;
	u8 f3_set_open_min;
	
	u8 f3_set_close_hour;
	u8 f3_set_close_min;
	//f4
	u8 f4_set_open_hour;
	u8 f4_set_open_min;
	
	u8 f4_set_close_hour;
	u8 f4_set_close_min;
	//电路编码
	u16 sys_id;
	u8  sys_year;
	//电路标识
	u8 board_id;
 
}_ee_time_set;

extern _ee_time_set time_set;
//=========变量声明============//
struct _STATU
{	
	//主机的状态量
	u8 M_relay1_flag;
	u8 M_relay2_flag;
	
	u8 M_sw_level1_flag;
	u8 M_sw_level2_flag;
	//u8 M_sw_level3_flag;
	
	u16 adc_fy;       //负压传感器
	u16 adc_bat_vol;  
	u8  bat_vol;       //电量
	u16 adc_charge_vol;
	u16 charge_flag;
	
	u8 error_code;  
	u8 lora_connect_flag;
	
	u8 sys_statu;      //系统实时状态
	u8 run_mode;
	u8 sys_speed;
	u8 sys_speed2;
	u8 front_led_pwm;

  u8 back_led_pwm;
	u8 other_led_pwm;
	
	u8 sys_temp;
	u8 sys_humity;
	
	u16 temp_h;
	u16 humity_h;
	
	//姿态采集
	u8 roll_h;
	u8 roll_l;
	short roll; 
	
	u8 pitch_h;
	u8 pitch_l;
	short pitch; 
	
	u8 yaw_h;
	u8 yaw_l;
	short yaw;
	
	//加速度
	u8 ax_h;
	u8 ax_l;
	
	u8 ay_h;
	u8 ay_l;
	
	u8 az_h;
	u8 az_l;
	
	//角速度
	u8 wx_h;
	u8 wx_l;
	
	u8 wy_h;
	u8 wy_l;
	
	u8 wz_h;
	u8 wz_l;
	
	//磁场
	u8 hx_h;
	u8 hx_l;
	
	u8 hy_h;
	u8 hy_l;
	
	u8 hz_h;
	u8 hz_l;
	
	u8 hh_h;
	u8 hh_l;
	
	//四元素
	u8 q0_h;
	u8 q0_l;
	
	u8 q1_h;
	u8 q1_l;
	
	u8 q2_h;
	u8 q2_l;
	
	u8 q3_h;
	u8 q3_l;
	
	u8 bat_low_flag;
	
	u16 zf_num;
	
	u16 distance;
	
	u8 fy_set_add;
	
	//CAN信息
	u16 motor_r_current;
	short motor_r_ture_speed;
	short motor_r_diff_speed;
	u32 motor_r_error_code;
	u16 motor_r_statu;
	
	u16 motor_l_current;
	short motor_l_ture_speed;
	short motor_l_diff_speed;
	u32 motor_l_error_code;
	u16 motor_l_statu;
	
	u16 sys_statu_show;   //硬件检测  以太网/左电机/右电机/气压/陀螺仪/尾部张力传感器/真空负压传感器/温湿度
	//用于记录硬件的通信超时
	u8 wifi_time;
	u8 canl_time;
	u8 canr_time;
	u8 m6050_time;
	u8 zl_control_enable;

};
//系统配置数据
struct _CONFG
{

	u8 wifi_connect_flag;
	
};
//采集模块基本信息的存储
struct _CJ_SYS
{
  //采集模块
	u16 temp;
	u16 humity;
	
	u16 temp_h;
	u16 humity_h;
	
	u16 co2_num;
	u16 pm2_5_num;
	u16 pm10_num;
	u16 ch20_num;
	u16 tvoc_num;
	
	u8 env_day;
	
};
//加湿器模块基本信息的存储
struct _JS_SYS
{
	//加湿
	u8 js_motor_flag;
	u8 js_pump_flag;
	u8 js_water_level1_flag;
	u8 js_water_level2_flag;
	u8 js_water_level3_flag;
	
	u8 run_flag;
	u8 auto_mode_flag;
	
};
//清风模块基本信息的存储
struct _QF_SYS
{
	//清风
	u8 qf_motor1_flag;//新风
	
	u8 qf_motor2_flag;//排风
	
	u8 qf_motor3_flag;//全热交换
	
	u8 qf_jh_flag;//净化
	
	u8 qf_fvalue1_flag;
	u8 qf_fvalue2_flag;
	u8 qf_fvalue3_flag;
	u8 qf_fvalue4_flag;
	u8 qf_fvalue5_flag;
	
	u8 qf_fanchong_flag;//反冲开关状态
	
	u8  sys_type;
	u8 run_flag;//运行开关
	u8 auto_flag;//自动手动
	u8 fan_speed;//风机速度
	u8 xhuan_mode;//循环模式
	u8 error_flag;//错误状态
	
	u8 keting_sw;
	u8 chanting_sw;
	u8 zhuwo_sw;
	u8 ciwo_sw;
	
	u8 old_room_sw;
	u8 baby_room_sw;
	u8 book_room_sw;
	u8 cloth_room_sw;
	u8 ytai_sw;
	u8 cfang_sw;
	u8 toilet_sw;
	
	
};
//杀毒模块基本信息的存储
struct _SD_SYS
{
//杀毒
	u8 sd_motor_flag;//投料电机
	u8 sd_qpump_flag;//气泵
	u8 sd_pspump_flag;//排水泵
	u8 sd_dcvalve_flag;//阀
	u8 sd_water_level1_flag;//水位1高
	u8 sd_water_level2_flag;//水位2中
	u8 sd_water_level3_flag;//水位3低
	u8 sd_sw1_flag; //投料
	u8 sd_sw2_flag; //料棒
	
	u8 run_flag;
	u8 error_flag;
	u8 med_num;
	
};
//分区域控制基本信息的存储
struct _FQ_SYS
{

	//u8 run_flag;
	u8 fq_run_flag;//运行开关
	
	u8 fq_keting_sw1;
	u8 fq_chanting_sw2;
	u8 fq_zhuwo_sw3;
	u8 fq_ciwo_sw4;
	
	u8 fq_old_room_sw5;
	u8 fq_baby_room_sw6;
	u8 fq_book_room_sw7;
	u8 fq_kit_room_sw8;
	
	u8 fq_ytai_sw9;
	u8 fq_toillet_sw10;
	
};
extern struct _CJ_SYS  CJ_SYS;
extern struct _JS_SYS  JS_SYS;
extern struct _QF_SYS  QF_SYS;
extern struct _SD_SYS  SD_SYS;
extern struct _FQ_SYS  FQ_SYS;
extern struct _CONFG  CONFG_SYS;
extern struct _STATU  STATU_SYS;

extern u16 HostAddress; 							  // 设备无线地址
extern u8 HostAddress_chan;

extern u8 led_blink_count;
extern u8 control_flag;
extern u8 test_flag;
extern u16 u2_count;
extern u8 o3_flag;
extern u8 motor_flag;
extern u16 o3_runtime_count;
extern u8 time_out_flag;
extern char password[4];
extern u8 Temp[2];
extern u8 Humi[2];
extern u16 o3o_cal_time_count;
extern u8 count_t;
//=========函数声明============//
extern void System_Configuration(void);   
extern void Data_init(void);
void led_update(void);
void ReadTemperature(void);
void ReadHumidity(void);
extern void o3o_cal(void);
void EEprom_check(void);
void Relay_upload_back(void);
void  Update_sys_ststu(void);
void switch_scan(void);
void Display_init(void);
void sys_run_task(void);
void sys_led_task(void);
void bat_level_cal(void);
u8 findElement(u8 arr[], u8 size, u8 target);
void motor_stop(void);
#endif
