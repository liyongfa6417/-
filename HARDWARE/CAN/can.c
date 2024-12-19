#include "can.h"
u8 test_num[8]={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //can���ݵķ���
/*
*******************************************************************************
**��    ��:CAN_Mode_Init
**��    ��:CAN��ʼ�� 
**��    ��:tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:1~3; CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
					 tbs2:ʱ���2��ʱ�䵥Ԫ.��Χ:1~8;     CAN_BS2_1tq ~CAN_BS2_8tq
					 tbs1:ʱ���1��ʱ�䵥Ԫ.��Χ:1~16;	  CAN_BS1_1tq ~CAN_BS1_16tq
					 brp :�����ʷ�Ƶ��.��Χ:1~1024;(ʵ��Ҫ��1,Ҳ����1~1024) tq=(brp)*tpclk1
					 ע�����ϲ����κ�һ����������Ϊ0,�������.
					 ������=Fpclk1/((tsjw+tbs1+tbs2)*brp);
					 mode:0,��ͨģʽ;1,�ػ�ģʽ;
					 Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ36M,�������CAN_Normal_Init(1,8,7,9,1);
					 ������Ϊ:36M/((1+8+7)*9)=500Kbps
**�� �� ֵ:0,��ʼ��OK;����,��ʼ��ʧ��;
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{

	  GPIO_InitTypeDef GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
 	  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
#if CAN_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); //ʹ��CAN1ʱ��	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);		           //��ʼ��IO
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��IO
	  
 	  //CAN��Ԫ����
 	  CAN_InitStructure.CAN_TTCM=DISABLE;						       //��ʱ�䴥��ͨ��ģʽ  //
 	  CAN_InitStructure.CAN_ABOM=DISABLE;						       //����Զ����߹���	 //
  	CAN_InitStructure.CAN_AWUM=DISABLE;						       //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
  	CAN_InitStructure.CAN_NART=ENABLE;						 	     //��ֹ�����Զ����� //
  	CAN_InitStructure.CAN_RFLM=DISABLE;						       //���Ĳ�����,�µĸ��Ǿɵ� // 
  	CAN_InitStructure.CAN_TXFP=DISABLE;						       //���ȼ��ɱ��ı�ʶ������ //
  	CAN_InitStructure.CAN_Mode= mode;	                   //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
  	//���ò�����
  	CAN_InitStructure.CAN_SJW=tsjw;				               //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1;                      //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;                      //Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;                 //��Ƶϵ��(Fdiv)Ϊbrp+1	//
  	CAN_Init(CAN1, &CAN_InitStructure);                  // ��ʼ��CAN1 

 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	         //������0
 	  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;     //32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
 	  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0

  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
#if CAN_RX0_INT_ENABLE
	
	  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
  
  	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
#endif
	  return 0;
}   
u32 rec_address=0; 
u8 Data_rec_flag=0; 
u8 rec_data_can[8]={0};
#if CAN_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����			    
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;
	int i=0;
  CAN_Receive(CAN1, 0, &RxMessage);
	//��ӽ��յ��������ڲ�
	rec_address=RxMessage.StdId;
	for(i=0;i<8;i++)
	{
		rec_data_can[i]=RxMessage.Data[i];
	}

	Data_rec_flag=1;
	//printf("rxbuf[%d]:%d\r\n",i,RxMessage.Data[i]);
}
#endif
/*
*******************************************************************************
**��    ��:Can_Send_Msg
**��    ��:����CAN���ݵķ���,can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
**��    ��:len:���ݳ���(���Ϊ8);msg:����ָ��,���Ϊ8���ֽ�.	
**�� �� ֵ:0,�ɹ�;����,ʧ��;
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 Can_Send_Msg(u8* msg,u8 len,u32 address_ID)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=address_ID;					 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=address_ID;		 // ������չ��ʾ����29λ��
  TxMessage.IDE=CAN_ID_STD;			 //  ʹ�ñ�׼��ʶ��
  TxMessage.RTR=CAN_RTR_DATA;		 // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=len;						 // ������֡��Ϣ
	
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];			 // ��һ֡��Ϣ  
	
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;		

}
/*
*******************************************************************************
**��    ��:Can_Receive_Msg
**��    ��:can�ڽ������ݲ�ѯ
**��    ��:���ݻ�����;	 
**�� �� ֵ:0,�����ݱ��յ�;����,���յ����ݳ���;
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	 u32 i;
	 CanRxMsg RxMessage;
   if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
   CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);              //��ȡ����	
   for(i=0;i<8;i++)
   buf[i]=RxMessage.Data[i];  
	 return RxMessage.DLC;	
}


/*
*******************************************************************************
**��    ��:Can_rev_flag
**��    ��://CAN���ݵĽ���
**��    ��:���ݻ�����;	 
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
//u32 ID_T=0;
u8 start_op_flag=0;
void Can_rev_flag(void)
{
	
	if(Data_rec_flag==1)
	{
		/********���ģ��***********************************/
		if(rec_address==MOTECBACK_1)           
		{
			start_op_flag=1;
			STATU_SYS.canr_time=0;
			STATU_SYS.motor_r_current=((u16)rec_data_can[7]<<8)+(u16)rec_data_can[6];
			STATU_SYS.motor_r_diff_speed=((u16)rec_data_can[5]<<8)+(u16)rec_data_can[4];
			STATU_SYS.motor_r_ture_speed=((u16)rec_data_can[3]<<8)+(u16)rec_data_can[2];
			STATU_SYS.motor_r_statu=((u16)rec_data_can[1]<<8)+(u16)rec_data_can[0];
		}
		else if(rec_address==MOTECBACK_2)
		{
			start_op_flag=1;
			STATU_SYS.canl_time=0;
			STATU_SYS.motor_l_current=((u16)rec_data_can[7]<<8)+(u16)rec_data_can[6];
			STATU_SYS.motor_l_diff_speed=((u16)rec_data_can[5]<<8)+(u16)rec_data_can[4];
			STATU_SYS.motor_l_ture_speed=((u16)rec_data_can[3]<<8)+(u16)rec_data_can[2];
			STATU_SYS.motor_l_statu=((u16)rec_data_can[1]<<8)+(u16)rec_data_can[0];
		}
		else if(rec_address==MOTECBACK_3)//282�Ҳ���
		{
			//start_op_flag=1;
			STATU_SYS.canr_time=0;
			STATU_SYS.motor_r_error_code=((u32)rec_data_can[3]<<24)+((u32)rec_data_can[2]<<16)+((u32)rec_data_can[1]<<8)+(u32)rec_data_can[0];
		}
		else if(rec_address==MOTECBACK_4)//283�����
		{
			//start_op_flag=1;
			STATU_SYS.canl_time=0;
			STATU_SYS.motor_l_error_code=((u32)rec_data_can[3]<<24)+((u32)rec_data_can[2]<<16)+((u32)rec_data_can[1]<<8)+(u32)rec_data_can[0];
		}
		else
		{
			
		}
		Data_rec_flag=0;
	}
}












