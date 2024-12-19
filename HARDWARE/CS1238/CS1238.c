#include "CS1238.h"

unsigned long int R_AD0_Data;
unsigned long int R_AD0_Data_end;


void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOA时钟

  /*Configure GPIO pin : PA1 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  ;        //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void F_Delay(void)
{
  unsigned int i;
  for(i=0;i<40;i++) ;
}

void spi_data_input(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOA时钟

  /*Configure GPIO pin : PA1 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  ;        //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void spi_data_output(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOA时钟

  /*Configure GPIO pin : PA1 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}


void Init1237(void)
{
	spi_data_input();
	R_AD0_Data=0;
}
 /*
*******************************************************************************
**函    数:InitCs1238_1()
**功    能:CS1238通信端口的初始化
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/

//MX_GPIO_Init();

 void InitCs1238_1(void)
 {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOA时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
	 
	SET_SEN12_CS1238_OUT_IN();
	 
	 // 初始化端口
	SEN12_CS1238_SCLK = 0;
	while(SEN12_CS1238_DOUT);
	Writes1238Chanel12Datas(0x00);
	 
 }
 
 /*
 +----------------------------------------------------------------------------+
 | 写数据先读出AD值高8位位通道和配置，value新的配置                           |
 +----------------------------------------------------------------------------+
 */
 ULONG Writes1238Chanel12Datas(BYTE value )
 {
	//BOOL old_EA;
	BYTE i;
	BYTE ctemp;
	ULONG ad_chnl_value;

	ad_chnl_value = 0;

	for (i = 0; i < 24; i++)					// 读出24位AD值
	{
	 	SEN12_CS1238_SCLK = 1;
		ad_chnl_value <<= 1;
		NOP4();
	 	SEN12_CS1238_SCLK = 0;
		NOP1();
		ad_chnl_value |= SEN12_CS1238_DOUT;
	}

	for ( ; i < 27; i++)						// 25 26 27完成读数据并把OUT拉高
	{
	 	SEN12_CS1238_SCLK = 1;
		NOP4();
	 	SEN12_CS1238_SCLK = 0;
		NOP1();
	}
	for ( ; i < 29; i++)						//  28 29完成OUT转换
	{
	 	SEN12_CS1238_SCLK = 1;
		NOP4();
	 	SEN12_CS1238_SCLK = 0;
		NOP1();
	}
	SET_SEN12_CS1238_OUT_NORMAL();
	ctemp = 0x65;								// 配置读数据
	ctemp <<= 1;
	for ( ; i < 36; i++)						// 写配置读数据
	{
	 	SEN12_CS1238_SCLK = 1;

		if(ctemp & 0x80)
		{
			SEN12_CS1238_DOUT = 1;
		}
		else
		{
			SEN12_CS1238_DOUT = 0;
		}
		NOP2();
	 	SEN12_CS1238_SCLK = 0;
		ctemp <<= 1;
		NOP1();
	}

 	SEN12_CS1238_SCLK = 1;						// 37个时钟切换OUT方向
	NOP4();
 	SEN12_CS1238_SCLK = 0;
	NOP2();
	i++;

	for (; i < 45; i++)							// 读出数据
	{
	 	SEN12_CS1238_SCLK = 1;

		if(value & 0x80)
		{
			SEN12_CS1238_DOUT = 1;
		}
		else
		{
			SEN12_CS1238_DOUT = 0;
		}
		NOP2();
	 	SEN12_CS1238_SCLK = 0;
		value <<= 1;
		NOP1();
	}

 	SEN12_CS1238_SCLK = 1;						// 46个时钟拉高OUT方向
	NOP4();
 	SEN12_CS1238_SCLK = 0;
	NOP4();



	SET_SEN12_CS1238_OUT_IN();

//	ad_chnl_value |= (ULONG)ctemp << 24;

	return ad_chnl_value;
 }
/************************************************/
 /*-----------------------------------------------------------------------------
Name	: F_AD_Clock
Function: ADC clock
-----------------------------------------------------------------------------*/
void	F_AD_Clock(void)
{
	spi_clk_1;
	F_Delay();
	spi_clk_0;
	F_Delay();	
}

