#include "funct.h"
#include <stdio.h>  

struct _USARTSS USART_01;
struct _USARTS USART_02;
struct _USARTSS USART_03;
struct _USARTS USART_04;
struct _USARTS USART_05;
/* CRC高位字节值表*/ 
const u8 CRCByteHi[] = { 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
		0x00, 0xC1, 0x81, 0x40 
} ; 
/* CRC低位字节值表*/ 
const u8 CRCByteLo[] = { 
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,  
		0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 
		0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 
		0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 
		0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 
		0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 
		0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 
		0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 
		0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 
		0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 
		0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 
		0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 
		0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 
		0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 
		0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 
		0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 
		0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 
		0x41, 0x81, 0x80, 0x40 
} ;
/*
*******************************************************************************
**函    数:CRCCheck
**功    能:计算CRC的值
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u16 CRCCheck(u8 *puchMsg, u16 usDataLen)  
{ 
	u8 uCRCByteHi = 0xFF ; /* 高CRC字节初始化 */ 
	u8 uCRCByteLo = 0xFF ; /* 低CRC字节初始化 */ 
	u32 uIndex ; 
	while (usDataLen--) 
	{ 
		uIndex = uCRCByteHi ^ (*puchMsg++) ;  
		uCRCByteHi = uCRCByteLo ^ CRCByteHi[uIndex] ; 
		uCRCByteLo = CRCByteLo[uIndex] ; 
	} 
	return (uCRCByteHi << 8 | uCRCByteLo) ; 
}
/*
*******************************************************************************
**函    数:Get_CRC16
**功    能:计算CRC的值
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u16 Get_CRC16(u8 *pchMsg,u16 wDataLen) 
{
 	u8 chCRCH=0xFF,chCRCL=0xFF; 
 	u16 wIndex;  
 	while (wDataLen--) 
	{
		wIndex=chCRCL^*pchMsg++;   
		chCRCL=chCRCH^CRCByteHi[wIndex]; 
		chCRCH=CRCByteLo[wIndex];  
	}  
 	return ((chCRCH<<8)|chCRCL);  
}
/*
*******************************************************************************
**函    数:ADDCheck
**功    能:计算数组校验和的值
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u8 ADDCheck(u8 *data,u8 Length)
{
    u8 Result,i;
    Result = 0;
    for(i=0;i<Length;i++)
    {
        Result = Result + data[i];
    }                             
    return Result;
} 

/*
*******************************************************************************
**函    数:USART1_Configuration
**功    能:串口1的初始化
**参    数:u32 bound为串口的波特率
**返 回 值:无
**创建日期:
**修改记录:
**说    明:用于程序的下载口
*******************************************************************************
*/
void USART1_Configuration(u32 bound)
{ 
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	  USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10


		 //USART 初始化设置
		USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

		USART_Init(USART1, &USART_InitStructure); //初始化串口
 
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断

    USART_Cmd(USART1, ENABLE);                    //使能串口 
}
/*
*******************************************************************************
**函    数:USART2_Configuration
**功    能:串口2的初始化
**参    数:u32 bound为串口的波特率
**返 回 值:无
**创建日期:
**修改记录:
**说    明:用于蓝牙通信模块
*******************************************************************************
*/
void USART2_Configuration(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  //使能或失能APB2外设时钟--时钟配置
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  //使能GPIOA时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);   //使能USART2
	  	  USART_DeInit(USART2);  //复位串口2
	  //USART1_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  //Usart2 NVIC 配置  嵌套向量中断控制器
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       //usart2全局中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
		
		//USART 初始化设置
	  USART_InitStructure.USART_BaudRate = bound;                                    //一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
	
    USART_Init(USART2, &USART_InitStructure);     //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART2, ENABLE);                    //使能串口 
}
/*
*******************************************************************************
**函    数:USART3_Configuration
**功    能:串口3的初始化
**参    数:u32 bound为串口的波特率
**返 回 值:无
**创建日期:
**修改记录:
**说    明:用于485通信模块
*******************************************************************************
*/
void USART3_Configuration(u32 bound)
{
	  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  //使能或失能APB2外设时钟--时钟配置
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  //GPIOB时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);   //使能USART3
		 	  USART_DeInit(USART3);  //复位串口3
		//USART1_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART1_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//Usart3 NVIC 配置  嵌套向量中断控制器
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;       //usart3全局中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //抢占优先级2
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  //子优先级0
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
		
		//USART 初始化设置
	  USART_InitStructure.USART_BaudRate = bound;                                    //一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
	
    USART_Init(USART3, &USART_InitStructure);     //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART3, ENABLE);                    //使能串口 
	
}
/*
*******************************************************************************
**函    数:USART4_Configuration
**功    能:串口4的初始化
**参    数:u32 bound为串口的波特率
**返 回 值:无
**创建日期:
**修改记录:
**说    明:用于485通信模块,用于与无线进行通信和信息的配置
*******************************************************************************
*/
void USART4_Configuration(u32 bound)
{
	  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  //使能或失能APB2外设时钟--时钟配置
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  //GPIOC时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 ,ENABLE);   //使能USART4
		 	  USART_DeInit(UART4);  //复位串口3
		//USART1_TX   PC.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //PC.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
   
    //USART1_RX	  PC.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		//Usart4 NVIC 配置  嵌套向量中断控制器
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //usart4全局中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级2
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //子优先级0
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
		
		//USART 初始化设置
	  USART_InitStructure.USART_BaudRate = bound;                                    //一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
	
    USART_Init(UART4, &USART_InitStructure);     //初始化串口
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(UART4, ENABLE);                    //使能串口 
	
}

/*
*******************************************************************************
**函    数:USART5_Configuration
**功    能:串口5的初始化
**参    数:u32 bound为串口的波特率
**返 回 值:无
**创建日期:
**修改记录:
**说    明:用于485通信模块,蓝牙模块
*******************************************************************************
*/
void USART5_Configuration(u32 bound)
{
	  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  //使能或失能APB2外设时钟--时钟配置
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  //GPIOC时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	  //GPIOD时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 ,ENABLE);   //使能USART5
	
		USART_DeInit(UART5);  //复位串口5
		//USART5_TX   PC.12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //PC.12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);
   
    //USART5_RX	  PD.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		//Usart5 NVIC 配置  嵌套向量中断控制器
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;        //usart4全局中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级2
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //子优先级0
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器
		
		//USART 初始化设置
	  USART_InitStructure.USART_BaudRate = bound;                                    //一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
	
    USART_Init(UART5, &USART_InitStructure);     //初始化串口
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(UART5, ENABLE);                    //使能串口 
	
}

