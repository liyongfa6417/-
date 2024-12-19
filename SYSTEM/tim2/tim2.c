/********************************
ģ�麯��˵��
���ã���ʱ����ʼ��
��ע����		 
*********************************/
#include "funct.h"

/*
*******************************************************************************
**��    ��:TIM4_Configuration()
**��    ��:��������ⲿ�жϽ����ⲿ�����źŵĲɼ�
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:���ö�ʱ��4 ��Ϊʱ���źŽ��м�ʱ
*******************************************************************************
*/

void TIM4_Configuration(void)      
{	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Period=0xffff;		 						  /* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM4, ENABLE);				
}
/*
*******************************************************************************
**��    ��:EXTI_one_Config()
**��    ��:
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:���ö�ʱ��4 ��Ϊʱ���źŽ��м�ʱ
*******************************************************************************
*/
void EXTI_one_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
	/* config the extiline(PB14) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO,ENABLE);
	
  //NVIC_Configuration();
	/* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PB14) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* EXTI line(PB14) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);  

	/* config the NVIC*/
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //���ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
}
/*
*******************************************************************************
**��    ��:TIM2_Configuration
**��    ��:���ڲ���1ms �Ķ�ʱ���񣬿��Խ���������л�
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:����TIM2Ϊ1MS��ʱ�� 72Mhz
*******************************************************************************
*/
void TIM2_Configuration(void)
{
  //����TIM2 �ж� �ṹ��
  TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  //���� TIM2 ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  //TIM2ϵͳ����
  TIM_DeInit(TIM2);
  TIM2_TimeBaseStructure.TIM_Period =1001-1;	    //1ms
  TIM2_TimeBaseStructure.TIM_Prescaler = 72-1; 	    //72Mhz-1
  TIM2_TimeBaseStructure.TIM_ClockDivision = 0x00;  //����Ƶ
  TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ�����ʽ
  TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseStructure); // Time base configuration
  TIM_ClearFlag(TIM2,TIM_FLAG_Update);      // �����־λ
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  // ����TIM2�ж�
	//TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);  // �ر�TIM2�ж�
  //TIM2�ж����ȼ�����
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	 //ѡ��TIM2�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 //��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	         //ʹ���ж�ͨ��
  NVIC_Init(&NVIC_InitStructure); //��ʼ��NVIC
  TIM_Cmd(TIM2, ENABLE);  		  //��ʼ��TIM2	             
}

/*
*******************************************************************************
**��    ��:TIM2_IRQHandler
**��    ��:TIM2�ж���Ӧ���������ڴ����ж�ָ������־λ���л�
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:����1ms
*******************************************************************************
*/
u32 time2_counter=0;                                          //����ϵͳȫ��ʱ��Ŀ���
u8 task_flag[10]={0};                                         //���ڴ���������еı�־λ
const u16 task_flag_count[10]={903,203,1003,803,5003,703,9000,867,700,900};
void TIM2_IRQHandler(void)   
{
     u8 i;
     if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   //��ʱ��1ms
     { 		
		  //��ȡ�ɼ��ı�����������
	     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	  //�����־λ
			 
			 //������ʱ��
			 time2_counter++;
			 if(time2_counter>0xffff0000)
			 {
				   time2_counter=1;	
			 }
			 //������л�
				for(i=0;i<TASK_NUM;i++)
			 {
				 if(time2_counter%task_flag_count[i]==0)
				 {
					 task_flag[i]=1;
				 }
			 }
			 #if	EN_USART5
			  //����5�Ľ���
				if(USART_05.begin_flag==1)                         //������ڽ������ݿ�ʼ����ʱ����ۼ�
				{
					USART_05.usart_time_count++;
					if(USART_05.usart_time_count>=com_out_time)      //���ʱ�����100ms��Ϊһ֡���Ľ������
					{
						USART_05.start_rec_flag=0;
						USART_05.begin_flag=0;
					}		 
				}
				#endif
				#if	EN_USART4
			 //����4�Ľ���
				if(USART_04.begin_flag==1)                         //������ڽ������ݿ�ʼ����ʱ����ۼ�
				{
					USART_04.usart_time_count++;
					if(USART_04.usart_time_count>=com_out_time)      //���ʱ�����100ms��Ϊһ֡���Ľ������
					{
						USART_04.start_rec_flag=0;
						USART_04.begin_flag=0;
					}		 
				}
				#endif
			//����3�Ľ���
			if(USART_03.begin_flag==1)                         //������ڽ������ݿ�ʼ����ʱ����ۼ�
			{
				USART_03.usart_time_count++;
				if(USART_03.usart_time_count>=10)      //���ʱ�����100ms��Ϊһ֡���Ľ������
				{
					USART_03.start_rec_flag=0;
					USART_03.begin_flag=0;
				}		
			}
			//����2�Ľ���
			if(USART_02.begin_flag==1)                         //������ڽ������ݿ�ʼ����ʱ����ۼ�
			{
				USART_02.usart_time_count++;
				if(USART_02.usart_time_count>=com_out_time)      //���ʱ�����100ms��Ϊһ֡���Ľ������
				{
					USART_02.start_rec_flag=0;
					USART_02.begin_flag=0;
				}		
			}
			//����1�Ľ���
			if(USART_01.begin_flag==1)                         //������ڽ������ݿ�ʼ����ʱ����ۼ�
			{
				USART_01.usart_time_count++;
				if(USART_01.usart_time_count>=com_out_time)            //���ʱ�����100ms��Ϊһ֡���Ľ������
				{
					USART_01.start_rec_flag=0;
					USART_01.begin_flag=0;
				}
				
			}
			  
				
    }
}

