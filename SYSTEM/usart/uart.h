#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"
#include "stdio.h"

//==========宏定义===========//
#define EN_USART1     1		     //使能（1）/禁止（0）串口1接收
#define EN_USART2     1	
#define EN_USART3     1	
#define EN_USART4     1	
#define EN_USART5     1	

#define REC_SET_LEN   5      //设置接收的长度
#define REC_LEN_MAX   1000     //接收的最大长度

#define com_out_time  5     //通信超时间为20*1ms

#define USART_REC_LEN 100 
#define BOARD_ID   0x01

#define DELAY_ENABLE 1
#define Delay_TIME 200
#define SEND_COUNTTIME 2
#define Delay_TIME_S 100 

#define AUTO_TIME_NUM   375 //375*0.8==300S


struct _USARTS
{
	u8 start_rec_flag;
	u16 usart_time_count;
	u8  begin_flag;
	
	u8 USART_TX_BUF[USART_REC_LEN];
	u8 USART_RX_BUF[USART_REC_LEN];
	u8 USART_RX_STA; 
};

struct _USARTSS
{
	u8 start_rec_flag;
	u16 usart_time_count;
	u8  begin_flag;
	
	u8 USART_TX_BUF[1000];
	u8 USART_RX_BUF[1000];
	u8 USART_RX_STA; 
};

extern s16 system_temp[6];

//extern u8 ReadE32ParCom[3];

extern struct _USARTSS USART_01;
extern struct _USARTS USART_02;
extern struct _USARTSS USART_03;
extern struct _USARTS USART_04;
extern struct _USARTS USART_05;
//extern u16 usart3count;

//节点相关的参数汇总
struct _point
{
	int  temp;      
	u16  hum;
	u16  pm25;
	u16  pm100;
	u16  tvoc;
	u16  co2;
	u16  ch2o;
	u16  O3O;
	
	u16 point_address;      //无线地址
	u8  point_speed;
	u8  point_chan;
	u8  point_option;
};

extern u8 PM25[2];
extern u8 PM10[2];
extern u8 CO2[2];
extern u8 HCHO[2];
extern u8 TVOC[2];
extern struct _point POINT_IN ;
extern u16 o3o_ss;
extern u16 tvoc_up_count;
extern u16 test_co2;
extern u16 send_ask_num;
extern u8 node_num;        //从机的数量
extern u8 node_address[20];//从机的地址列表
extern u8 node_online_time[20];
extern u8 ask_ennable;
extern u8 ask_flag;

extern u8 SetE32Com[6];
extern u8 ReadE32ParCom[3];
extern u8 start_rec_time_out;
extern u32 rec_data_count;
extern u8 cs_time_count;
//=========变量声明===========//
//extern u16 REC_TIME_COUNT; //接收超时计数器
//=========函数声明============//
extern void USART1_Configuration(u32 bound);
extern void USART2_Configuration(u32 bound);
extern void USART3_Configuration(u32 bound);
extern void USART4_Configuration(u32 bound);
extern void USART5_Configuration(u32 bound);
extern void usart1_send_value(u8 m_addr,u8 fun_flag,u16 set_value);
//extern int fputc(int ch, FILE *f);
extern u8 ADDCheck(u8 *data,u8 Length);
extern u16 CRCCheck(u8 *puchMsg, u16 usDataLen) ;
extern u16 Get_CRC16(u8 *pchMsg,u16 wDataLen);

extern void u1_printf(char* fmt,...);
extern void u3_printf(char* fmt,...);
extern void u2_printf(char* fmt,...);
extern void u4_printf(char* fmt,...);
extern void u5_printf(char* fmt,...);

void Uart1SendBuffer(u8 *pSource, u8 nLength);
void Uart2SendBuffer(u8 *pSource, u8 nLength);
void Uart3SendBuffer(u8 *pSource, u8 nLength);
void Uart4SendBuffer(u8 *pSource, u8 nLength);
void Uart5SendBuffer(u8 *pSource, u8 nLength);

extern void usart1_rec(void);
extern void usart2_rec(void);
extern void usart3_rec(void);
extern void usart4_rec(void);
extern void usart5_rec(void);
extern void usart1_send_back(void);
extern void usart3_send_back(void);
extern void AutotimeUpload(void);
extern void Get_temphum(u8 addr);
extern void Get_XYZ_statu(u8 addr);
extern void Get_add_statu(u8 addr);
extern void Get_ang_statu(u8 addr);
extern void Get_ccc_statu(u8 addr);
extern void Get_sys_statu(u8 addr);
extern void Get_ZF_Num(u8 addr);
extern void Reset_ZF_Num(void);
extern void Control_node(u8 address,u8 funum,u8 code);
extern void FQ_Control_node(u8 address,u8 funum,u8 code1,u8 code2);
extern void OpenAutomaticUpload_VOC(void);
void Uart1SendBuffer(u8 *pSource, u8 nLength);
void Uart3SendBuffer(u8 *pSource, u8 nLength);
extern void Send_ask(void);
extern void Send_ask2(void);
extern void Upload_sysstatu1(u8 addr,u8 cmd);
extern void Upload_sysstatu2(u8 addr,u8 cmd);

extern void Upload_sysstatu3(u8 addr,u8 cmd);
extern void Upload_sysstatu4(u8 addr,u8 cmd);
extern void Upload_sysstatu5(u8 addr,u8 cmd);
extern void Upload_sysstatu6(u8 addr,u8 cmd);
extern void Upload_sysstatut(u8 addr,u8 cmd,u8 data);

extern void Upload_sysstatu_time(u8 addr,u8 cmd);

extern void Send_back(u8 addr,u8 cmd);
void Read_addr(u8 addr,u8 cmd,u16 addr_begin,u8 num);
void Set_addr(u8 addr,u8 cmd,u16 addr_begin,short data);
void Set_addr_l(u8 addr,u8 cmd,u16 addr_begin,short data);
void Set_addr_r(u8 addr,u8 cmd,u16 addr_begin,short data);

void Send_ask_test(void);
void Back_sn_test(void);

void Read_addr_com3(u8 addr,u8 cmd,u16 addr_begin,u8 num);
void Set_addr_com3(u8 addr,u8 cmd,u16 addr_begin,short data);
void Upload_lora_sysstatu(u8 cmd);

#endif