/*
*******************************************************************************
**函    数:fputc 串口添加函数 
**功    能:可以调用printf
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
#if 1
#pragma import(__use_no_semihosting)                          
struct __FILE 
{
    int handle; 
 
};
 
FILE __stdout;         
_sys_exit(int x) 
{
    x = x; 
}

int fputc(int ch, FILE *f)
{      
    while( !(USART1->SR & (1 << 7)) );
    USART_SendData(USART1,(uint8_t)ch); 
    return ch;
}
#endif 
//ui
void u1_printf(char* fmt,...)
{  
	u16 i,j; 
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_01.USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_01.USART_TX_BUF);		//此次发送数据的长度
//	COM1_EN=1;
//	delay_ms(1);
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART1,USART_01.USART_TX_BUF[j]); 
	} 
//	delay_ms(1);
//	COM1_EN=0;
}
//printf2
void u2_printf(char* fmt,...)
{  
	u16 i,j; 
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_02.USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_02.USART_TX_BUF);		//此次发送数据的长度
//	COM2_EN=1;
	delay_ms(1);
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART_02.USART_TX_BUF[j]); 
	} 
	delay_ms(1);
//	COM2_EN=0;
}
//printf3
void u3_printf(char* fmt,...)
{  
	u16 i,j; 
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_03.USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_03.USART_TX_BUF);		//此次发送数据的长度
	COM3_EN=1;
	delay_ms(1);
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART_03.USART_TX_BUF[j]); 
	} 
	delay_ms(1);
	COM3_EN=0;
}
//printf4
void u4_printf(char* fmt,...)
{  
	u16 i,j; 
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_04.USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_04.USART_TX_BUF);		//此次发送数据的长度
//	COM4_EN=1;
	delay_ms(1);
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(UART4,USART_04.USART_TX_BUF[j]); 
	} 
	delay_ms(1);
//	COM4_EN=0;
}
//printf5
void u5_printf(char* fmt,...)
{  
	u16 i,j; 
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_05.USART_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_05.USART_TX_BUF);		//此次发送数据的长度
	COM5_EN=1;
	delay_ms(1);
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(UART5,USART_05.USART_TX_BUF[j]); 
	}
  delay_ms(1);
	COM5_EN=0;	
}

//串口1发送字符串
void Uart1SendBuffer(u8 *pSource, u8 nLength)
 {
//	 COM1_EN=1;
//	delay_ms(1);
	while (nLength > 0)
	{
    USART_SendData(USART1,*pSource);

		pSource ++;

		nLength --;

		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}
	}
//	delay_ms(1);
//	COM1_EN=0;	
 }
 //串口2发送字符串
void Uart2SendBuffer(u8 *pSource, u8 nLength)
 {
	while (nLength > 0)
	{
    USART_SendData(USART2,*pSource);

		pSource ++;

		nLength --;

		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}
	}
 }
 //串口3发送字符串
 void Uart3SendBuffer(u8 *pSource, u8 nLength)
 {
	 COM3_EN=1;
		delay_ms(1);
		while (nLength > 0)
		{
			USART_SendData(USART3,*pSource);

			pSource ++;

			nLength --;

			while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}
		}
		delay_ms(1);
		COM3_EN=0;
 }
 //串口4发送字符串
void Uart4SendBuffer(u8 *pSource, u8 nLength)
 {
//	 COM4_EN=1;
	delay_ms(1);
	while (nLength > 0)
	{
    USART_SendData(UART4,*pSource);

		pSource ++;

		nLength --;

		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}
	}
	delay_ms(1);
//	COM4_EN=0;
 }
  //串口5发送字符串
void Uart5SendBuffer(u8 *pSource, u8 nLength)
 {
	 COM5_EN=1;
	delay_ms(1);
	while (nLength > 0)
	{
    USART_SendData(UART5,*pSource);

		pSource ++;

		nLength --;

		while(USART_GetFlagStatus(UART5,USART_FLAG_TXE) == RESET){}
	}
	delay_ms(1);
	COM5_EN=0;	
 }
/*
*******************************************************************************
**函    数:USART1_IRQHandler
**功    能:串口1的中断处理函数
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:光通无线模块的通信的接收中断
*******************************************************************************
*/
u8 start_rec_time_out=0;
void USART1_IRQHandler(void) //串口1中断服务程序
{
	u8 Res,i;
	if((USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)&&(USART_01.start_rec_flag==1))  //接收中断
	{  
		IWDG_Feed();
		 Res = USART_ReceiveData(USART1);	                  //读取接收到的数据
		 USART_01.usart_time_count=0;                       //复位间隔时间
		
		if(USART_01.USART_RX_STA>(REC_LEN_MAX-1))           //接收数据超长时重新开始数据接收	
		{
			//数据标志位复位
			USART_01.USART_RX_STA=0;
			for(i=0;i<REC_LEN_MAX;i++)
			{
				USART_01.USART_RX_BUF[i]=0;
			}
			USART_01.start_rec_flag=1;
			start_rec_time_out=0;
	    USART_01.begin_flag=0;
		}		
		
		USART_01.USART_RX_BUF[USART_01.USART_RX_STA]=Res ;
		USART_01.USART_RX_STA++;	
		USART_01.begin_flag=1;
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	
}

/*
*******************************************************************************
**函    数:USART2_IRQHandler
**功    能:串口2的中断处理函数
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:光通无线模块的通信的接收中断
*******************************************************************************
*/
void USART2_IRQHandler(void) //串口2中断服务程序
{
	u8 Res,i;
	if((USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)&&(USART_02.start_rec_flag==1))  //接收中断
	{  
		 Res = USART_ReceiveData(USART2);	  //读取接收到的数据
		 USART_02.usart_time_count=0;                       //复位间隔时间
		
		if(USART_02.USART_RX_STA>(REC_LEN_MAX-1))           //接收数据超长时重新开始数据接收	
		{
			//数据标志位复位
			USART_02.USART_RX_STA=0;
			for(i=0;i<REC_LEN_MAX;i++)
			{
				USART_02.USART_RX_BUF[i]=0;
			}
			USART_02.start_rec_flag=1;
	    USART_02.begin_flag=0;
		}		
		
		USART_02.USART_RX_BUF[USART_02.USART_RX_STA]=Res ;
		USART_02.USART_RX_STA++;	
		USART_02.begin_flag=1;
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
}

/*
*******************************************************************************
**函    数:USART3_IRQHandler
**功    能:串口3的中断处理函数
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:485通信的接收中断,主要是与外部的智能电表进行通信
*******************************************************************************
*/
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 Res,i;
	if((USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)&&(USART_03.start_rec_flag==1))  //接收中断
	{  	
		IWDG_Feed();
		 Res = USART_ReceiveData(USART3);	//读取接收到的数据
		 USART_03.usart_time_count=0;                //记录每一帧的通信时间长度
		
		if(USART_03.USART_RX_STA>(REC_LEN_MAX-1)) //接收数据错误,重新开始接收	
		{
			//数据标志位复位
			USART_03.USART_RX_STA=0;
			for(i=0;i<REC_LEN_MAX;i++)
			{
				USART_03.USART_RX_BUF[i]=0;
			}
			USART_03.start_rec_flag=1;
	    USART_03.begin_flag=0;
		}		
		USART_03.USART_RX_BUF[USART_03.USART_RX_STA]=Res ;
		USART_03.USART_RX_STA++;	
		USART_03.begin_flag=1;
			 
   } //接收到中断  END
	 USART_ClearITPendingBit(USART3, USART_IT_RXNE);
} 

/*
*******************************************************************************
**函    数:USART4_IRQHandler
**功    能:串口4的中断处理函数
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:485通信的接收中断,主要与配置信息和无线模块进行通信
*******************************************************************************
*/
void UART4_IRQHandler(void)                	//串口4中断服务程序
{
	u8 Res,i;
	if((USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)&&(USART_04.start_rec_flag==1))  //接收中断
	{  	
		 Res = USART_ReceiveData(UART4);	//读取接收到的数据
		 USART_04.usart_time_count=0;                //记录每一帧的通信时间长度
		
		if(USART_04.USART_RX_STA>(REC_LEN_MAX-1)) //接收数据错误,重新开始接收	
		{
			//数据标志位复位
			USART_04.USART_RX_STA=0;
			for(i=0;i<REC_LEN_MAX;i++)
			{
				USART_04.USART_RX_BUF[i]=0;
			}
			USART_04.start_rec_flag=1;
	    USART_04.begin_flag=0;
		}		
		USART_04.USART_RX_BUF[USART_04.USART_RX_STA]=Res ;
		USART_04.USART_RX_STA++;	
		USART_04.begin_flag=1;
			 
   } //接收到中断  END
	 USART_ClearITPendingBit(UART4, USART_IT_RXNE);
} 
/*
*******************************************************************************
**函    数:USART5_IRQHandler
**功    能:串口5的中断处理函数
**参    数:无
**返 回 值:无
**创建日期:
**修改记录:
**说    明:485通信的接收中断,主要与配置信息和无线模块进行通信
*******************************************************************************
*/
void UART5_IRQHandler(void)                	//串口4中断服务程序
{
	u8 Res,i;
	if((USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)&&(USART_05.start_rec_flag==1))  //接收中断
	{  	
		 Res = USART_ReceiveData(UART5);	//读取接收到的数据
		 USART_05.usart_time_count=0;                //记录每一帧的通信时间长度
		
		if(USART_05.USART_RX_STA>(REC_LEN_MAX-1)) //接收数据错误,重新开始接收	
		{
			//数据标志位复位
			USART_05.USART_RX_STA=0;
			for(i=0;i<REC_LEN_MAX;i++)
			{
				USART_05.USART_RX_BUF[i]=0;
			}
			USART_05.start_rec_flag=1;
	    USART_05.begin_flag=0;
		}		
		USART_05.USART_RX_BUF[USART_05.USART_RX_STA]=Res ;
		USART_05.USART_RX_STA++;	
		USART_05.begin_flag=1;
			 
   } //接收到中断  END
	 USART_ClearITPendingBit(UART5, USART_IT_RXNE);
} 


/*
*******************************************************************************
**函    数:usart1_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u8 send_back_1[6]={0x68,0xA0,0x01,0xFF,0x09,0x16};
u8 send_back_4[9]={0x68,0xA1,0x02,0x00,0x00,0x00,0x00,0x09,0x16};
u8 send_back_6[11]={0x68,0xA1,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x16};
u8 wei[3]={0};
u8 rec_data[6]={0};
u32 rec_data_count=0;
u8 cs_time_count=0;
void usart1_rec(void)
{
	u8 count=0;
	u16 year=0;
	u8 data_wz=0;
	u8 month,day,hour,min,sec;
	if(USART_01.start_rec_flag==0)
	{
		rec_data_count++;
		if(int_send_time>=300)
		{
		   int_send_time=300;
		}
		/*-----接收数据的处理-----*/
		if(USART_01.USART_RX_STA<=2)
		{ //AT   OK
			if((USART_01.USART_RX_BUF[0]==0x41)&&(USART_01.USART_RX_BUF[1]==0x54))
			{
				u1_printf("OK\r\n");  //测试
			}
			
		}
		else if(USART_01.USART_RX_BUF[0]==0x68&&USART_01.USART_RX_BUF[USART_01.USART_RX_STA-1]==0x16)
		{
			STATU_SYS.wifi_time=0;
			data_wz=findElement(USART_01.USART_RX_BUF,USART_01.USART_RX_STA,0x68) ;
			//如果目标地址为自己
			if((USART_01.USART_RX_BUF[2]==0x0C)&&(data_wz==0))//目标地址为本机地址的全部接收
			{
				//状态的上传
				if(USART_01.USART_RX_BUF[3]==0xA0)
				{
					Upload_sysstatu1(USART_01.USART_RX_BUF[1],0xA0);
					
				}
				//姿态数据
				else if(USART_01.USART_RX_BUF[3]==0xA1)
				{
					Upload_sysstatu2(USART_01.USART_RX_BUF[1],0xA1);
					
				}
				//加速度数据
				else if(USART_01.USART_RX_BUF[3]==0xA3)
				{
					Upload_sysstatu3(USART_01.USART_RX_BUF[1],0xA3);
					
				}
				//角速度数据
				else if(USART_01.USART_RX_BUF[3]==0xA4)
				{
					Upload_sysstatu4(USART_01.USART_RX_BUF[1],0xA4);
					
				}
				//磁场数据
				else if(USART_01.USART_RX_BUF[3]==0xA5)
				{
					Upload_sysstatu5(USART_01.USART_RX_BUF[1],0xA5);
					
				}
				//四元素数据
				else if(USART_01.USART_RX_BUF[3]==0xA6)
				{
					Upload_sysstatu6(USART_01.USART_RX_BUF[1],0xA6);
					
				}
				//软件版本
				else if(USART_01.USART_RX_BUF[3]==0xA7)
				{
					Upload_sysstatut(USART_01.USART_RX_BUF[1],0xA7,time_set.board_id);
					
				}
				//声纳数据
				else if(USART_01.USART_RX_BUF[3]==0xA2)
				{
					//Upload_sysstatu2(0xA2);
					
				}
				//时间数据
				else if(USART_01.USART_RX_BUF[3]==0xAF)
				{
					//Upload_sysstatu2(0xA2);
					Upload_sysstatu_time(USART_01.USART_RX_BUF[1],0xAF);
				}
				//控制运动
        else if(USART_01.USART_RX_BUF[3]==0xB0)
				{
 			    STATU_SYS.run_mode=USART_01.USART_RX_BUF[5];
					STATU_SYS.sys_speed=USART_01.USART_RX_BUF[6];
					STATU_SYS.sys_speed2=USART_01.USART_RX_BUF[7];
					//开启电机使能
					if(STATU_SYS.run_mode>0)
					{
						Set_addr_l(2,6,40,1);
						delay_ms(50);
						Set_addr_r(3,6,40,1);
					}
					//返回确认数据
					Send_back(USART_01.USART_RX_BUF[1],0xB0);
					//伺服控制直接写入控制器相关的指令
					if(STATU_SYS.run_mode==2)//后退
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						
					}
					else if(STATU_SYS.run_mode==9)//差速后退
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed2);
					}
					else if(STATU_SYS.run_mode==1)//前进
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==8)//前进差速
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed2);
					}
					else if(STATU_SYS.run_mode==3)//左转
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==4)//右转
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==5)//单步左转
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						cs_time_count=0;
//		        IWDG_Feed(); 
//						delay_ms(1000);
//						IWDG_Feed(); 
//						Set_addr_l(2,06,40,0);
//						delay_ms(10);
//						Set_addr_r(3,06,40,0);
//						STATU_SYS.run_mode=0;
//						STATU_SYS.sys_speed=0;
						
					}
					else if(STATU_SYS.run_mode==6)//单步右转
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						cs_time_count=0;
//						IWDG_Feed(); 
//						delay_ms(1000);
//						IWDG_Feed(); 
//						Set_addr_l(2,06,40,0);
//						delay_ms(10);
//						Set_addr_r(3,06,40,0);
//						STATU_SYS.run_mode=0;
//						STATU_SYS.sys_speed=0;
					}
					else if(STATU_SYS.run_mode==0)//停止
					{
						//关闭使能 20231214
//						Set_addr_l(2,06,40,0);
//						delay_ms(100);
//						Set_addr_r(3,06,40,0);
//						delay_ms(100);
						//速度设置为0
						Set_addr_l(2,06,174,0);
						delay_ms(10);
						Set_addr_r(3,06,174,0);
					}
				}
				//电磁铁操作
				else if(USART_01.USART_RX_BUF[3]==0xB1)
				{
					if(USART_01.USART_RX_BUF[5]==1)
					{
					   RELAY1_EN=1;
						 RELAY2_EN=1;
					   STATU_SYS.M_relay1_flag=1;
						STATU_SYS.M_relay2_flag=1;
					}
					else
					{
						RELAY1_EN=0;
						 RELAY2_EN=0;
					   STATU_SYS.M_relay1_flag=0;
						STATU_SYS.M_relay2_flag=0;
					}
					Send_back(USART_01.USART_RX_BUF[1],0xB1);
				}
				//点刹车操作
				else if(USART_01.USART_RX_BUF[3]==0xB2)
				{
					if(USART_01.USART_RX_BUF[5]<=1)
					{
					  STATU_SYS.zl_control_enable=USART_01.USART_RX_BUF[5];
					}
					
					Send_back(USART_01.USART_RX_BUF[1],0xB2);
				}
				//配置参数亮度
				else if(USART_01.USART_RX_BUF[3]==0xC0)
				{
					STATU_SYS.other_led_pwm=USART_01.USART_RX_BUF[7];
					STATU_SYS.back_led_pwm=USART_01.USART_RX_BUF[6];
					STATU_SYS.front_led_pwm=USART_01.USART_RX_BUF[5];
					Send_back(USART_01.USART_RX_BUF[1],0xC0);
				}
				//配置水压校准值
				else if(USART_01.USART_RX_BUF[3]==0xC1)
				{
					if(USART_01.USART_RX_BUF[5]<=100)
					{
					  STATU_SYS.fy_set_add=USART_01.USART_RX_BUF[5];
						AT24CXX_Write(EE_FY_SET_ADD, &(STATU_SYS.fy_set_add), 1);
						Send_back(USART_01.USART_RX_BUF[1],0xC1);
					}
	
				}
				//发送电机复位指令
				else if(USART_01.USART_RX_BUF[3]==0xC2)
				{
					IWDG_Feed();
					//CAN
					test_num[0]=0x86;
			    test_num[1]=0x00;
			    test_num[2]=0x00;
			    test_num[3]=0x00;
					//复位指令
			    Can_Send_Msg(test_num,4,0x202);
					delay_ms(100);
			    Can_Send_Msg(test_num,4,0x203);
					delay_ms(500);
					//返回
					Send_back(USART_01.USART_RX_BUF[1],0xC2);
					IWDG_Feed();
					test_num[0]=0x01;
					test_num[1]=0x00;
					test_num[2]=0x00;
					test_num[3]=0x00;
					Can_Send_Msg(test_num,4,0x0000);//进入OP模式
					IWDG_Feed();
					delay_ms(300);
					//握手指令 232
					Set_addr_l(2,6,40,0);
					delay_ms(300);
					Set_addr_r(3,6,40,0);
					IWDG_Feed();
					//接收复位指令后重置运动状态
					STATU_SYS.run_mode=0;
				}
				//发送张力传感器复位指令
				else if(USART_01.USART_RX_BUF[3]==0xC3)
				{
					Reset_ZF_Num();
					//返回
					Send_back(USART_01.USART_RX_BUF[1],0xC3);
				}
				
			}
			else if((USART_01.USART_RX_BUF[data_wz+2]==0x0C)&&(data_wz>0))//连帧的处理
			{
				delay_ms(100);
				//状态的上传
				if(USART_01.USART_RX_BUF[data_wz+3]==0xA0)
				{
					Upload_sysstatu1(USART_01.USART_RX_BUF[data_wz+1],0xA0);
					
				}
				//姿态数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA1)
				{
					Upload_sysstatu2(USART_01.USART_RX_BUF[data_wz+1],0xA1);
					
				}
				//加速度数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA3)
				{
					Upload_sysstatu3(USART_01.USART_RX_BUF[data_wz+1],0xA3);
					
				}
				//角速度数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA4)
				{
					Upload_sysstatu4(USART_01.USART_RX_BUF[data_wz+1],0xA4);
					
				}
				//磁场数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA5)
				{
					Upload_sysstatu5(USART_01.USART_RX_BUF[data_wz+1],0xA5);
					
				}
				//四元素数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA6)
				{
					Upload_sysstatu6(USART_01.USART_RX_BUF[data_wz+1],0xA6);
					
				}
				//声纳数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xA2)
				{
					//Upload_sysstatu2(0xA2);
					
				}
				//时间数据
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xAF)
				{
					//Upload_sysstatu2(0xA2);
					Upload_sysstatu_time(USART_01.USART_RX_BUF[data_wz+1],0xAF);
				}
				//控制运动
        else if(USART_01.USART_RX_BUF[data_wz+3]==0xB0)
				{
 			    STATU_SYS.run_mode=USART_01.USART_RX_BUF[data_wz+5];
					STATU_SYS.sys_speed=USART_01.USART_RX_BUF[data_wz+6];
					STATU_SYS.sys_speed2=USART_01.USART_RX_BUF[data_wz+7];
					//开启电机使能
					if(STATU_SYS.run_mode>0)
					{
						Set_addr_l(2,6,40,1);
						delay_ms(50);
						Set_addr_r(3,6,40,1);
					}
					//返回确认数据
					Send_back(USART_01.USART_RX_BUF[data_wz+1],0xB0);
					//伺服控制直接写入控制器相关的指令
					if(STATU_SYS.run_mode==2)//后退
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						
					}
					else if(STATU_SYS.run_mode==9)//差速后退
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed2);
					}
					else if(STATU_SYS.run_mode==1)//前进
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==8)//前进差速
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed2);
					}
					else if(STATU_SYS.run_mode==3)//左转
					{
						Set_addr_l(2,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==4)//右转
					{
						Set_addr_l(2,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
						delay_ms(10);
						Set_addr_r(3,06,174,-speed_zy*(u16)STATU_SYS.sys_speed);
					}
					else if(STATU_SYS.run_mode==0)//停止
					{
//						Set_addr_l(2,06,40,0);
//						delay_ms(100);
//						Set_addr_r(3,06,40,0);
//						delay_ms(100);
						//速度设置为0
						Set_addr_l(2,06,174,0);
						delay_ms(10);
						Set_addr_r(3,06,174,0);
					}
				}
				//电磁铁操作
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xB1)
				{
					if(USART_01.USART_RX_BUF[data_wz+5]==1)
					{
					   RELAY1_EN=1;
						 RELAY2_EN=1;
					   STATU_SYS.M_relay1_flag=1;
						 STATU_SYS.M_relay2_flag=1;
					}
					else
					{
						 RELAY1_EN=0;
						 RELAY2_EN=0;
					   STATU_SYS.M_relay1_flag=0;
						 STATU_SYS.M_relay2_flag=0;
					}
					Send_back(USART_01.USART_RX_BUF[data_wz+1],0xB1);
				}
				//配置参数亮度
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xC0)
				{
					STATU_SYS.other_led_pwm=USART_01.USART_RX_BUF[data_wz+7];
					STATU_SYS.back_led_pwm=USART_01.USART_RX_BUF[data_wz+6];
					STATU_SYS.front_led_pwm=USART_01.USART_RX_BUF[data_wz+5];
					Send_back(USART_01.USART_RX_BUF[data_wz+1],0xC0);
				}
				//配置水压校准值
				else if(USART_01.USART_RX_BUF[data_wz+3]==0xC1)
				{
					if(USART_01.USART_RX_BUF[data_wz+5]<=100)
					{
					  STATU_SYS.fy_set_add=USART_01.USART_RX_BUF[data_wz+5];
						AT24CXX_Write(EE_FY_SET_ADD, &(STATU_SYS.fy_set_add), 1);
						Send_back(USART_01.USART_RX_BUF[data_wz+1],0xC1);
					}
	
				}
				
				
			}
			//如果为广播报文
			else if((USART_01.USART_RX_BUF[1]==0x00)&&(USART_01.USART_RX_BUF[2]==0xFF))
			{		
				//校准时间
				if(USART_01.USART_RX_BUF[3]==0xB0)
				{
					 year=USART_01.USART_RX_BUF[5]+2000;
					 month=USART_01.USART_RX_BUF[6];
					 day=USART_01.USART_RX_BUF[7];
					 hour=USART_01.USART_RX_BUF[8];
					 min=USART_01.USART_RX_BUF[9];
					 sec=USART_01.USART_RX_BUF[10];
//					 RTC_Set(year,month,day,hour,min,sec);
				}
				
				
			}
			
			
		}
		//声纳数据
		else if(USART_01.USART_RX_BUF[0]==0xFE&&USART_01.USART_RX_BUF[USART_01.USART_RX_STA-1]==0xFD)
		{
			//直接转发
			Uart3SendBuffer(USART_01.USART_RX_BUF,USART_01.USART_RX_STA);
			
		}
		//A~~~@
		else if(USART_01.USART_RX_BUF[0]==0x41&&USART_01.USART_RX_BUF[USART_01.USART_RX_STA-1]==0x40)
		{
			
		}
		/*-----数据的判断和任务的添加--------*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_01.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_01.USART_RX_STA=0;             		 	//标志位复位	
		USART_01.usart_time_count=0;
		USART_01.start_rec_flag=1;     		 	      //重新开始接收	
		start_rec_time_out=0;
		/*-----------end---------------------*/
	
   }
 }
