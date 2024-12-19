#include "key.h"
#include "led.h"
#include "funct.h"

/*
*******************************************************************************
**函    数:KEY_Init()
**功    能:按键端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/

//按键初始化函数
void KEY_Init(void)    //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);//使能PORTA,PORTB时钟

	//A12模式识别
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化GPIOA
	//雷达模块
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置浮空输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                //初始化GPIOB
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         //
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                //初始化GPIOB

}
/*
*******************************************************************************
**函    数:Key_scan()
**功    能:按键的扫描
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u8 sys_mode=0;//系统运行模式 0位关机，1是手动，2是自动
u8 run_flag=1;//运行标志位
u8 pre_sys_flag=0;
void Key_scan(void)
{
	//系统模式选择
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

