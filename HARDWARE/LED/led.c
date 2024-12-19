#include "funct.h"

 /*
*******************************************************************************
**��    ��:LED_GPIO_Configuration()
**��    ��:LED�ƶ˿ڵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u32 int_send_time=0;
void LED_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	  //ʹ��GPIOB/C�˿�ʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);                     //�ر�jtag��ʹ��SWD��������SWDģʽ����	
	//PB   0/1/3/4/5/8/12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_15;                        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                         //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                         //IO���ٶ�Ϊ2MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PA  1/11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		    //IO���ٶ�Ϊ2MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//led
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	//485
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	
	//����
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	//LORA
	
	
} 
//������ʼ������
void KEY_Init(void)    //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTB

	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_3|GPIO_Pin_13|GPIO_Pin_14;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_11;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
//�̵�����ʼ��
void RELAY_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  //ʹ��GPIOC�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		    //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					        //�����趨������ʼ��GPIOC
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5);//��ʼ������Ϊ0,�رռ̵���
} 

//RGB��ʼ��
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
**��    ��:Buzzer_GPIO_Configuration()
**��    ��:�������˿ڵĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 Buzzer_flag=0;
void Buzzer_GPIO_Configuration(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				     
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					       //�����趨������ʼ��GPIOB
 GPIO_ResetBits(GPIOB,GPIO_Pin_11);						         //PB.8�����
 
} 
/********************************************************/
//��ʱ
/********************************************************/
void ws281X_delay(unsigned int delay_num)
{
  while(delay_num--);   
}
/********************************************************/
//д1
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
//д0
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
//��λ
/********************************************************/
void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(80);
}
/********************************************************/
//дһ���ֽڵ�����
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
//дһ���Ƶ���ɫ
/********************************************************/
u8 rgb_blink_flag=0;
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}
/********************************************************/
//��ɫ
/********************************************************/
void RGB_LED_white(void)
{
	 uint8_t i;
	//4��LEDȫ�ʵ�
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits( 0xff,  0xff,  0xff);
	}
}
/********************************************************/
//��ɫ
/********************************************************/
void RGB_LED_black(void)
{
	 uint8_t i;
	//4��LEDȫ�ʵ�
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits(0, 0, 0);
	}
}
/********************************************************/
//��ɫ
/********************************************************/
void RGB_LED_Red(void)
{
	 uint8_t i;
	//4��LEDȫ�ʵ�
	for(i=0;i<4;i++)
	{
		RGB_LED_Write_24Bits(0, 0xff, 0);
	}
}
/********************************************************/
//��ɫ
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
//��ɫ
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
  * @brief  ���͵���һ���Ƶ����ݣ���24bit��
  * @param  dat����ɫ��24λ����
  * @retval None
  */
void ws281x_sendOne(uint32_t dat)   
{
  uint8_t i;
  unsigned char byte;
  for(i = 24; i > 0; i--)
  {
    byte = ((dat>>i) & 0x01);  //λ��������ȡdat���ݵĵ�iλ
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

