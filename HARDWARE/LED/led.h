#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
 
#define ON 0
#define OFF 1

//led灯对应的定义
#define LED0_RED     PBout(12)
//#define LED1_RED     PBout(15) 

//COM1
#define COM1_EN       PBout(15)

//COM2
#define COM2_EN       PAout(1)

//COM3
#define COM3_EN       PBout(1)

//#define COM3_RST      PBout(1)
//#define COM3_NET      PBout(0)

//COM4
#define COM4_EN       PAout(15)

#define COM4_M0      PBout(5)
#define COM4_M1      PBout(4)
//#define COM4_AUX     PBout(3)

#define E32_SWI_TO_TRANSMIT()		COM4_M0 = 0; COM4_M1 = 0		// 透传模式	
#define E32_SWI_TO_AWAKE()			COM4_M0 = 1; COM4_M1 = 0		// 唤醒模式
#define E32_SWI_TO_SAVE()			  COM4_M0 = 0; COM4_M1 = 1		// 省电模式
#define E32_SWI_TO_SLEEP()			COM4_M0 = 1; COM4_M1 = 1		// 休眠模式

#define AUX                     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define AUX_FLAG                GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)    //AUX识别
#define AUX_P                   (AUX_FLAG==0)

//COM5
#define COM5_EN       PBout(3)

#define POWR_ON       PBout(0)=0
#define POWR_OFF      PBout(0)=1


//inter on
#define INT_EN       PAout(8)
#define INT_ON       INT_EN=1;
#define INT_OFF      INT_EN=0;

#define 	RGB_LED 	GPIO_Pin_9
#define		RGB_LED_HIGH	(GPIO_SetBits(GPIOC,RGB_LED))
#define 	RGB_LED_LOW		(GPIO_ResetBits(GPIOC,RGB_LED))


#define DS3231_INT              PBout(8)

#define DS3231_INT_ON           PBout(8) =1
#define DS3231_INT_OFF          PBout(8) =0

#define DS3231_RST              PBout(9)
 
#define DS3231_RST_ON           PBout(9) =1
#define DS3231_RST_OFF          PBout(9) =0

#define Buzzer     PAout(11)

#define PM25_RST              PAout(4)

#define RELAY1_EN   PCout(4) //继电器1
#define RELAY2_EN   PCout(5) //继电器2


#define RELAY_1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4) //开关1
#define RELAY_2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) //开关2

#define SW_1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) //开关1
#define SW_2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) //开关2
//#define SW_3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) //开关3

extern u8 Buzzer_flag;
extern u32 int_send_time;
void KEY_Init(void) ;   //IO初始化
void RELAY_GPIO_Configuration(void);
void LED_GPIO_Configuration(void);
void Buzzer_GPIO_Configuration(void);
void RGB_LED_Init(void);

void ws281X_delay(unsigned int delay_num);//WS2812延时函数
void RGB_LED_Write0(void);
void RGB_LED_Write1(void);
void RGB_LED_Reset(void);
void RGB_LED_Write_Byte(uint8_t byte);
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue);
void RGB_LED_white(void);
void RGB_LED_black(void);
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);
void ws281x_sendOne(uint32_t dat);		 				    
#endif
