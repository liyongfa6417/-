#include "music_ctrl.h"
/*
*******************************************************************************
**��    ��:Music_Init()
**��    ��:����оƬ�˿ڵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void Music_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //ʹ��PORTBʱ��

	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PB12 BUSY
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB12
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB4 DATA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB4
	

} 

/*
*******************************************************************************
**��    ��:Line_1A_WTN6()
**��    ��:���ֲ��ź��������Ŷ�Ӧ��ַ������
**��    ��:SB_DATA�����������ĵ�ַ
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void Line_1A_WTN6(u8 SB_DATA)
{
	u8 S_DATA,j;
	u8 B_DATA;
	S_DATA =SB_DATA;
	P_DATA =0;
	delay_ms(5);
  B_DATA=S_DATA&0X01;
	
	for(j=0;j<8;j++)
	{
		if(B_DATA==1)
		{
			P_DATA=1;
			delay_us(600);
			P_DATA=0;
			delay_us(200);
		}
		else
		{
			P_DATA=1;
			delay_us(200);
			P_DATA=0;
			delay_us(600);
		}
		S_DATA=S_DATA>>1;
		B_DATA=S_DATA&0x01;
	}
		P_DATA=1;
	
}


