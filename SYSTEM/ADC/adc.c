#include "adc.h"
#include "delay.h"
 
/*
*******************************************************************************
**��    ��:Adc_Configuration
**��    ��:ADC���ܵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
1���Զ˿ڽ������ã�
2��
*******************************************************************************
*/		   													   
void  Adc_Configuration(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
}	

/*
*******************************************************************************
**��    ��:Get_Adc
**��    ��:
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u16 Get_Adc(u8 ch)   
{
  //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		     //ʹ��ָ����ADC1�����ת����������	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	         //�������һ��ADC1�������ת�����
}
/*
*******************************************************************************
**��    ��:
**��    ��:
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��://��ƽ��ֵ �˲�
*******************************************************************************
*/

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=(u32)Get_Adc(ch);
		delay_ms(5);
	}
	return (u16)(temp_val/times);
}
/*
*******************************************************************************
**��    ��:Get_Real_Value
**��    ��:
**��    ��:ch
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u16 Get_Real_Value(u8 ch)
{
	u16 temp;
	temp = Get_Adc_Average(ch,2);

  return   temp;
}


u16 ozone_num=0;
float ozone_vol=0;
//��ȡ��ѹ��Ϣ
void GetOzoneData(void)
{
	u16 myozone=0;
	myozone=Get_Adc_Average(ADC_Channel_5,1);
	//ozone_num=myozone;
	//myozone=myozone/14*5/3.3;
	ozone_vol=(myozone*11)/(25/2);
	myozone=(u16)ozone_vol;
	//nydy=myozone;
	if(myozone > 250)  
	{ 
		myozone=(490-myozone)*2/1.5-85;
	}
	else
	{
		if(150 > myozone )  
		{
			myozone=1200;
		}	
		else	
		{
		  myozone=(250-myozone)*10+200;
		}
	}
	ozone_num=myozone;
//	OZONE[0]=myozone&0X00FF;
//  OZONE[1]=myozone>>8;
}

/******************* (C) COPYRIGHT 2012 yunyi Team *****END OF FILE****/
