/*
*******************************************************************************
**函    数:usart2_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
 MOTEC驱动器常用地址（十进制）
 11：地址 
 12：波特率 
 40：使能 
 199：使能状态 
 174：速度设定 
 52：故障复位 
 200：故障码 
 162：实际电流
 175：实际转速 
 195：驱动器温度 
 160：伺服状态
 //加速度
	u8 ax_h;
	u8 ax_l;
	
	u8 ay_h;
	u8 ay_l;
	
	u8 az_h;
	u8 az_l;
	
	//角速度
	u8 wx_h;
	u8 wx_l;
	
	u8 wy_h;
	u8 wy_l;
	
	u8 wz_h;
	u8 wz_l;
	
	//磁场
	u8 hx_h;
	u8 hx_l;
	
	u8 hy_h;
	u8 hy_l;
	
	u8 hz_h;
	u8 hz_l;
	
	//四元素
	u8 q0_h;
	u8 q0_l;
	
	u8 q1_h;
	u8 q1_l;
	
	u8 q2_h;
	u8 q2_l;
	
	u8 q3_h;
	u8 q3_l;
	
*******************************************************************************
*/
u8 PM25[2]={0};
u8 PM10[2]={0};
void usart2_rec(void)
{
	u8 count=0;
	if(USART_02.start_rec_flag==0)
	{
		/*-----接收数据的处理-----*/
		if(USART_02.USART_RX_STA<=2)
		{ //AT   OK
			if((USART_02.USART_RX_BUF[0]==0x41)&&(USART_02.USART_RX_BUF[1]==0x54))
			{
				u2_printf("OK\r\n");  //测试
			}
			
		}
		//温湿度
		else if(USART_02.USART_RX_BUF[0]==0x0C&&USART_02.USART_RX_BUF[1]==0x03)
		{		
			STATU_SYS.humity_h=((u16)USART_02.USART_RX_BUF[3]<<8)+USART_02.USART_RX_BUF[4];
			STATU_SYS.temp_h=((u16)USART_02.USART_RX_BUF[5]<<8)+USART_02.USART_RX_BUF[6];
			
		}
		//姿态采集
		else if((USART_02.USART_RX_BUF[0]==0x50)&&(USART_02.USART_RX_BUF[1]==0x03))
		{
			if(ask_flag==2)
			{
				STATU_SYS.roll_h=USART_02.USART_RX_BUF[3];
				STATU_SYS.roll_l=USART_02.USART_RX_BUF[4];
				
				STATU_SYS.pitch_h=USART_02.USART_RX_BUF[5];
				STATU_SYS.pitch_l=USART_02.USART_RX_BUF[6];
				
				STATU_SYS.yaw_h=USART_02.USART_RX_BUF[7];
				STATU_SYS.yaw_l=USART_02.USART_RX_BUF[8];
				//姿态角计算
				STATU_SYS.roll=(((short)STATU_SYS.roll_h<<8)|STATU_SYS.roll_l);//*180/32768;
				if(STATU_SYS.roll>=0)
				{
					STATU_SYS.roll=STATU_SYS.roll/182;
				}
				else
				{
					STATU_SYS.roll=-(abs(STATU_SYS.roll)/182);
				}
				STATU_SYS.pitch=(((short)STATU_SYS.pitch_h<<8)|STATU_SYS.pitch_l);//*180/32768;
				if(STATU_SYS.pitch>=0)
				{
					STATU_SYS.pitch=STATU_SYS.pitch/182;
				}
				else
				{
					STATU_SYS.pitch=-(abs(STATU_SYS.pitch)/182);
				}
				
				STATU_SYS.yaw=(((short)STATU_SYS.yaw_h<<8)|STATU_SYS.yaw_l);//*180/32768/182;
				if(STATU_SYS.yaw>=0)
				{
					STATU_SYS.yaw=STATU_SYS.yaw/182;
				}
				else
				{
					STATU_SYS.yaw=-(abs(STATU_SYS.yaw)/182);
				}
		  }
			else if(ask_flag==3)
			{
				STATU_SYS.ax_h=USART_02.USART_RX_BUF[3];
				STATU_SYS.ax_l=USART_02.USART_RX_BUF[4];
				
				STATU_SYS.ay_h=USART_02.USART_RX_BUF[5];
				STATU_SYS.ay_l=USART_02.USART_RX_BUF[6];
				
				STATU_SYS.az_h=USART_02.USART_RX_BUF[7];
				STATU_SYS.az_l=USART_02.USART_RX_BUF[8];
			}
			else if(ask_flag==4)
			{
				STATU_SYS.wx_h=USART_02.USART_RX_BUF[3];
				STATU_SYS.wx_l=USART_02.USART_RX_BUF[4];
				
				STATU_SYS.wy_h=USART_02.USART_RX_BUF[5];
				STATU_SYS.wy_l=USART_02.USART_RX_BUF[6];
				
				STATU_SYS.wz_h=USART_02.USART_RX_BUF[7];
				STATU_SYS.wz_l=USART_02.USART_RX_BUF[8];
			}
			else if(ask_flag==5)
			{
				STATU_SYS.hx_h=USART_02.USART_RX_BUF[3];
				STATU_SYS.hx_l=USART_02.USART_RX_BUF[4];
				
				STATU_SYS.hy_h=USART_02.USART_RX_BUF[5];
				STATU_SYS.hy_l=USART_02.USART_RX_BUF[6];
				
				STATU_SYS.hz_h=USART_02.USART_RX_BUF[7];
				STATU_SYS.hz_l=USART_02.USART_RX_BUF[8];
				
				STATU_SYS.hh_h=USART_02.USART_RX_BUF[9];
				STATU_SYS.hh_l=USART_02.USART_RX_BUF[10];
			}
			else if(ask_flag==6)
			{
				STATU_SYS.q0_h=USART_02.USART_RX_BUF[3];
				STATU_SYS.q0_l=USART_02.USART_RX_BUF[4];
				
				STATU_SYS.q1_h=USART_02.USART_RX_BUF[5];
				STATU_SYS.q1_l=USART_02.USART_RX_BUF[6];
				
				STATU_SYS.q2_h=USART_02.USART_RX_BUF[7];
				STATU_SYS.q2_l=USART_02.USART_RX_BUF[8];
				
				STATU_SYS.q3_h=USART_02.USART_RX_BUF[9];
				STATU_SYS.q3_l=USART_02.USART_RX_BUF[10];
			}
		}
		//pm2.5
		else if(USART_02.USART_RX_BUF[0]==0x42&&USART_02.USART_RX_BUF[1]==0x4d)
		{
			PM25[0]=USART_02.USART_RX_BUF[6];
			PM25[1]=USART_02.USART_RX_BUF[7];
			PM10[0]=USART_02.USART_RX_BUF[8];
			PM10[1]=USART_02.USART_RX_BUF[9];
			
			POINT_IN.pm25=((u16)USART_02.USART_RX_BUF[6]<<8)+USART_02.USART_RX_BUF[7];
			POINT_IN.pm100=((u16)USART_02.USART_RX_BUF[8]<<8)+USART_02.USART_RX_BUF[9];
			
		} 
		//臭氧
		else if(USART_02.USART_RX_BUF[0]==0xFF)
		{
			if(USART_02.USART_RX_BUF[1]==0x2A)
			{
			   POINT_IN.O3O=((u16)USART_02.USART_RX_BUF[4]<<8)+USART_02.USART_RX_BUF[5];
			}
		}
		//环境采集板
		else if(USART_02.USART_RX_BUF[0]==0x3C&&USART_02.USART_RX_BUF[1]==0x02)
		{
			 CJ_SYS.co2_num=((u16)USART_02.USART_RX_BUF[2]<<8)+USART_02.USART_RX_BUF[3];
			
			CJ_SYS.ch20_num=((u16)USART_02.USART_RX_BUF[4]<<8)+USART_02.USART_RX_BUF[5];
			
			CJ_SYS.tvoc_num=((u16)USART_02.USART_RX_BUF[6]<<8)+USART_02.USART_RX_BUF[7];
			
			CJ_SYS.pm2_5_num=((u16)USART_02.USART_RX_BUF[8]<<8)+USART_02.USART_RX_BUF[9];
			
			CJ_SYS.pm10_num=((u16)USART_02.USART_RX_BUF[10]<<8)+USART_02.USART_RX_BUF[11];
			

		}
		/*-----数据的判断和任务的添加--------*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_02.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_02.USART_RX_STA=0;             		 	//标志位复位	
		USART_02.usart_time_count=0;
		USART_02.start_rec_flag=1;     		 	      //重新开始接收	
		/*-----------end---------------------*/
	
   }
}
/*
*******************************************************************************
**函    数:usart3_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/

u8 CO2[2]={0};
u8 HCHO[2]={0};
u8 TVOC[2]={0};
u16 tvoc_up_count=0;
u16 test_co2=0;
void usart3_rec(void)
{
	u8 count;
	if(USART_03.start_rec_flag==0)
	{
		if(USART_03.USART_RX_STA<=2)
		{ //AT   OK
			if((USART_03.USART_RX_BUF[0]==0x41)&&(USART_03.USART_RX_BUF[1]==0x54))
			{
				u3_printf("OK\r\n");  //测试
			}
			
		}
		else if(USART_03.USART_RX_BUF[0]==0x42&&USART_03.USART_RX_BUF[1]==0x4d)
		{
			 POINT_IN.co2=((u16)USART_03.USART_RX_BUF[9]<<8)+USART_03.USART_RX_BUF[10];
			test_co2=POINT_IN.co2;
			 //CO2[1]=USART_03.USART_RX_BUF[10];
			POINT_IN.tvoc=((u16)USART_03.USART_RX_BUF[11]<<8)+USART_03.USART_RX_BUF[12];
			//TVOC[1]=USART_03.USART_RX_BUF[12];
			POINT_IN.ch2o=((u16)USART_03.USART_RX_BUF[13]<<8)+USART_03.USART_RX_BUF[14];
			//HCHO[1]=USART_03.USART_RX_BUF[14];
			
			
			
			CO2[0]=(u8)(POINT_IN.co2>>8);
			CO2[1]=(u8)(POINT_IN.co2);
			
			TVOC[0]=(u8)(POINT_IN.tvoc>>8);
			TVOC[1]=(u8)(POINT_IN.tvoc);
			
			HCHO[1]=(u8)(POINT_IN.ch2o>>8);
			HCHO[1]=(u8)(POINT_IN.ch2o);
			
		}
		else if(USART_03.USART_RX_BUF[0]==0xFF)
		{
			if(USART_03.USART_RX_BUF[1]==0x2A)
			{
			   POINT_IN.O3O=((u16)USART_03.USART_RX_BUF[4]<<8)+USART_03.USART_RX_BUF[5];
			}
			else if(USART_03.USART_RX_BUF[1]==0x17)
			{
				POINT_IN.ch2o=((u16)USART_03.USART_RX_BUF[4]<<8)+USART_03.USART_RX_BUF[5];
				HCHO[1]=(u8)(POINT_IN.ch2o>>8);
			  HCHO[1]=(u8)(POINT_IN.ch2o);
			}
		}
		/*-----数据的判断和任务的添加--------*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_03.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_03.USART_RX_STA=0;             		 	//标志位复位	
		USART_03.usart_time_count=0;
		USART_03.start_rec_flag=1;     		 	      //重新开始接收	
		/*-----------end---------------------*/
	
   }
}

