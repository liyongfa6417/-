/********************************
模块函数说明
作用：定时器初始化
备注：无		 
*********************************/
#include "funct.h"

/*
*******************************************************************************
**函    数:TIM4_Configuration()
**功    能:用于配合外部中断进行外部触发信号的采集
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:配置定时器4 作为时基信号进行计时
*******************************************************************************
*/

void TIM4_Configuration(void)      
{	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Period=0xffff;		 						  /* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM4, ENABLE);				
}
/*
*******************************************************************************
**函    数:EXTI_one_Config()
**功    能:
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:配置定时器4 作为时基信号进行计时
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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 下拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* EXTI line(PB14) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);  

	/* config the NVIC*/
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //边沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
}
/*
*******************************************************************************
**函    数:TIM2_Configuration
**功    能:用于产生1ms 的定时任务，可以进行任务的切换
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:配置TIM2为1MS定时器 72Mhz
*******************************************************************************
*/
void TIM2_Configuration(void)
{
  //定义TIM2 中断 结构体
  TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  //配置 TIM2 时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  //TIM2系统配置
  TIM_DeInit(TIM2);
  TIM2_TimeBaseStructure.TIM_Period =1001-1;	    //1ms
  TIM2_TimeBaseStructure.TIM_Prescaler = 72-1; 	    //72Mhz-1
  TIM2_TimeBaseStructure.TIM_ClockDivision = 0x00;  //不分频
  TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数方式
  TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseStructure); // Time base configuration
  TIM_ClearFlag(TIM2,TIM_FLAG_Update);      // 清楚标志位
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  // 开启TIM2中断
	//TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);  // 关闭TIM2中断
  //TIM2中断优先级配置
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	 //选择TIM2中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 //先占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 //从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	         //使能中断通道
  NVIC_Init(&NVIC_InitStructure); //初始化NVIC
  TIM_Cmd(TIM2, ENABLE);  		  //初始化TIM2	             
}

/*
*******************************************************************************
**函    数:TIM2_IRQHandler
**功    能:TIM2中断响应函数，用于处理中断指令及任务标志位的切换
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:周期1ms
*******************************************************************************
*/
u32 time2_counter=0;                                          //进行系统全局时间的控制
u8 task_flag[10]={0};                                         //用于存放任务运行的标志位
const u16 task_flag_count[10]={903,203,1003,803,5003,703,9000,867,700,900};
void TIM2_IRQHandler(void)   
{
     u8 i;
     if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   //定时到1ms
     { 		
		  //提取采集的编码器脉冲数
	     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	  //清楚标志位
			 
			 //基础计时器
			 time2_counter++;
			 if(time2_counter>0xffff0000)
			 {
				   time2_counter=1;	
			 }
			 //任务的切换
				for(i=0;i<TASK_NUM;i++)
			 {
				 if(time2_counter%task_flag_count[i]==0)
				 {
					 task_flag[i]=1;
				 }
			 }
			 #if	EN_USART5
			  //串口5的接收
				if(USART_05.begin_flag==1)                         //如果正在接收数据开始进行时间的累加
				{
					USART_05.usart_time_count++;
					if(USART_05.usart_time_count>=com_out_time)      //如果时间大于100ms认为一帧报文接收完成
					{
						USART_05.start_rec_flag=0;
						USART_05.begin_flag=0;
					}		 
				}
				#endif
				#if	EN_USART4
			 //串口4的接收
				if(USART_04.begin_flag==1)                         //如果正在接收数据开始进行时间的累加
				{
					USART_04.usart_time_count++;
					if(USART_04.usart_time_count>=com_out_time)      //如果时间大于100ms认为一帧报文接收完成
					{
						USART_04.start_rec_flag=0;
						USART_04.begin_flag=0;
					}		 
				}
				#endif
			//串口3的接收
			if(USART_03.begin_flag==1)                         //如果正在接收数据开始进行时间的累加
			{
				USART_03.usart_time_count++;
				if(USART_03.usart_time_count>=10)      //如果时间大于100ms认为一帧报文接收完成
				{
					USART_03.start_rec_flag=0;
					USART_03.begin_flag=0;
				}		
			}
			//串口2的接收
			if(USART_02.begin_flag==1)                         //如果正在接收数据开始进行时间的累加
			{
				USART_02.usart_time_count++;
				if(USART_02.usart_time_count>=com_out_time)      //如果时间大于100ms认为一帧报文接收完成
				{
					USART_02.start_rec_flag=0;
					USART_02.begin_flag=0;
				}		
			}
			//串口1的接收
			if(USART_01.begin_flag==1)                         //如果正在接收数据开始进行时间的累加
			{
				USART_01.usart_time_count++;
				if(USART_01.usart_time_count>=com_out_time)            //如果时间大于100ms认为一帧报文接收完成
				{
					USART_01.start_rec_flag=0;
					USART_01.begin_flag=0;
				}
				
			}
			  
				
    }
}

