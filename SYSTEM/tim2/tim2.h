#ifndef __tim2_H
#define __tim2_H

#include "stm32f10x.h"

#define ABS(x) ((x)>=0?(x):(-(x)))

//==========�궨��===========//
#define OVER_TIME_SECOND 5

#define OVER_TIME   1000*OVER_TIME_SECOND  //100*OVER_TIME_SECOND*10ms

#define TASK_NUM 5


//=========��������===========//
extern u32 time2_counter;
extern u8 task_flag[10];
extern u16 co2_time;
extern const u16 task_flag_count[10];

//=========��������============//
extern void TIM2_Configuration(void);
extern void EXTI_one_Config(void);
extern void TIM4_Configuration(void) ;
extern void TIM3_PWM_Init(u16 arr,u16 psc);
extern void TIM8_PWM_Init(u16 arr,u16 psc);


#endif
