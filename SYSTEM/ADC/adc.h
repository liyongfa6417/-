#ifndef __adc_H
#define __adc_H	

#include "stm32f10x.h"

#define ADD_VOL   50

#define VOL_UP      1200
#define VOL_MID     1100
#define VOL_DOWN    1000

extern u16 ozone_num;
extern float ozone_vol;

extern void Adc_Configuration(void);    //ADC ≥ı ºªØ
extern u16  Get_Adc(u8 ch); 
extern u16 Get_Adc_Average(u8 ch,u8 times); 
extern u16 Get_Real_Value(u8 ch);
extern void GetOzoneData(void);
 
#endif 
