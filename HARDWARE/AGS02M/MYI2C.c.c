//****************************************************************//
//ģ��IIC���ó���
//ע�⣺ADS02MA��IIC��ͨѶƵ�ʲ��ó���30KHZ
// ��˾��    ���ɵ���
//****************************************************************//
#include "MYI2C.h"

MYI2C_Struct SENx;

/*******************************************************************************
* Function Name  : MYI2C_GPIO_Config
* Description    : ����IO������
* Input          : TYP ����IO����Ҫ���õ�����
* Output         : None
* Return         : None
*******************************************************************************/
void MYI2C_GPIO_Config(unsigned char TYP)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   	
	 if(TYP==SDA_OUT_1)
	 {
		 GPIO_InitStructure.GPIO_Pin = MYI2C_SDA_Pin;
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		 GPIO_Init(MYI2C_SDA_PORT, &GPIO_InitStructure);
   }
	 if(TYP==SDA_OUT_1)
	 { 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_InitStructure.GPIO_Pin = MYI2C_SDA_Pin;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(MYI2C_SDA_PORT, &GPIO_InitStructure);
   }
	 if(TYP==SCL_OUT_1)
	 {
			GPIO_InitStructure.GPIO_Pin = MYI2C_SCK_Pin;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(MYI2C_SCK_PORT, &GPIO_InitStructure);
   }
}
/**********************************************
//IIC Delay
**********************************************/
void  MYI2C_Delay(unsigned int nTim)
{
 for(;nTim>0;nTim--);
}
/**********************************************
//IIC Start
**********************************************/
void MYI2C_IIC_Start(void)
{
	MYI2C_SCK_Set();
	MYI2C_SDA_Set();
	MYI2C_SDA_Clr();
	MYI2C_SCK_Clr();
}
/**********************************************
//IIC Stop
**********************************************/
void MYI2C_IIC_Stop(void)
{
//unsigned char i=0;
	MYI2C_SCK_Clr();
	MYI2C_SDA_Clr();
	MYI2C_SCK_Set();
	MYI2C_SDA_Set();	
}
/**********************************************
//IIC Ack
**********************************************/
void MYI2C_IIC_Ack(unsigned char ack)
{
	MYI2C_SCK_Clr();
	if(ack)
	{
		MYI2C_SDA_Clr();
	}	
	else
	{
		MYI2C_SDA_Set();
	}
	MYI2C_SCK_Set();	
}
/**********************************************
//IIC Wait_Ack
**********************************************/
unsigned char MYI2C_IIC_Wait_Ack(unsigned char wait_time)
{
	MYI2C_SCK_Clr();
	MYI2C_SDA_IN_Mode;
	MYI2C_SDA_Set();
	MYI2C_SCK_Set();
	while(Read_MYI2C_SDA && wait_time)wait_time--;//
	MYI2C_SDA_OD_Mode;
	return wait_time;
}
/**********************************************
// IIC Write byte
**********************************************/
void MYI2C_Write_IIC_Byte(unsigned char dat)
{
unsigned char i;
		
	for(i=0;i<8;i++)		
	{
		MYI2C_SCK_Clr();
		if(dat&0x80)
		{
			MYI2C_SDA_Set();
		}	
		else 
    {
		  MYI2C_SDA_Clr();
		}			
		MYI2C_SCK_Set();
		dat=dat<<1;
	}	
}
/**********************************************
// IIC Read byte
**********************************************/
unsigned char MYI2C_Read_IIC_Byte(void)
{
unsigned char i,dat=0;
	
	MYI2C_SCK_Clr();
	MYI2C_SDA_IN_Mode;
	MYI2C_SDA_Set();	
	for(i=0;i<8;i++)		
	{
		MYI2C_SCK_Clr();	
		if(Read_MYI2C_SDA)dat++;	
		if(i<7)dat=dat<<1;
    MYI2C_SCK_Set();	
	}	
	MYI2C_SDA_OD_Mode;
	return dat;
}

 /*******************************************************************************
* Function Name  : 	MYI2C_Init
* Description    : 	��ʼ��I2C������ASG02MA�ṹ�����
* Input          :  ReadTim ÿ��msʱ���ȡAGS02MAģ��
                    xAddr 	AGS02MAģ��ͨѶ��ַ
* Output         : 	None
* Return         :	None
*******************************************************************************/
void  MYI2C_Init(MYI2C_Struct *pSENSOR,unsigned int ReadTim,unsigned char xAddr)
{	
	  pSENSOR->Adrr=xAddr;
	  pSENSOR->RegAddr=0x11;////�ϵ���汾
	  if(ReadTim<1500)ReadTim=1500;
		pSENSOR->SetRTim=ReadTim;
	  MYI2C_SCK_OD_Mode;
		MYI2C_SDA_OD_Mode;	
	  MYI2C_SCK_Set();
	  MYI2C_SDA_Set();		 
}
 /*******************************************************************************
* Function Name  : 	MYI2C_READ_FUNC
* Description    : 	IIC������ȡ�ӻ�����
* Input          : 	pSENSOR��Ŷ�������
										device_addr�ӻ���ַ
										register_addr�Ĵ�����ַ
										len�������ݵĳ���  ��λ��byte
* Output         : 	None
* Return         :	0����ȡ���ݳɹ�
										1����ȡ����ʧ��
*******************************************************************************/
unsigned char MYI2C_READ_FUNC(MYI2C_Struct *pSENSOR,unsigned char device_addr,signed char register_addr, unsigned char len)
{
unsigned int TimeOut=9999;
unsigned char i=0;
	if(register_addr>=0)
	{
		/* Send STRAT condition a second time */  
		MYI2C_IIC_Start();	
		/* Send slave address for Write Regsiter */
		MYI2C_Write_IIC_Byte( (device_addr<<1) + 0);
		/* ack */
		if(MYI2C_IIC_Wait_Ack(255)==0)TimeOut=0; 
		 /* Send register_addr   */
		MYI2C_Write_IIC_Byte( (register_addr));
		/* Test on EV6 and clear it */
		if(MYI2C_IIC_Wait_Ack(255)==0)TimeOut=0;

   MYI2C_IIC_Stop();
   MYI2C_Delay(9999);		
	}	
  /* Send STRAT condition a second time */  
	MYI2C_IIC_Start();	
  /* Send slave address for Read */
  MYI2C_Write_IIC_Byte( (device_addr<<1)+1 );
  /* ack */
	if(MYI2C_IIC_Wait_Ack(255)==0)TimeOut=0;
  /* While there is data to be read */
  while(i<len&&TimeOut ) //
  {
		TimeOut--;
		pSENSOR->ReadByte[i]=MYI2C_Read_IIC_Byte();
		/*  Acknowledgement */
		MYI2C_IIC_Ack(len-1-i);//len = 1 NoAck       
		i++;           
  }
		/* Send STOP Condition */
		MYI2C_IIC_Stop();
//	I2C_ClearFlag(pSENSOR->pPORT,I2C_FLAG_TIMEOUT);
 
if(TimeOut){pSENSOR->ErrFlag=0;return 0;}
else {pSENSOR->ErrFlag++;return 1;}

}
 /*******************************************************************************
* Function Name  : 	MYI2C_WRITE_FUNC
* Description    : 	IIC������ӻ�д������
* Input          : 	pSENSOR������Ҫ���͸��ӻ�������
										device_addr�ӻ���ַ
										register_addr�Ĵ�����ַ
										len�������ݵĳ���  ��λ��byte
* Return         :	0����ȡ���ݳɹ�
										1����ȡ����ʧ��
*******************************************************************************/
unsigned char MYI2C_WRITE_FUNC(MYI2C_Struct *pSENSOR,unsigned char device_addr,unsigned char register_addr, unsigned char *pDATA, unsigned char len)
{
unsigned int TimeOut=9999;	

  /* Send STRAT condition */
	MYI2C_IIC_Start();
  /* Send EEPROM address for write */
  MYI2C_Write_IIC_Byte( (device_addr<<1) + 0);
  /* Test on EV6 and clear it */
	if(MYI2C_IIC_Wait_Ack(255)==0)TimeOut=0;
   /* Send register_addr for read */
  MYI2C_Write_IIC_Byte( (register_addr));
  /* Test on EV6 and clear it */
	if(MYI2C_IIC_Wait_Ack(255)==0)TimeOut=0;  	
  while(TimeOut &&len)//
  {
		/* Send the byte to be written */
		MYI2C_Write_IIC_Byte( *pDATA);
		/*  Acknowledgement */
		MYI2C_IIC_Wait_Ack(9);		
		pDATA++;
		len--;
		TimeOut--;		
  }
  /* Send STOP condition */
   MYI2C_IIC_Stop();
	
if(TimeOut){pSENSOR->ErrFlag=0;return 0;}
else {pSENSOR->ErrFlag++;return 1;}
}
 /*******************************************************************************
* Function Name  : 	CheckCrc
* Description    :  CRCУ��
* Input          :  *pDAT��Ҫ����CRCУ�������
										Lenth����CRCУ������ݳ���  ��λ��byte
* Output         : 	None
* Return         :	CRCУ����
*******************************************************************************/
unsigned char  CheckCrc8(unsigned char *pDAT,unsigned char Lenth)
{
unsigned char crc = 0xff, i, j;

    for (i = 0; i < Lenth ; i++)
    {
        crc = crc ^ *pDAT;
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x80) crc = (crc << 1) ^ 0x31;
            else crc <<= 1;
        }
                pDAT++;
    }
    return crc;
} 

 /*******************************************************************************
* Function Name  :  MYI2C_Handle
* Description    :  ��ȡAGS02MA�İ汾���������TVOC����
* Input          :  *pSENSOR�����AGS02MAͨѶ���������
* Output         : 	None
* Return         :	None
*******************************************************************************/
 void  MYI2C_Handle(MYI2C_Struct *pSENSOR)
{
	 pSENSOR->timcnt+=MYI2C_Tick;
	if(pSENSOR->timcnt > pSENSOR->SetRTim)
	{
		pSENSOR->timcnt=0;
		MYI2C_READ_FUNC(pSENSOR,pSENSOR->Adrr,pSENSOR->RegAddr,5);	
		pSENSOR->ReadByte[5]=CheckCrc8(&pSENSOR->ReadByte[0],4);
		if(pSENSOR->ReadByte[5]==pSENSOR->ReadByte[4])
		{
			  if(pSENSOR->RegAddr==0x00)
				{
					pSENSOR->RegAddr=0x00;
					pSENSOR->Status=pSENSOR->ReadByte[0];
					pSENSOR->PPBVal=pSENSOR->ReadByte[1];//TVOC  ppb��ֵ
					pSENSOR->PPBVal=pSENSOR->PPBVal<<8;
					pSENSOR->PPBVal+=pSENSOR->ReadByte[2];
					pSENSOR->PPBVal=pSENSOR->PPBVal<<8;
					pSENSOR->PPBVal+=pSENSOR->ReadByte[3];
				}
			  else if(pSENSOR->RegAddr==0x11)
				{
					pSENSOR->RegAddr=0x00;
					pSENSOR->year=pSENSOR->ReadByte[0];
					pSENSOR->month=pSENSOR->ReadByte[1];
					pSENSOR->day=pSENSOR->ReadByte[2];
					pSENSOR->SoftVer=pSENSOR->ReadByte[3];	//�汾��
					pSENSOR->ReadByte[3]=0;
				}				
		}
	}
}

