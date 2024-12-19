//#include "myiic.h"
//#include "delay.h"
//#include "uart.h"
#include "funct.h"
 
//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7); 	
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	SDA_OUT(); 	    
	IIC_SCL=0;//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{              
		if((txd&0x80)>>7)
		{
			IIC_SDA=1;
		}
		else
		{
			IIC_SDA=0;
		}
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
	}	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
	{
		IIC_SCL=0; 
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)receive++;   
		delay_us(1); 
  }					 
	if (!ack)
	{
		IIC_NAck();//发送nACK
	}
	else
	{
		IIC_Ack(); //发送ACK 
	}		
	return receive;
}
//读写初始化
void AHT10_Init(void)
{
	IIC_Start();
	IIC_Send_Byte(0x70);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xE1);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x08);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(40);
}
//初始化
void SHT_Init(void)
{
	IIC_Init();
	
#if AHT10_ENABLE
	
	delay_ms(40);
	AHT10_Init();
	
#endif
//	AHT10_REST();
//	delay_ms(40);
}



/**
校验
*/
u8 AHT10Check(void)
{
	u8 ack=0;
	IIC_Start();
	IIC_Send_Byte(0X70);
	ack=IIC_Wait_Ack();
	IIC_Stop();	
	return ack;
}
//复位
void AHT10_REST(void)
{
	IIC_Start();
	IIC_Send_Byte(0x70);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xBA);
	IIC_Wait_Ack();
	IIC_Stop();
}


//读取温湿度
float temp_aht10;
u8 humi_aht10; 
u8 AHT10ReadData(void) 
{
	u8 ack;
	u32 SRH=0,ST=0;
	u8 databuff[6];
	IIC_Start();
	IIC_Send_Byte(0X70);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xac);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x33);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Stop();	  
	delay_ms(80);//??????????
	IIC_Start();
	IIC_Send_Byte(0X71);
	IIC_Wait_Ack();
	ack=IIC_Read_Byte(1);
	if((ack&0x40)==0)
	{
		databuff[0]=IIC_Read_Byte(1);
		databuff[1]=IIC_Read_Byte(1);
		databuff[2]=IIC_Read_Byte(1);
		databuff[3]=IIC_Read_Byte(1);
		databuff[4]=IIC_Read_Byte(0);
		IIC_Stop();
		SRH=(databuff[0]<<12)+(databuff[1]<<4)+(databuff[2]>>4);
		ST=((databuff[2]&0X0f)<<16)+(databuff[3]<<8)+(databuff[4]);
		humi_aht10=(u8)(int)(SRH*100.0/1024/1024+0.5);
		POINT_IN.hum=humi_aht10;
		CJ_SYS.humity=humi_aht10*10;
		temp_aht10=(float)((int)(ST*2000.0/1024/1024+0.5))/10.0-50;
		if(temp_aht10>=0)
		{
			CJ_SYS.temp=(u16)(temp_aht10*10);
		}
		else
		{
			CJ_SYS.temp=(u16)abs(temp_aht10*10)+0x8000;
		}
		return 0;
	}
	IIC_Stop();	
	return 1;
	
	
	
}

/////////////////////////////////////////////



























