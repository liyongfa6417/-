#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
#include "delay.h"

#define KEY0     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) 
#define KEY1     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)   
#define KEY2     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)  
#define KEY3     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)

#define SYS1_SWITCH       GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)   //系统开关1

#define SYS2_SWITCH       GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)   //系统开关2

#define SOFA1_SWITCH      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)    

#define SOFA2_SWITCH      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)

extern u8 sys_mode;
extern u8 run_flag;
extern u8 pre_sys_flag;

//while(AUX_P);
void KEY_Init(void);
void Key_scan(void);

#endif


