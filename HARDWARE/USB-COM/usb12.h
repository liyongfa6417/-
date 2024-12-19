#ifndef _USB12_H
#define _USB12_H

#include "stm32f10x.h"

#define   NODE_NUM_X    30
extern u16 node_add[NODE_NUM_X];

//struct _USARTSX
//{
//	u8 fs1;
//	u8 fs2;
//	u8 fs3;
//	u8 fs4;
//	u8 fs5;
//	
//	u8 qffg1;
//	u8 hffg1;
//	u8 jhfg1;
//	u8 qzfg1;
//	u16 run_tm;
//	u8 run_flag;
//};

//extern struct _USARTSX CONF_01X;


//extern u8 node_check(u16 num);
extern void Usb_send_request(u8 station_flag,u8 fundata,u8 count,u16 begin_addr);
extern void Usb_send_order(u8 station_flag,u16 order_addr,u8 flag);

extern void usb_rec(void);
//extern void ensys_rec(void);
#endif


