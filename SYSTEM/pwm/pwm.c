#include "pwm.h"
u16 led0pwmval=1799;
/*
*******************************************************************************
**函    数:TIM3_PWM_Init(u16 arr,u16 psc) 
**功    能:PWM初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
1、端口的定义根据实际的端口进行定义；
2、是否需要重映射，进行GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)；
3、TIM_OC3Init和TIM_OC3PreloadConfig前面的数字需要与通道的数字一一对应；
4、TIM_SetCompare3函数为占空比的填充前面的数字需要与通道一一对应；
*******************************************************************************
*/
void TIM3_PWM_Init(u16 arr,u16 psc) 
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	                        //使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH3->PB0   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);               //初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;                      //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;                    //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                 //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);                      //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);             //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);                                        //使能TIM3
	
}


