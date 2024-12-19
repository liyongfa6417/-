#ifndef __CAN_H
#define __CAN_H	 
#include "funct.h"	    
#define CAN_EX extern 
	
#define MAINMCU_TO_ROBOT_ARM_ID1        0x1801e50d

#define MOTECBACK_1                0x182
#define MOTECBACK_2                0x183

#define MOTECBACK_3                0x282
#define MOTECBACK_4                0x283

#define OTHER_TO_MAINMCU_ID        0X180100E5

CAN_EX u8 test_num[8];

CAN_EX u8 rec_data_can[8];
CAN_EX u8 start_op_flag;

//CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    
										 							 				   
CAN_EX u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
CAN_EX u8 Can_Send_Msg(u8* msg,u8 len,u32 address_ID);					//发送数据

CAN_EX u8 Can_Receive_Msg(u8 *buf);							  //接收数据

CAN_EX void Can_rev_flag(void);
#endif

















