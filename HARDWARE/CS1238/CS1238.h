#ifndef __CS1238_H
#define __CS1238_H
#include "sys.h"
#include "delay.h"

extern unsigned long int R_AD0_Data;

#define NOP1() delay_us(2)
#define NOP2() delay_us(4)
#define NOP4() delay_us(8)

#define SET_SEN12_CS1238_OUT_IN()		{GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=(u32)8<<4;}
#define SET_SEN12_CS1238_OUT_NORMAL()	{GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=(u32)3<<4;}

#define SEN12_CS1238_SCLK	  			PAout(2) 
#define SEN12_CS1238_DOUT	  			PAout(1)


#define spi_clk_1 GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define spi_clk_0 GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define spi_dat_1 GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define spi_dat_0 GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define IO_Data_AD (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==1)

void F_Delay(void);
void spi_data_input(void);
void spi_data_output(void);

extern void MX_GPIO_Init(void);
extern void	F_Read_AD(void);
extern unsigned char	F_Rd_AdReg(void);
extern void	F_Wr_AdReg(unsigned char R_AdReg);




extern void InitCs1238_1(void);
extern ULONG Writes1238Chanel12Datas(BYTE value );

#endif 
/*------------------------ Nothing Below This Line --------------------------*/

