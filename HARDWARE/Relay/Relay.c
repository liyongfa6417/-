#include "Relay.h"
 /*
*******************************************************************************
**函    数:void Relay_Init(void)
**功    能:继电器端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void Relay_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				     //端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					       
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;				  
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	

	 MOTOR1_ANODE_OFF(); //关闭电机1
	 MOTOR2_ANODE_OFF(); //关闭电机2
   O3_ANODE_OFF();     //关闭臭氧
}
/*
*******************************************************************************
**函    数:void Relay_control(void)
**功    能:继电器控制
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/

void Relay_control (void)
{
	
	
}


