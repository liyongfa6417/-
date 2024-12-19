#ifndef __RELAY_H
#define __RELAY_H	 
#include "sys.h"

#define MOTOR1_ANODE              PBout(12)                 //1号电机控制

#define MOTOR1_ANODE_ON()				  PBout(12) = 1							
#define MOTOR1_ANODE_OFF()				PBout(12) = 0							

#define MOTOR2_ANODE              PBout(14)                 //2号电机控制

#define MOTOR2_ANODE_ON()				  PBout(14) = 1							
#define MOTOR2_ANODE_OFF()				PBout(14) = 0		

#define O3_ANODE              PAout(8)                      //臭氧控制开关

#define O3_ANODE_ON()				  PAout(8) = 1							
#define O3_ANODE_OFF()				PAout(8) = 0		

extern void Relay_Init(void);
//extern void Relay_on (void);

 
		 				    
#endif
