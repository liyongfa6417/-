#include "music_ctrl.h"
/*
*******************************************************************************
**函    数:Music_Init()
**功    能:音乐芯片端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void Music_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //使能PORTB时钟

	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PB12 BUSY
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB12
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PB4 DATA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB4
	

} 

/*
*******************************************************************************
**函    数:Line_1A_WTN6()
**功    能:音乐播放函数，播放对应地址的语音
**参    数:SB_DATA，播放语音的地址
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
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


