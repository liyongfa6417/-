#include "adc.h"
#include "delay.h"
 
/*
*******************************************************************************
**函    数:Adc_Configuration
**功    能:ADC功能的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
1、对端口进行配置；
2、
*******************************************************************************
*/		   													   
void  Adc_Configuration(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
}	

/*
*******************************************************************************
**函    数:Get_Adc
**功    能:
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u16 Get_Adc(u8 ch)   
{
  //设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		     //使能指定的ADC1的软件转换启动功能	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	         //返回最近一次ADC1规则组的转换结果
}
/*
*******************************************************************************
**函    数:
**功    能:
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明://求平均值 滤波
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
**函    数:Get_Real_Value
**功    能:
**参    数:ch
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
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
//获取电压信息
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
