/*
*******************************************************************************
**函    数:usart4_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u16 o3o_ss=0;
u8 SetE32Com[6] = {0xC0,0x00,0x00,0x1A,0x17,0x44};
u8 ReadE32ParCom[3] = {0xC1, 0xC1,0xC1};
struct _point POINT_IN ;
void usart4_rec(void)
{
	u8 count=0;
//	u16 o3o_mid=0;
	if(USART_04.start_rec_flag==0)
	{
		//Uart3SendBuffer(USART_04.USART_RX_BUF,USART_04.USART_RX_STA);
		//u3_printf("\r\n");
		if(USART_04.USART_RX_STA<=2)
		{ //AT   OK
			if((USART_04.USART_RX_BUF[0]==0x41)&&(USART_04.USART_RX_BUF[1]==0x54))
			{
				u4_printf("OK\r\n");  //测试
			}
			
		}
		else if(USART_04.USART_RX_BUF[0]==0xc0)
		{
			//保存无线模块的参数信息
			POINT_IN.point_address=(USART_04.USART_RX_BUF[1]<<8)+USART_04.USART_RX_BUF[2];
			POINT_IN.point_speed=USART_04.USART_RX_BUF[3];
			POINT_IN.point_chan=USART_04.USART_RX_BUF[4];
			POINT_IN.point_option=USART_04.USART_RX_BUF[5];			
			
		}
		else if(strstr((const char*)USART_04.USART_RX_BUF,"test")!= NULL)
		{
			while(AUX_P);
			//u4_printf("SYS/03d%/03d%/03d%/03d%/\r\n",);  //测试发送数据
			Upload_lora_sysstatu(0xA0);
		}
		
		
		/*数据的判断和任务的添加----------end*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_04.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_04.start_rec_flag=1;     		 	      //重新开始接收	
		USART_04.USART_RX_STA=0;             		 	//标志位复位	
		USART_04.usart_time_count=0;
	}
}
/*
*******************************************************************************
**函    数:usart5_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
void usart5_rec(void)
{
	u8 count=0;
//	u16 o3o_mid=0;
	if(USART_05.start_rec_flag==0)
	{
		
		if(USART_05.USART_RX_STA<=2)
		{ //AT   OK
			if((USART_05.USART_RX_BUF[0]==0x41)&&(USART_05.USART_RX_BUF[1]==0x54))
			{
				u5_printf("OK\r\n");  //测试
			}
			
		}
		
		/*数据的判断和任务的添加----------end*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_05.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_05.start_rec_flag=1;     		 	      //重新开始接收	
		USART_05.USART_RX_STA=0;             		 	//标志位复位	
		USART_05.usart_time_count=0;
	}
}
/*
*******************************************************************************
**函    数:usart1_send_back
**功    能:
**参    数:
**返 回 值:
**创建日期:
**修改记录:
**说    明:返回数据的发送
*******************************************************************************
*/
void usart1_send_back(void)
{
	u8 i;
//	printf("SET_TEMP: %d C\r\n",time_set.temp);
//	printf("%d\r\n",u2_count);
	//printf("\r\n");
	USART_01.USART_TX_BUF[0]=0x68;
	USART_01.USART_TX_BUF[1]=0xba;
	USART_01.USART_TX_BUF[2]=0x10;
	
	USART_01.USART_TX_BUF[3]=CO2[1];
	USART_01.USART_TX_BUF[4]=CO2[0];
	
	USART_01.USART_TX_BUF[5]=HCHO[1];
	USART_01.USART_TX_BUF[6]=HCHO[0];
	
	USART_01.USART_TX_BUF[7]=TVOC[1];
	USART_01.USART_TX_BUF[8]=TVOC[0];
	
	USART_01.USART_TX_BUF[9]=PM25[1];
	USART_01.USART_TX_BUF[10]=PM25[0];
	
	USART_01.USART_TX_BUF[11]=PM10[1];
	USART_01.USART_TX_BUF[12]=PM10[0];
	
	USART_01.USART_TX_BUF[13]=Temp[1];
	USART_01.USART_TX_BUF[14]=Temp[0];
	
	USART_01.USART_TX_BUF[15]=Humi[1];
	USART_01.USART_TX_BUF[16]=Humi[0];
	
	USART_01.USART_TX_BUF[17]=POINT_IN.O3O>>8;
	USART_01.USART_TX_BUF[18]=POINT_IN.O3O;

  USART_01.USART_TX_BUF[19]=0x0;
	USART_01.USART_TX_BUF[20]=0x16;

  for(i=0;i<=20;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_01.USART_TX_BUF[i]=0;
	}

	
}

