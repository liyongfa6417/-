#ifndef __MUSIC_H
#define __MUSIC_H	 
#include "sys.h"
#include "delay.h"

#define P_DATA PBout(4)	// ”Ô“ÙDATA
//#define P_BUSY PBout(12)   //”Ô“ÙBUSY

void Music_Init(void);
void Line_1A_WTN6(u8 SB_DATA);   
#endif
