#include "Relay.h"
 /*
*******************************************************************************
**��    ��:void Relay_Init(void)
**��    ��:�̵����˿ڵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void Relay_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					       
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				  
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	

	 MOTOR1_ANODE_OFF(); //�رյ��1
	 MOTOR2_ANODE_OFF(); //�رյ��2
   O3_ANODE_OFF();     //�رճ���
}
/*
*******************************************************************************
**��    ��:void Relay_control(void)
**��    ��:�̵�������
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/

void Relay_control (void)
{
	
	
}


