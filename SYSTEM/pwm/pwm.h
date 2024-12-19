#ifndef _PWM_H
#define _PWM_H
#include "sys.h"

extern u16 led0pwmval;

void TIM3_PWM_Init(u16 arr,u16 psc);

#endif

