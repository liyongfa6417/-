#include "key.h"
#include "led.h"
#include "funct.h"

/*
*******************************************************************************
**��    ��:KEY_Init()
**��    ��:�����˿ڵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/

//������ʼ������
void KEY_Init(void)    //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTA,PORTBʱ��

	//A12ģʽʶ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ��GPIOA
	//�״�ģ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���ø�������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                //��ʼ��GPIOB
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         //
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                //��ʼ��GPIOB

}
/*
*******************************************************************************
**��    ��:Key_scan()
**��    ��:������ɨ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 sys_mode=0;//ϵͳ����ģʽ 0λ�ػ���1���ֶ���2���Զ�
u8 run_flag=1;//���б�־λ
u8 pre_sys_flag=0;
void Key_scan(void)
{
	//ϵͳģʽѡ��
	if(SYS1_SWITCH==0) 
	{
			sys_mode=1;			
	}
	
	else if(SYS2_SWITCH==0) 
	{
			sys_mode=2;		
	}
	
	else
	{
		  sys_mode=0;	
	}
	
	if(pre_sys_flag==sys_mode)
	{
		
	}
	else
	{
			pre_sys_flag=sys_mode;
		  SYS_OUTO_OFF;
		  SYS_HAND_OFF;
	}

		
}

