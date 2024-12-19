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

//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.								    
										 							 				   
CAN_EX u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
CAN_EX u8 Can_Send_Msg(u8* msg,u8 len,u32 address_ID);					//��������

CAN_EX u8 Can_Receive_Msg(u8 *buf);							  //��������

CAN_EX void Can_rev_flag(void);
#endif

