/*-----------------------------------------------------------------------------
Name	: F_Read_AD_Byte
Function: read 3 byte ADC
-----------------------------------------------------------------------------*/
void	F_Read_AD(void)
{
	unsigned char	i;
	R_AD0_Data = 0;

	while(IO_Data_AD);
	
	for(i = 0; i < 24; i++)				//send 24 CLK,for recive data
	{
		R_AD0_Data <<= 1;
		F_AD_Clock();
		if(IO_Data_AD)
		{
			R_AD0_Data |=1;
		}
	}
	
	F_AD_Clock();
	F_AD_Clock();
	F_AD_Clock();						//CLK27,pull up DRDY
	
	R_AD0_Data_end=R_AD0_Data;
	//it must 46 CLK(NOT 27 CLK),when read/write over two
	//(at frist 24 CLK for read data, after 22 CLK)
//	EIC20_EIE0 = 1;						//restart MCU_DAT pin for exti interrupt
}

/*-----------------------------------------------------------------------------
Name	: F_Rd_AdReg
Function: read ADC register
-----------------------------------------------------------------------------*/
unsigned char	F_Rd_AdReg(void)
{	
	unsigned char i;
	unsigned char R_Temp;

	//----------------------------------
	//1 ~ 3:clk1-clk27
	//----------------------------------
 while(IO_Data_AD);	
	for(i = 0; i < 27; i++)
	{
		F_AD_Clock();
	}

	//----------------------------------
	//4:clk28-clk29
	//----------------------------------
	spi_data_output();					//set MCU_Data output
	F_AD_Clock();	
	F_AD_Clock();

	//----------------------------------
	//5:clk30-clk36(send read register)
	//----------------------------------		
	R_Temp = 0xAC;					//read command(0x56) left move 1 bit
	for(i = 0; i < 7; i ++)
	{
		if(R_Temp&0x80)				//MSB
		{
			spi_dat_1;
		}
		else
		{
			spi_dat_0;
		}
		R_Temp = R_Temp << 1;
		F_AD_Clock();
	}

	//----------------------------------
	//6:clk37
	//----------------------------------
	spi_data_input();					//set MCU_Data input
	F_AD_Clock();	
	
	//----------------------------------
	//7:clk38-clk45(read register)
	//----------------------------------	
	R_Temp	= 0;
	for(i = 0; i < 8; i++)
	{
		R_Temp <<= 1;
		F_AD_Clock();
		if(IO_Data_AD)
		{
			R_Temp ++;
		}
	}	
	
	//----------------------------------
	//8:clk46
	//----------------------------------	
	F_AD_Clock();		

	return R_Temp;
}

/*-----------------------------------------------------------------------------
Name	: F_Wr_AdReg
Function: write ADC register
-----------------------------------------------------------------------------*/
void	F_Wr_AdReg(unsigned char R_AdReg)
{	
	unsigned char i;
	unsigned char R_Temp;

	while(IO_Data_AD);
	//----------------------------------
	//1 ~ 3:clk1-clk27
	//----------------------------------	
	for(i = 0; i < 27; i++)
	{
		F_AD_Clock();
	}

	//----------------------------------
	//4:clk28-clk29
	//----------------------------------
	spi_data_output();					//set MCU_Data output
	F_AD_Clock();	
	F_AD_Clock();

	//----------------------------------
	//5:clk30-clk36(send write command)
	//----------------------------------		
	R_Temp = 0xCA;					//write command (0x65); left move 1 bit
	for(i = 0; i < 7; i ++)
	{
		if(R_Temp&0x80)				//MSB
		{
			spi_dat_1;
		}
		else
		{
			spi_dat_0;
		}
		R_Temp = R_Temp << 1;
		F_AD_Clock();
	}

	//----------------------------------
	//6:clk37
	//----------------------------------
	F_AD_Clock();	
	
	//----------------------------------
	//7:clk38-clk45(write to register)
	//----------------------------------
	R_Temp = R_AdReg;	
	for(i = 0; i < 8; i ++)
	{
		if(R_Temp&0x80)				//MSB
		{
			spi_dat_1;
		}
		else
		{
			spi_dat_0; 
		}
		R_Temp = R_Temp << 1;
		F_AD_Clock();
	}
	
	//----------------------------------
	//8:clk46
	//----------------------------------	
	spi_data_input();					//set MCU_Data input
	F_AD_Clock();
}

