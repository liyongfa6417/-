#ifndef __MUSIC_H
#define __MUSIC_H	 
#include "sys.h"
#include "delay.h"

#define P_DATA PBout(4)	// ����DATA
//#define P_BUSY PBout(12)   //����BUSY

void Music_Init(void);
void Line_1A_WTN6(u8 SB_DATA);   
#endif