/*
*******************************************************************************
**��    ��:EXTI15_10_IRQHandler
**��    ��:
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:Cppm=5000��(TH-2ms)/(TH+TL-4ms)
*******************************************************************************
*/
u16 co2_time=0;
void EXTI15_10_IRQHandler(void)
{
	//����ģ��һ
	if(EXTI_GetITStatus(EXTI_Line14) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)	//�����ش���	
		{
			TIM_SetCounter(TIM4, 0);
			co2_time=0;
		}
		else   //�½��ش���	
		{
			if(TIM_GetCounter(TIM4)>0)
			{
			    co2_time=TIM_GetCounter(TIM4);
				  POINT_IN.co2=co2_time/10*5;
				  CO2[0]=(u8)(POINT_IN.co2>>8);
			    CO2[1]=(u8)(POINT_IN.co2);
			}
				
			 
		}
	  
		EXTI_ClearITPendingBit(EXTI_Line14);     //����жϱ�־λ
	}
	
}
/*
*******************************************************************************
**��    ����TIM3_PWM_Init
**��    ��: PWM��ʼ������
**��    ��: arr���Զ���װֵ ��psc��ʱ��Ԥ��Ƶ��
**�� �� ֵ: ��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  //����ϵͳ��RCCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);      //��ʱ��4
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     //ʹ��GPIO�����AFIO���ù���ģ��ʱ�� 
  //���ø�����Ϊ�����������,���TIM3 CH1��PWM���岨��	GPIOA.6  CH2��PWM���岨��	GPIOA.7
	//TIM3_CH1,TIM3_CH2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                //��ʼ��GPIO

	
   //��ʼ��TIM
	TIM_TimeBaseStructure.TIM_Period = arr;     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc;   //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIM3��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
	
	/*********TIM3��ʱ��--------------------------------------------------------------------------*/
//	TIM_OCInitStructure.TIM_Pulse = 0;                 //�趨��װ��Ĳ���Ƚϵ�����ֵ����ʼ��ռ�ձ�
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);           //����Tָ���Ĳ�����ʼ������TIM3 OC3
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;                 //�趨��װ��Ĳ���Ƚϵ�����ֵ����ʼ��ռ�ձ�
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);           //����Tָ���Ĳ�����ʼ������TIM3 OC4
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���	

  TIM_ARRPreloadConfig(TIM3, ENABLE);                //ʹ��TIM2,TIM3,TIM4��ARR��Ԥװ�Ĵ���
	
//	TIM_SetCompare3(TIM3,53000);
//	TIM_SetCompare4(TIM4,0);
//	
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM4
}
/*
*******************************************************************************
**��    ����TIM8_PWM_Init
**��    ��: PWM��ʼ������
**��    ��: arr���Զ���װֵ ��psc��ʱ��Ԥ��Ƶ��
**�� �� ֵ: ��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void TIM8_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  //����ϵͳ��RCCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);      //��ʱ��8
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);     //ʹ��GPIO�����AFIO���ù���ģ��ʱ�� 
  //���ø�����Ϊ�����������,���TIM3 CH3��PWM���岨��	GPIOB.0  CH4��PWM���岨��	GPIOB.1
	//TIM3_CH3,TIM3_CH4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);                //��ʼ��GPIOC
	
   //��ʼ��TIM
	TIM_TimeBaseStructure.TIM_Period = arr;     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc;   //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIM3��ʱ�������λ
	
	//��ʼ��TIM8 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
	
	/*********TIM3��ʱ��--------------------------------------------------------------------------*/
  TIM_OCInitStructure.TIM_Pulse = 0;                 //�趨��װ��Ĳ���Ƚϵ�����ֵ����ʼ��ռ�ձ�
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);           //����Tָ���Ĳ�����ʼ������TIM3 OC3

	TIM_OCInitStructure.TIM_Pulse = 0;                 //�趨��װ��Ĳ���Ƚϵ�����ֵ����ʼ��ռ�ձ�
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);           //����Tָ���Ĳ�����ʼ������TIM3 OC4
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 

	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM8��CCR3�ϵ�Ԥװ�ؼĴ���	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM8��CCR4�ϵ�Ԥװ�ؼĴ���	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM8��CCR1�ϵ�Ԥװ�ؼĴ���	

  TIM_CtrlPWMOutputs(TIM8,ENABLE);    //MOE �����ʹ��   
	
  TIM_ARRPreloadConfig(TIM8, ENABLE);                //ʹ��TIM2,TIM3,TIM4��ARR��Ԥװ�Ĵ���

	TIM_Cmd(TIM8, ENABLE);                              //ʹ��TIM8
}

/******************* (C) COPYRIGHT 2012 yunyi Team *****END OF FILE****/


