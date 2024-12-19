#include "funct.h"

 /*
*******************************************************************************
**函    数:LED_GPIO_Configuration()
**功    能:LED灯端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u32 int_send_time=0;
void LED_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	  //使能GPIOB/C端口时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);                     //关闭jtag，使能SWD，可以用SWD模式调试	
	//PB   0/1/3/4/5/8/12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_15;                        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO口速度为2MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PA  1/11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		    //IO口速度为2MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//led
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	//485
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	
	//网络
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	//LORA
	
	
} 
//按键初始化函数
void KEY_Init(void)    //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB

	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_3|GPIO_Pin_13|GPIO_Pin_14;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_11;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
//继电器初始化
void RELAY_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  //使能GPIOC端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		    //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					        //根据设定参数初始化GPIOC
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5);//初始化设置为0,关闭继电器
} 

//RGB初始化
void RGB_LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOC, &GPIO_InitStructure);					
	GPIO_SetBits(GPIOC,GPIO_Pin_9);						 
}
 /*
*******************************************************************************
**函    数:Buzzer_GPIO_Configuration()
**功    能:蜂鸣器端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u8 Buzzer_flag=0;
void Buzzer_GPIO_Configuration(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				     
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					       //根据设定参数初始化GPIOB
 GPIO_ResetBits(GPIOB,GPIO_Pin_11);						         //PB.8输出低
 
} 
/********************************************************/
//延时
/********************************************************/
void ws281X_delay(unsigned int delay_num)
{
  while(delay_num--);   
}
/********************************************************/
//写1
/********************************************************/
void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
//	PBout(6)=0;  0.7us
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
	__nop(); __nop(); __nop();

	
	RGB_LED_LOW;
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop();

}

/********************************************************/
//写0
/********************************************************/
void RGB_LED_Write0(void)
{
	
	RGB_LED_HIGH;
  __nop(); __nop(); __nop(); __nop(); 
	
	RGB_LED_LOW;  
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	
	__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); 
}
/********************************************************/
//复位
/********************************************************/
void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(80);
}
/********************************************************/
//写一个字节的数据
/********************************************************/
void RGB_LED_Write_Byte(uint8_t byte)
{
	uint8_t i;

	for(i=0;i<8;i++)
	{
		if(byte&0x80)
		{
				RGB_LED_Write1();
		}
		else
		{
				RGB_LED_Write0();
		}
		byte <<= 1;
	}
}
/********************************************************/
//写一个灯的颜色
/********************************************************/
u8 rgb_blink_flag=0;
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}
/********************************************************/
//白色
/********************************************************/
void RGB_LED_white(void)
{
	 uint8_t i;
	//4个LED全彩灯
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits( 0xff,  0xff,  0xff);
	}
}
/********************************************************/
//黑色
/********************************************************/
void RGB_LED_black(void)
{
	 uint8_t i;
	//4个LED全彩灯
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits(0, 0, 0);
	}
}
/********************************************************/
//红色
/********************************************************/
void RGB_LED_Red(void)
{
	 uint8_t i;
	//4个LED全彩灯
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits(0, 0xff, 0);
	}
}
/********************************************************/
//绿色
/********************************************************/
void RGB_LED_Green(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits(0xFF, 0x00, 0x00);
	}
}
/********************************************************/
//蓝色
/********************************************************/
void RGB_LED_Blue(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
			RGB_LED_Write_24Bits(0, 0, 0xff);
	}
}
/**
  * @brief  发送点亮一个灯的数据（即24bit）
  * @param  dat：颜色的24位编码
  * @retval None
  */
void ws281x_sendOne(uint32_t dat)   
{
  uint8_t i;
  unsigned char byte;
  for(i = 24; i > 0; i--)
  {
    byte = ((dat>>i) & 0x01);  //位操作，读取dat数据的第i位
    if(byte == 1)
    {
      RGB_LED_Write1();
    }
    else
    {
      RGB_LED_Write0();
    }
  }
}

/******************* (C) COPYRIGHT 2012 yunyi Team *****END OF FILE****/