/*
*******************************************************************************
**函    数:EXTI15_10_IRQHandler
**功    能:
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:Cppm=5000×(TH-2ms)/(TH+TL-4ms)
*******************************************************************************
*/
u16 co2_time=0;
void EXTI15_10_IRQHandler(void)
{
	//超声模块一
	if(EXTI_GetITStatus(EXTI_Line14) != RESET) //确保是否产生了EXTI Line中断
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)	//上升沿触发	
		{
			TIM_SetCounter(TIM4, 0);
			co2_time=0;
		}
		else   //下降沿触发	
		{
			if(TIM_GetCounter(TIM4)>0)
			{
			    co2_time=TIM_GetCounter(TIM4);
				  POINT_IN.co2=co2_time/10*5;
				  CO2[0]=(u8)(POINT_IN.co2>>8);
			    CO2[1]=(u8)(POINT_IN.co2);
			}
				
			 
		}
	  
		EXTI_ClearITPendingBit(EXTI_Line14);     //清除中断标志位
	}
	
}
/*
*******************************************************************************
**函    数：TIM3_PWM_Init
**功    能: PWM初始化函数
**参    数: arr：自动重装值 ，psc：时钟预分频数
**返 回 值: 无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  //配置系统的RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);      //定时器4
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     //使能GPIO外设和AFIO复用功能模块时钟 
  //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形	GPIOA.6  CH2的PWM脉冲波形	GPIOA.7
	//TIM3_CH1,TIM3_CH2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化GPIO

	
   //初始化TIM
	TIM_TimeBaseStructure.TIM_Period = arr;     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;   //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIM3的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //输出极性:TIM输出比较极性低
	
	/*********TIM3定时器--------------------------------------------------------------------------*/
//	TIM_OCInitStructure.TIM_Pulse = 0;                 //设定待装入的捕获比较的脉冲值，初始的占空比
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);           //根据T指定的参数初始化外设TIM3 OC3
//	
//	TIM_OCInitStructure.TIM_Pulse = 0;                 //设定待装入的捕获比较的脉冲值，初始的占空比
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);           //根据T指定的参数初始化外设TIM3 OC4
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器	

  TIM_ARRPreloadConfig(TIM3, ENABLE);                //使能TIM2,TIM3,TIM4在ARR上预装寄存器
	
//	TIM_SetCompare3(TIM3,53000);
//	TIM_SetCompare4(TIM4,0);
//	
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);

	TIM_Cmd(TIM3, ENABLE);  //使能TIM4
}
/*
*******************************************************************************
**函    数：TIM8_PWM_Init
**功    能: PWM初始化函数
**参    数: arr：自动重装值 ，psc：时钟预分频数
**返 回 值: 无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void TIM8_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  //配置系统的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);      //定时器8
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);     //使能GPIO外设和AFIO复用功能模块时钟 
  //设置该引脚为复用输出功能,输出TIM3 CH3的PWM脉冲波形	GPIOB.0  CH4的PWM脉冲波形	GPIOB.1
	//TIM3_CH3,TIM3_CH4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);                //初始化GPIOC
	
   //初始化TIM
	TIM_TimeBaseStructure.TIM_Period = arr;     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;   //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIM3的时间基数单位
	
	//初始化TIM8 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //输出极性:TIM输出比较极性低
	
	/*********TIM3定时器--------------------------------------------------------------------------*/
  TIM_OCInitStructure.TIM_Pulse = 0;                 //设定待装入的捕获比较的脉冲值，初始的占空比
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);           //根据T指定的参数初始化外设TIM3 OC3

	TIM_OCInitStructure.TIM_Pulse = 0;                 //设定待装入的捕获比较的脉冲值，初始的占空比
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);           //根据T指定的参数初始化外设TIM3 OC4
	
	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 

	TIM_OCInitStructure.TIM_Pulse = 0;                
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR3上的预装载寄存器	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR4上的预装载寄存器	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR2上的预装载寄存器	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR1上的预装载寄存器	

  TIM_CtrlPWMOutputs(TIM8,ENABLE);    //MOE 主输出使能   
	
  TIM_ARRPreloadConfig(TIM8, ENABLE);                //使能TIM2,TIM3,TIM4在ARR上预装寄存器

	TIM_Cmd(TIM8, ENABLE);                              //使能TIM8
}

/******************* (C) COPYRIGHT 2012 yunyi Team *****END OF FILE****/


