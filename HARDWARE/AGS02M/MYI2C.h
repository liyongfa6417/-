#ifndef _MYI2C_h_
#define _MYI2C_h_

#include "stm32f10x.h"

//#define I2C_P02P16
//#define I2C_CLOCK     0x02//max<1.4Mbps
#define MYI2C_Tick  10//MS

#define MYI2C_SCK_PORT	GPIOB  
#define MYI2C_SDA_PORT	GPIOB
#define MYI2C_SCK_Pin	  GPIO_Pin_6
#define MYI2C_SDA_Pin	  GPIO_Pin_7

#define MYI2C_SCK_OD_Mode   MYI2C_GPIO_Config(SCL_OUT_1);MYI2C_Delay(500)
#define MYI2C_SDA_OD_Mode   MYI2C_GPIO_Config(SDA_OUT_1);MYI2C_Delay(500)
#define MYI2C_SDA_IN_Mode   MYI2C_GPIO_Config(SDA_OUT_1);MYI2C_Delay(500)

#define MYI2C_SCK_Clr()  GPIO_ResetBits(MYI2C_SCK_PORT,MYI2C_SCK_Pin);MYI2C_Delay(110)
#define MYI2C_SCK_Set()  GPIO_SetBits(MYI2C_SCK_PORT,MYI2C_SCK_Pin);MYI2C_Delay(110)

#define MYI2C_SDA_Clr()  GPIO_ResetBits(MYI2C_SDA_PORT,MYI2C_SDA_Pin);MYI2C_Delay(110)
#define MYI2C_SDA_Set()	 GPIO_SetBits(MYI2C_SDA_PORT,MYI2C_SDA_Pin);MYI2C_Delay(110)

#define Read_MYI2C_SDA	GPIO_ReadInputDataBit(MYI2C_SDA_PORT ,MYI2C_SDA_Pin)


#define SDA_OUT_1  0
#define SDA_IN_1   1
#define SCL_OUT_1  2

#define SlaveAddr   0x38

//#define SENSOR_PORT_TYPE  unsigned char
typedef struct
{
// 	SENSOR_PORT_TYPE  *pPORT;
//	unsigned int  Speed;
	unsigned char   Adrr;		//通讯设备地址

	unsigned char   Status;	//AGS02MA模块状态字节
	unsigned short int  timcnt;	//时间计数器
	unsigned char   ErrFlag;	//通讯错误次数
	unsigned short int  SetRTim;	//设置读取间隔时间

	unsigned char  RegAddr;	//寄存器地址
	unsigned char  ReadByte[10];  //存放读取的数据
	unsigned int RSVal;  //传感器阻值
	unsigned int PPBVal;	//TVOC  ppb数值
	unsigned char  year;	//年
	unsigned char  month;//月
	unsigned char  day;		//日
	unsigned char  SoftVer;	//版本号

}MYI2C_Struct;

extern  MYI2C_Struct SENx;

/* Exported functions ------------------------------------------------------- */
void  MYI2C_Init(MYI2C_Struct *pSENSOR,unsigned int ReadTim,unsigned char xadrr);
void  MYI2C_Handle(MYI2C_Struct *pSENSOR);
/* Private functions ---------------------------------------------------------*/
void  MYI2C_Delay(unsigned int nTim);
void MYI2C_IIC_Start(void);
void MYI2C_IIC_Stop(void);
void MYI2C_IIC_Ack(unsigned char ack);
unsigned char MYI2C_IIC_Wait_Ack(unsigned char wait_time);
void MYI2C_Write_IIC_Byte(unsigned char dat);
unsigned char MYI2C_Read_IIC_Byte(void);
//void  MYI2C_Reset(void);
unsigned char MYI2C_READ_FUNC(MYI2C_Struct *pSENSOR,unsigned char device_addr,signed char register_addr, unsigned char len);
unsigned char MYI2C_WRITE_FUNC(MYI2C_Struct *pSENSOR,unsigned char device_addr,unsigned char register_addr, unsigned char *pDATA, unsigned char len);

void MYI2C_GPIO_Config(unsigned char TYP);
unsigned char  CheckCrc8(unsigned char *pDAT,unsigned char Lenth);

void JHM2030A_Config(
	MYI2C_Struct *pSENSOR,
	unsigned char SYS_CFG_REG_CAL_EN,unsigned char SYS_CFG_REG_TM_RATE,unsigned char SYS_CFG_REG_MEAS_CYC,unsigned char SYS_CFG_REG_IIR_CO,
  unsigned char CCP_CCN_REG_CCP,unsigned char CCP_CCN_REG_CCN,
  unsigned char AFE_CFG_REG_OSR_T,unsigned char AFE_CFG_REG_OSR_C,unsigned char AFE_CFG_REG_CAP_RANGE,unsigned char AFE_CFG_REG_SAMPLING_FREQ
	);
#endif //_MYI2C_h_