/*
*******************************************************************************
**函    数:usart3_send_back
**功    能:
**参    数:
**返 回 值:
**创建日期:
**修改记录:
**说    明:返回数据的发送
*******************************************************************************
*/
void usart3_send_back(void)
{
	u8 i;
//	u8 ADD_num;
	//读取eeprom内部的值
	//AT24CXX_Read(0x00,confg_data,8);
	//USART_03.USART_TX_BUF[0]=0x09;
	USART_03.USART_TX_BUF[0]=0x42;
	USART_03.USART_TX_BUF[1]=0x86;
	USART_03.USART_TX_BUF[2]=0x04;
	USART_03.USART_TX_BUF[3]=0x00;
	USART_03.USART_TX_BUF[4]=0x00;
	USART_03.USART_TX_BUF[5]=0x00;
	USART_03.USART_TX_BUF[6]=0x00;
	USART_03.USART_TX_BUF[7]=0x00;
	USART_03.USART_TX_BUF[8]=0xff;
	
	for(i=0;i<=8;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//广播报文进行时间校准
void AutotimeUpload(void)
{

	u8 i;
	u8 add_sum;

	USART_04.USART_TX_BUF[0]=0x68;
	
	USART_04.USART_TX_BUF[1]=0x00;
	
	USART_04.USART_TX_BUF[2]=0xFF;
	
	USART_04.USART_TX_BUF[3]=0xB0;
	
	USART_04.USART_TX_BUF[4]=0x06;
	
	USART_04.USART_TX_BUF[5]=(calendar.w_year-2000);//年
	USART_04.USART_TX_BUF[6]=calendar.w_month;//月
	USART_04.USART_TX_BUF[7]=calendar.w_date;//日
	USART_04.USART_TX_BUF[8]=calendar.hour;//时
	USART_04.USART_TX_BUF[9]=calendar.min;//分
	USART_04.USART_TX_BUF[10]=calendar.sec;//秒
	
	add_sum=ADDCheck(USART_04.USART_TX_BUF,11);
	
	USART_04.USART_TX_BUF[11]=add_sum;
	USART_04.USART_TX_BUF[12]=0x16;//结束
	
//	COM4_EN=1;
	delay_ms(1);
	for(i=0;i<=12;i++)
	{
		USART_SendData(UART4,USART_04.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
//	COM4_EN=0;
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_04.USART_TX_BUF[i]=0;
	}
}
//获取温湿度
void Get_temphum(u8 addr)
{

	u8 i;

	USART_02.USART_TX_BUF[0]=addr;
	
	USART_02.USART_TX_BUF[1]=0x03;
	
	USART_02.USART_TX_BUF[2]=0x00;
	
	USART_02.USART_TX_BUF[3]=0x00;
	
	USART_02.USART_TX_BUF[4]=0x00;
	
	USART_02.USART_TX_BUF[5]=0x02;
	
	USART_02.USART_TX_BUF[6]=CRCCheck(USART_02.USART_TX_BUF,6)>>8;
	
	USART_02.USART_TX_BUF[7]=CRCCheck(USART_02.USART_TX_BUF,6);
	
//	COM2_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_02.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
//	COM2_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_02.USART_TX_BUF[i]=0;
	}
}
//获取姿态数据
void Get_XYZ_statu(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x3d;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x03;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//获取加速度数据
void Get_add_statu(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x34;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x03;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//获取角速度数据
void Get_ang_statu(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x37;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x03;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//获取磁场数据
void Get_ccc_statu(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x3a;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x04;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//获取四元素数据
void Get_sys_statu(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x51;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x04;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//获取张力数据
void Get_ZF_Num(u8 addr)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=0x03;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x00;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x02;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//复位张力数据
void Reset_ZF_Num(void)
{

	u8 i;

	USART_03.USART_TX_BUF[0]=0x20;
	
	USART_03.USART_TX_BUF[1]=0x06;
	
	USART_03.USART_TX_BUF[2]=0x00;
	
	USART_03.USART_TX_BUF[3]=0x02;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=0x01;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//从机控制指令的下发
u16 send_ask_num=0;       //用于轮询状态的查询
void Control_node(u8 address,u8 funum,u8 code)
{
	u8 i;
	u8 add_sum;
	
	USART_04.USART_TX_BUF[0]=0x68;
	USART_04.USART_TX_BUF[1]=time_set.board_id;
	USART_04.USART_TX_BUF[2]=address;
	USART_04.USART_TX_BUF[3]=funum;
	USART_04.USART_TX_BUF[4]=0x01;
	USART_04.USART_TX_BUF[5]=code;
	
	add_sum=ADDCheck(USART_04.USART_TX_BUF,6);
	
	USART_04.USART_TX_BUF[6]=add_sum;
	USART_04.USART_TX_BUF[7]=0x16;
	
//	COM4_EN=1;
	delay_ms(1);
	
	for(i=0;i<=7;i++)
	{
		USART_SendData(UART4,USART_04.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	
	delay_ms(1);
//	COM4_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_04.USART_TX_BUF[i]=0;
	}
}
//分区域控制
void FQ_Control_node(u8 address,u8 funum,u8 code1,u8 code2)
{
	u8 i;
	u8 add_sum;
	
	USART_04.USART_TX_BUF[0]=0x68;
	USART_04.USART_TX_BUF[1]=time_set.board_id;
	USART_04.USART_TX_BUF[2]=address;
	USART_04.USART_TX_BUF[3]=funum;
	USART_04.USART_TX_BUF[4]=0x02;
	USART_04.USART_TX_BUF[5]=code1;
	USART_04.USART_TX_BUF[6]=code2;
	
	add_sum=ADDCheck(USART_04.USART_TX_BUF,7);
	
	USART_04.USART_TX_BUF[7]=add_sum;
	USART_04.USART_TX_BUF[8]=0x16;
	
//	COM4_EN=1;
	delay_ms(1);
	
	for(i=0;i<=8;i++)
	{
		USART_SendData(UART4,USART_04.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	
	delay_ms(1);
//	COM4_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_04.USART_TX_BUF[i]=0;
	}
}
//请求各从机的状态
u8 node_num=0;        //从机的数量
u8 node_address[20]={0};//从机的地址列表
u8 node_online_time[20]={0};//用于存储从机的超时时间长度 认为超时
u8 ask_ennable=0;     //轮询启动标志位
u8 ask_flag=0;  //数据发送标志位
void Send_ask(void)//com2
{
	if(ask_ennable==1)
	{
		//查询温湿度
//		if(send_ask_num%10==0)//8s/次
//		{
//			//0C 03 00 00 00 02 C5 16
//			//Get_temphum(TEMP_ADDR);
//			//ask_flag=1;
//		}
//		else if(send_ask_num%6==0)//角度数据
//		{
//			Get_XYZ_statu(ZTSYS_ADDR);
//			ask_flag=2;
//		}
//		else if(send_ask_num%6==1)//请求加速度数据
//		{
//			Get_add_statu(ZTSYS_ADDR);
//			ask_flag=3;
//		}
//		else if(send_ask_num%6==2)//请求角速度数据
//		{
//			Get_ang_statu(ZTSYS_ADDR);
//			ask_flag=4;
//		}
//		else if(send_ask_num%6==3)//请求磁场数据
//		{
//			Get_ccc_statu(ZTSYS_ADDR);
//			ask_flag=5;
//		}
//		else if(send_ask_num%6==4)//请求四元素数据
//		{
//			Get_sys_statu(ZTSYS_ADDR);
//			ask_flag=6;
//		}
		if(send_ask_num%2==0)//请求张力数据
		{
			Get_ZF_Num(ZF_ADDR);
			ask_flag=7;
		}
		
	}		
}
//姿态采集//com3
void Send_ask2(void)
{
	if(ask_ennable==1)
	{
		//查询姿态采集
		if(send_ask_num%2==0)
		{
			Get_XYZ_statu(0x50);
		}
	}		
}
//声纳测试
void Send_ask_test(void)
{
	u16 data;
	
	for(data=0;data<=900;data++)
	{
		USART_01.USART_TX_BUF[data]='a';
	}
	
	for(data=0;data<=900;data++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[data]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	
}
//模拟声纳数据
void Back_sn_test(void)
{
	u16 data;

	for(data=0;data<=199;data++)
	{
		USART_03.USART_TX_BUF[data]=0X01;
	}
	USART_03.USART_TX_BUF[0]=0X49;
	USART_03.USART_TX_BUF[199]=0XFC;
		COM3_EN=1;
	delay_ms(1);
	for(data=0;data<=199;data++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[data]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
}
//开启TVOC主动上传
void OpenAutomaticUpload_VOC(void)
{

	u8 i;
	//读取eeprom内部的值
	//AT24CXX_Read(0x00,confg_data,8);
	USART_05.USART_TX_BUF[0]=0x42;
	USART_05.USART_TX_BUF[1]=0x78;
	USART_05.USART_TX_BUF[2]=0x04;
	USART_05.USART_TX_BUF[3]=0x00;
	USART_05.USART_TX_BUF[4]=0x00;
	USART_05.USART_TX_BUF[5]=0x00;
	USART_05.USART_TX_BUF[6]=0x00;
	USART_05.USART_TX_BUF[7]=0x00;
	USART_05.USART_TX_BUF[8]=0xff;
	
	COM5_EN=1;
	delay_ms(1);
	
	for(i=0;i<=8;i++)
	{
		USART_SendData(UART5,USART_05.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART5,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM5_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_05.USART_TX_BUF[i]=0;
	}
}

//上传系统基本信息
void Upload_sysstatu1(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=41;
	
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.sys_speed;

	USART_01.USART_TX_BUF[6]=STATU_SYS.front_led_pwm;
	
	USART_01.USART_TX_BUF[7]=STATU_SYS.back_led_pwm;

	USART_01.USART_TX_BUF[8]=STATU_SYS.adc_fy>>8;
	
	USART_01.USART_TX_BUF[9]=STATU_SYS.adc_fy;

	USART_01.USART_TX_BUF[10]=STATU_SYS.adc_bat_vol>>8;
	
	USART_01.USART_TX_BUF[11]=STATU_SYS.adc_bat_vol;

	USART_01.USART_TX_BUF[12]=STATU_SYS.error_code;
	
	USART_01.USART_TX_BUF[13]=STATU_SYS.sys_statu;
	//CJ_SYS.temp
	USART_01.USART_TX_BUF[14]=CJ_SYS.temp>>8;
	
	USART_01.USART_TX_BUF[15]=CJ_SYS.temp;
	//CJ_SYS.humity
	USART_01.USART_TX_BUF[16]=CJ_SYS.humity>>8;
	
	USART_01.USART_TX_BUF[17]=CJ_SYS.humity;
	
	USART_01.USART_TX_BUF[18]=STATU_SYS.other_led_pwm;;
	
	if((STATU_SYS.run_mode==9)||(STATU_SYS.run_mode==8))
	{
	  USART_01.USART_TX_BUF[19]=STATU_SYS.sys_speed2;
	}
	else
	{
		USART_01.USART_TX_BUF[19]=STATU_SYS.sys_speed;
	}
	//20230816添加
	//right
	USART_01.USART_TX_BUF[20]=STATU_SYS.motor_r_current>>8;
	USART_01.USART_TX_BUF[21]=STATU_SYS.motor_r_current;
	
	USART_01.USART_TX_BUF[22]=STATU_SYS.motor_r_ture_speed>>8;
	USART_01.USART_TX_BUF[23]=STATU_SYS.motor_r_ture_speed;
	
	USART_01.USART_TX_BUF[24]=STATU_SYS.motor_r_diff_speed>>8;
	USART_01.USART_TX_BUF[25]=STATU_SYS.motor_r_diff_speed;
	
	USART_01.USART_TX_BUF[26]=STATU_SYS.motor_r_statu>>8;
	USART_01.USART_TX_BUF[27]=STATU_SYS.motor_r_statu;
	
	USART_01.USART_TX_BUF[28]=STATU_SYS.motor_r_error_code>>24;
	USART_01.USART_TX_BUF[29]=STATU_SYS.motor_r_error_code>>16;
	USART_01.USART_TX_BUF[30]=STATU_SYS.motor_r_error_code>>8;
	USART_01.USART_TX_BUF[31]=STATU_SYS.motor_r_error_code;
	//left
	USART_01.USART_TX_BUF[32]=STATU_SYS.motor_l_current>>8;
	USART_01.USART_TX_BUF[33]=STATU_SYS.motor_l_current;
	
	USART_01.USART_TX_BUF[34]=STATU_SYS.motor_l_ture_speed>>8;
	USART_01.USART_TX_BUF[35]=STATU_SYS.motor_l_ture_speed;
	
	USART_01.USART_TX_BUF[36]=STATU_SYS.motor_l_diff_speed>>8;
	USART_01.USART_TX_BUF[37]=STATU_SYS.motor_l_diff_speed;
	
	USART_01.USART_TX_BUF[38]=STATU_SYS.motor_l_statu>>8;
	USART_01.USART_TX_BUF[39]=STATU_SYS.motor_l_statu;
	
	USART_01.USART_TX_BUF[40]=STATU_SYS.motor_l_error_code>>24;
	USART_01.USART_TX_BUF[41]=STATU_SYS.motor_l_error_code>>16;
	USART_01.USART_TX_BUF[42]=STATU_SYS.motor_l_error_code>>8;
	USART_01.USART_TX_BUF[43]=STATU_SYS.motor_l_error_code;
	
	USART_01.USART_TX_BUF[44]=STATU_SYS.zf_num>>8;
	USART_01.USART_TX_BUF[45]=STATU_SYS.zf_num;
	
	USART_01.USART_TX_BUF[46]=STATU_SYS.sys_statu_show>>8;
	USART_01.USART_TX_BUF[47]=STATU_SYS.sys_statu_show;
	
	USART_01.USART_TX_BUF[48]=ADDCheck(USART_01.USART_TX_BUF,48);
	
	USART_01.USART_TX_BUF[49]=0x16;
	
//	COM1_EN=1;
//	delay_ms(1);
	for(i=0;i<=49;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
//	delay_ms(1);
//	COM1_EN=0;
}
//上传系统角度数据
void Upload_sysstatu2(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x06;
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.roll_h;

	USART_01.USART_TX_BUF[6]=STATU_SYS.roll_l;
	
		USART_01.USART_TX_BUF[7]=STATU_SYS.pitch_h;

	USART_01.USART_TX_BUF[8]=STATU_SYS.pitch_l;
	
		USART_01.USART_TX_BUF[9]=STATU_SYS.yaw_h;

	USART_01.USART_TX_BUF[10]=STATU_SYS.yaw_l;
	
	USART_01.USART_TX_BUF[11]=ADDCheck(USART_01.USART_TX_BUF,11);
	
	USART_01.USART_TX_BUF[12]=0x16;
	
	for(i=0;i<=12;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传系统加速度数据
void Upload_sysstatu3(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x06;
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.ax_h;

	USART_01.USART_TX_BUF[6]=STATU_SYS.ax_l;
	
	USART_01.USART_TX_BUF[7]=STATU_SYS.ay_h;

	USART_01.USART_TX_BUF[8]=STATU_SYS.ay_l;
	
	USART_01.USART_TX_BUF[9]=STATU_SYS.az_h;

	USART_01.USART_TX_BUF[10]=STATU_SYS.az_l;
	
	USART_01.USART_TX_BUF[11]=ADDCheck(USART_01.USART_TX_BUF,11);
	
	USART_01.USART_TX_BUF[12]=0x16;
	
	for(i=0;i<=12;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传系统角速度数据
void Upload_sysstatu4(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x06;
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.wx_h;

	USART_01.USART_TX_BUF[6]=STATU_SYS.wx_l;
	
	USART_01.USART_TX_BUF[7]=STATU_SYS.wy_h;

	USART_01.USART_TX_BUF[8]=STATU_SYS.wy_l;
	
	USART_01.USART_TX_BUF[9]=STATU_SYS.wz_h;

	USART_01.USART_TX_BUF[10]=STATU_SYS.wz_l;
	
	USART_01.USART_TX_BUF[11]=ADDCheck(USART_01.USART_TX_BUF,11);
	
	USART_01.USART_TX_BUF[12]=0x16;
	
	for(i=0;i<=12;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传系统磁场数据
void Upload_sysstatu5(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x08;
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.hx_h;

	USART_01.USART_TX_BUF[6]=STATU_SYS.hx_l;
	
	USART_01.USART_TX_BUF[7]=STATU_SYS.hy_h;

	USART_01.USART_TX_BUF[8]=STATU_SYS.hy_l;
	
	USART_01.USART_TX_BUF[9]=STATU_SYS.hz_h;

	USART_01.USART_TX_BUF[10]=STATU_SYS.hz_l;
	
	USART_01.USART_TX_BUF[11]=STATU_SYS.hh_h;

	USART_01.USART_TX_BUF[12]=STATU_SYS.hh_l;
	
	USART_01.USART_TX_BUF[13]=ADDCheck(USART_01.USART_TX_BUF,13);
	
	USART_01.USART_TX_BUF[14]=0x16;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传系统四元素数据
void Upload_sysstatu6(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x08;
	
	USART_01.USART_TX_BUF[5]=STATU_SYS.q0_h;

	USART_01.USART_TX_BUF[6]=STATU_SYS.q0_l;
	
	USART_01.USART_TX_BUF[7]=STATU_SYS.q1_h;

	USART_01.USART_TX_BUF[8]=STATU_SYS.q1_l;
	
	USART_01.USART_TX_BUF[9]=STATU_SYS.q2_h;

	USART_01.USART_TX_BUF[10]=STATU_SYS.q2_l;
	
	USART_01.USART_TX_BUF[11]=STATU_SYS.q3_h;

	USART_01.USART_TX_BUF[12]=STATU_SYS.q3_l;
	
	USART_01.USART_TX_BUF[13]=ADDCheck(USART_01.USART_TX_BUF,13);
	
	USART_01.USART_TX_BUF[14]=0x16;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传单个数据
void Upload_sysstatut(u8 addr,u8 cmd,u8 data)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x01;
	
	USART_01.USART_TX_BUF[5]=data;
	
	USART_01.USART_TX_BUF[6]=ADDCheck(USART_01.USART_TX_BUF,6);
	
	USART_01.USART_TX_BUF[7]=0x16;
	
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}
//上传系统时间数据
void Upload_sysstatu_time(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x06;
	
	USART_01.USART_TX_BUF[5]=calendar.w_year-2000;

	USART_01.USART_TX_BUF[6]=calendar.w_month;
	
	USART_01.USART_TX_BUF[7]=calendar.w_date;

	USART_01.USART_TX_BUF[8]=calendar.hour;
	
	USART_01.USART_TX_BUF[9]=calendar.min;

	USART_01.USART_TX_BUF[10]=calendar.sec;
	
	
	USART_01.USART_TX_BUF[11]=ADDCheck(USART_01.USART_TX_BUF,11);
	
	USART_01.USART_TX_BUF[12]=0x16;
	
	for(i=0;i<=12;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}

}

//返回确认信息
void Send_back(u8 addr,u8 cmd)
{
	u8 i=0;

	USART_01.USART_TX_BUF[0]=0x68;
	
	USART_01.USART_TX_BUF[1]=0x0C;
	
	USART_01.USART_TX_BUF[2]=addr;
	
	USART_01.USART_TX_BUF[3]=cmd;
	
	USART_01.USART_TX_BUF[4]=0x01;
	
	USART_01.USART_TX_BUF[5]=0xFF;

	
	USART_01.USART_TX_BUF[6]=ADDCheck(USART_01.USART_TX_BUF,6);
	
	USART_01.USART_TX_BUF[7]=0x16;
	
//	COM1_EN=1;
//	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART1,USART_01.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
//	delay_ms(1);
//	COM1_EN=0;
}

//modbus操作 0x03
void Read_addr(u8 addr,u8 cmd,u16 addr_begin,u8 num)
{
	u8 i;

	USART_02.USART_TX_BUF[0]=addr;
	
	USART_02.USART_TX_BUF[1]=cmd;
	
	USART_02.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_02.USART_TX_BUF[3]=addr_begin;
	
	USART_02.USART_TX_BUF[4]=0x00;
	
	USART_02.USART_TX_BUF[5]=num;
	
	USART_02.USART_TX_BUF[6]=CRCCheck(USART_02.USART_TX_BUF,6)>>8;
	
	USART_02.USART_TX_BUF[7]=CRCCheck(USART_02.USART_TX_BUF,6);
	
//	COM2_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_02.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
//	COM2_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_02.USART_TX_BUF[i]=0;
	}
}

//modbus设置  0x06  单个地址设置
void Set_addr(u8 addr,u8 cmd,u16 addr_begin,short data)
{
	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=cmd;
	
	USART_03.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_03.USART_TX_BUF[3]=addr_begin;
	
	USART_03.USART_TX_BUF[4]=data>>8;
	
	USART_03.USART_TX_BUF[5]=data;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}
//modbus设置  0x06  单个地址设置 左电机对应的串口
void Set_addr_l(u8 addr,u8 cmd,u16 addr_begin,short data)
{
	u8 i;

	USART_02.USART_TX_BUF[0]=addr;
	
	USART_02.USART_TX_BUF[1]=cmd;
	
	USART_02.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_02.USART_TX_BUF[3]=addr_begin;
	
	USART_02.USART_TX_BUF[4]=data>>8;
	
	USART_02.USART_TX_BUF[5]=data;
	
	USART_02.USART_TX_BUF[6]=CRCCheck(USART_02.USART_TX_BUF,6)>>8;
	
	USART_02.USART_TX_BUF[7]=CRCCheck(USART_02.USART_TX_BUF,6);
	
//	COM3_EN=1;
//	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_02.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
//	delay_ms(1);
//	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_02.USART_TX_BUF[i]=0;
	}
	//使能控制--CAN数据的发送
	if(addr_begin==40)
	{
		if(data==0)//关闭使能
		{
			test_num[0]=0x06;
			test_num[1]=0x00;
			test_num[2]=0x00;
			test_num[3]=0x00;
			Can_Send_Msg(test_num,4,0x202);
		}
		else if(data==1)//开启使能
		{
			test_num[0]=0x07;
			test_num[1]=0x00;
			test_num[2]=0x00;
			test_num[3]=0x00;
			Can_Send_Msg(test_num,4,0x202);
		}
	}
	//速度的控制
	else if(addr_begin==174)
	{
		test_num[0]=0x0f;
		test_num[1]=0x00;
		
		test_num[2]=data;
		test_num[3]=data>>8;
		Can_Send_Msg(test_num,4,0x202);
		
	}
}
//modbus设置  0x06  单个地址设置 右电机对应的串口
void Set_addr_r(u8 addr,u8 cmd,u16 addr_begin,short data)
{
	u8 i;

	USART_04.USART_TX_BUF[0]=addr;
	
	USART_04.USART_TX_BUF[1]=cmd;
	
	USART_04.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_04.USART_TX_BUF[3]=addr_begin;
	
	USART_04.USART_TX_BUF[4]=data>>8;
	
	USART_04.USART_TX_BUF[5]=data;
	
	USART_04.USART_TX_BUF[6]=CRCCheck(USART_04.USART_TX_BUF,6)>>8;
	
	USART_04.USART_TX_BUF[7]=CRCCheck(USART_04.USART_TX_BUF,6);
	
//	COM3_EN=1;
//	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(UART4,USART_04.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
//	delay_ms(1);
//	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_04.USART_TX_BUF[i]=0;
	}
	//使能控制--CAN数据的发送
	if(addr_begin==40)
	{
		if(data==0)//关闭使能
		{
			test_num[0]=0x06;
			test_num[1]=0x00;
			test_num[2]=0x00;
			test_num[3]=0x00;
			Can_Send_Msg(test_num,4,0x203);
		}
		else if(data==1)//开启使能
		{
			test_num[0]=0x07;
			test_num[1]=0x00;
			test_num[2]=0x00;
			test_num[3]=0x00;
			Can_Send_Msg(test_num,4,0x203);
		}
	}
	//速度的控制
	else if(addr_begin==174)
	{
		test_num[0]=0x0f;
		test_num[1]=0x00;
		
		test_num[2]=data;
		test_num[3]=data>>8;
		Can_Send_Msg(test_num,4,0x203);
		
	}
}

//modbus操作 0x03
void Read_addr_com3(u8 addr,u8 cmd,u16 addr_begin,u8 num)
{
	u8 i;

	USART_03.USART_TX_BUF[0]=addr;
	
	USART_03.USART_TX_BUF[1]=cmd;
	
	USART_03.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_03.USART_TX_BUF[3]=addr_begin;
	
	USART_03.USART_TX_BUF[4]=0x00;
	
	USART_03.USART_TX_BUF[5]=num;
	
	USART_03.USART_TX_BUF[6]=CRCCheck(USART_03.USART_TX_BUF,6)>>8;
	
	USART_03.USART_TX_BUF[7]=CRCCheck(USART_03.USART_TX_BUF,6);
	
	COM3_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
	COM3_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_03.USART_TX_BUF[i]=0;
	}
}

//modbus设置  0x06  单个地址设置
void Set_addr_com3(u8 addr,u8 cmd,u16 addr_begin,short data)
{
	u8 i;

	USART_02.USART_TX_BUF[0]=addr;
	
	USART_02.USART_TX_BUF[1]=cmd;
	
	USART_02.USART_TX_BUF[2]=addr_begin>>8;
	
	USART_02.USART_TX_BUF[3]=addr_begin;
	
	USART_02.USART_TX_BUF[4]=data>>8;
	
	USART_02.USART_TX_BUF[5]=data;
	
	USART_02.USART_TX_BUF[6]=CRCCheck(USART_02.USART_TX_BUF,6)>>8;
	
	USART_02.USART_TX_BUF[7]=CRCCheck(USART_02.USART_TX_BUF,6);
	
//	COM2_EN=1;
	delay_ms(1);
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_02.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	delay_ms(1);
//	COM2_EN=0;
	
	for(i=0;i<=USART_REC_LEN;i++)
	{
		USART_02.USART_TX_BUF[i]=0;
	}
}
//lora上传系统基本信息
void Upload_lora_sysstatu(u8 cmd)
{
	u8 i=0;

	USART_04.USART_TX_BUF[0]=0x68;
	
	USART_04.USART_TX_BUF[1]=0x0C;
	
	USART_04.USART_TX_BUF[2]=0X0B;
	
	USART_04.USART_TX_BUF[3]=cmd;
	
	USART_04.USART_TX_BUF[4]=0x0F;
	
	
	USART_04.USART_TX_BUF[5]=STATU_SYS.bat_vol;

	USART_04.USART_TX_BUF[6]=CJ_SYS.temp>>8;
	USART_04.USART_TX_BUF[7]=CJ_SYS.temp;
	
	USART_04.USART_TX_BUF[8]=CJ_SYS.humity>>8;
	USART_04.USART_TX_BUF[9]=CJ_SYS.humity;

	USART_04.USART_TX_BUF[10]=STATU_SYS.adc_fy>>8;
	USART_04.USART_TX_BUF[11]=STATU_SYS.adc_fy;
	
	USART_04.USART_TX_BUF[12]=STATU_SYS.roll>>8;
	USART_04.USART_TX_BUF[13]=STATU_SYS.roll;

	USART_04.USART_TX_BUF[14]=STATU_SYS.pitch>>8;
	USART_04.USART_TX_BUF[15]=STATU_SYS.pitch;
	
	if(STATU_SYS.run_mode>0)
	{
	USART_04.USART_TX_BUF[16]=STATU_SYS.sys_speed;
	}
	else
	{
		USART_04.USART_TX_BUF[16]=0;
	}
	
	USART_04.USART_TX_BUF[17]=STATU_SYS.distance>>8;
	USART_04.USART_TX_BUF[18]=STATU_SYS.distance;
	
	USART_04.USART_TX_BUF[19]=STATU_SYS.run_mode;
	
	USART_04.USART_TX_BUF[20]=ADDCheck(USART_04.USART_TX_BUF,20);
	
	USART_04.USART_TX_BUF[21]=0x16;
	
//	COM1_EN=1;
//	delay_ms(1);
	for(i=0;i<=21;i++)
	{
		USART_SendData(UART4,USART_04.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
//	delay_ms(1);
//	COM1_EN=0;
}

/******************* (C) COPYRIGHT 2012 RongYu Team *****************************/

