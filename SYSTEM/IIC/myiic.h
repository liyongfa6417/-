#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"							  
//////////////////////////////////////////////////////////////////////////////////
#define IIC_1_ENABLE         1
#define IIC_2_ENABLE         0

// //IO��������
// #define IIC_2_ENABLE
// #define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
// #define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

// //IO��������	 
// #define IIC_SCL    PBout(10) //SCL
// #define IIC_SDA    PBout(11) //SDA	 
// #define READ_SDA   PBin(11)  //����SDA 

// #endif

#if IIC_1_ENABLE

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 

#endif


//IIC���в�������
void IIC_Init(void);            //��ʼ��IIC��IO��				 
void IIC_Start(void);				    //����IIC��ʼ�ź�
void IIC_Stop(void);	  			  //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				  //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					    //IIC����ACK�ź�
void IIC_NAck(void);				    //IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















