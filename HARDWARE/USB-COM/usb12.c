#include "funct.h"
//检查是否是该集中器内部的节点

//struct _USARTSX CONF_01X;

//u8 node_check(u16 num)
//{
//	u8 numx=0;
//	for(numx=0;numx<node_num_in;numx++)
//	{
//		if(node_add[numx]==num)
//		{
//			return 1;
//			//break;
//		}
//		
//	}
//	return 0;
//	
//}


/*
*******************************************************************************
**函    数:usart5_send
**功    能:具体报文的发送的底层报文
**参    数:station_flag为站号,fundata为功能码,count具体的数量,begin_addr开始的地址
**返 回 值:无
**创建日期:
**修改记录:
**说    明:04为读取多个输入寄存器的状态，03为读取多个保持寄存器的状态，
           02为读取输入线圈/点的状态，01为读取输出线圈/点的状态

*******************************************************************************
*/
void Usb_send_request(u8 station_flag,u8 fundata,u8 count,u16 begin_addr)
{
	u8 i;
	u16 CRC_num;
	USART_05.USART_TX_BUF[0]=station_flag;
	USART_05.USART_TX_BUF[1]=fundata;
	USART_05.USART_TX_BUF[2]=(u8)(begin_addr>>8);
	USART_05.USART_TX_BUF[3]=(u8)(begin_addr);
	USART_05.USART_TX_BUF[4]=0;
	USART_05.USART_TX_BUF[5]=count;
	CRC_num=CRCCheck(USART_05.USART_TX_BUF,6);
	USART_05.USART_TX_BUF[6]=(u8)(CRC_num>>8);
  USART_05.USART_TX_BUF[7]=(u8)CRC_num;
	
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_05.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	
	
}

/*
*******************************************************************************
**函    数:usart5_send_order
**功    能:强制对位进行写操作，控制系统的运行
**参    数:
**返 回 值:
**创建日期:
**修改记录:
**说    明:flag==0x00/0xff
*******************************************************************************
*/
void Usb_send_order(u8 station_flag,u16 order_addr,u8 flag)
{
	u8 i;
	u16 CRC_num;
	USART_05.USART_TX_BUF[0]=station_flag;
	USART_05.USART_TX_BUF[1]=0x05;
	USART_05.USART_TX_BUF[2]=(u8)(order_addr>>8);
	USART_05.USART_TX_BUF[3]=(u8)(order_addr);
	USART_05.USART_TX_BUF[4]=flag;
	USART_05.USART_TX_BUF[5]=0;
	CRC_num=CRCCheck(USART_05.USART_TX_BUF,6);
	USART_05.USART_TX_BUF[6]=(u8)(CRC_num>>8);
  USART_05.USART_TX_BUF[7]=(u8)CRC_num;
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART2,USART_05.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET){}	//等待直到发送完成
	}
	
}




/*
*******************************************************************************
**函    数:usb_rec(void)
**功    能:接收其它通信设备返回的报文
**参    数:
**返 回 值:无
**创建日期:
**修改记录:
**说    明:
*******************************************************************************
*/
u16 node_add[NODE_NUM_X]={0}; 
//struct _CONFx conf_01;
//u16 run_time=0;//定时运行的时长
void usb_rec(void)
{
	u8 count,ctemp;
	u8 _id_year,_id_month;
	u16 _id_num;
	u16 sysid;
	u16 year=0;
	u8 month,day,hour,min,sec;
//	u32 cteyy=0;
//	u8 month,day,hour,min,sec;
	if(USART_05.start_rec_flag==0)
	{

		if(USART_05.USART_RX_STA<=2)
		{//AT   OK
			if((USART_05.USART_RX_BUF[0]==0x41)&&(USART_05.USART_RX_BUF[1]==0x54))
			{
				u5_printf("OK\r\n");  //测试
			}
			
		}
		else
		{
			if((USART_05.USART_RX_BUF[0]==0x41)&&(USART_05.USART_RX_BUF[1]==0x54))
			{
				//读取系统ID
				if(strstr((const char*)USART_05.USART_RX_BUF,"AT+ID=?")!= NULL)
				{
          u5_printf("AT+ID=%02d%05d",time_set.sys_year,time_set.sys_id);
				}
				//设置系统ID
        else if(strstr((const char*)USART_05.USART_RX_BUF,"AT+ID=")!= NULL)	
				{
          _id_year=(USART_05.USART_RX_BUF[6]-0x30)*10+(USART_05.USART_RX_BUF[7]-0x30);
					_id_month=(USART_05.USART_RX_BUF[8]-0x30)*10+(USART_05.USART_RX_BUF[9]-0x30);
					_id_num=(USART_05.USART_RX_BUF[10]-0x30)*100+(USART_05.USART_RX_BUF[11]-0x30)*10+(USART_05.USART_RX_BUF[12]-0x30);        
					if((_id_year>21)&&(_id_month<=12)&&(_id_num<=999))
					{
						sysid=(u16)_id_month*1000+_id_num;
						//REC_sys_id  
						ctemp = sysid; 
						AT24CXX_Write(EE_SYS_ID,  &(ctemp), 1);
						ctemp = sysid>>8; 
						AT24CXX_Write(EE_SYS_ID+1,  &(ctemp), 1);
						time_set.sys_id=sysid; 
						
						ctemp = _id_year;  
						AT24CXX_Write(EE_SYS_ID_YEAR,  &(ctemp), 1);
						time_set.sys_year=_id_year;
						
						u5_printf("AT+ID=OK\r\n");
					}
					else
					{
						u5_printf("AT+ID=ERROR\r\n");
					}
				}	
				//读取系统时间
        else if(strstr((const char*)USART_05.USART_RX_BUF,"AT+TIME=?")!= NULL)	
				{
          u5_printf("TIME:%d-%d-%d/%d:%d:%d\r\n",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
				}
				//设置系统时间
        else if(strstr((const char*)USART_05.USART_RX_BUF,"AT+TIME=")!= NULL)	
				{
					 year=(USART_05.USART_RX_BUF[8]-0x30)*1000+(USART_05.USART_RX_BUF[9]-0x30)*100+(USART_05.USART_RX_BUF[10]-0x30)*10+(USART_05.USART_RX_BUF[11]-0x30);
					 month=(USART_05.USART_RX_BUF[13]-0x30)*10+(USART_05.USART_RX_BUF[14]-0x30);
					 day=(USART_05.USART_RX_BUF[16]-0x30)*10+(USART_05.USART_RX_BUF[17]-0x30);
					 hour=(USART_05.USART_RX_BUF[19]-0x30)*10+(USART_05.USART_RX_BUF[20]-0x30);
					 min=(USART_05.USART_RX_BUF[22]-0x30)*10+(USART_05.USART_RX_BUF[23]-0x30);
					 sec=(USART_05.USART_RX_BUF[25]-0x30)*10+(USART_05.USART_RX_BUF[26]-0x30);
//					 RTC_Set(year,month,day,hour,min,sec);
					 u5_printf("AT+TIME=OK\r\n");
				}
				//测试
        else if(strstr((const char*)USART_05.USART_RX_BUF,"AT+TEST")!= NULL)	
				{
           if(strstr((const char*)USART_05.USART_RX_BUF,"ALL OPEN")!= NULL)
					 {
						  RELAY1_EN=1;
						  RELAY2_EN=1;
						  u5_printf("ALL OPEN OK");
					 }
					 else if(strstr((const char*)USART_05.USART_RX_BUF,"ALL CLOSE")!= NULL)
					 {
						 RELAY1_EN=0;
						 RELAY2_EN=0;
						 u5_printf("ALL CLOSE OK");
					 }
					 else if(strstr((const char*)USART_05.USART_RX_BUF,"READ")!= NULL)
					 {
//							u5_printf("SYS:%01d/%01d/%01d/%01d/%01d",STATU_SYS.M_relay1_flag,STATU_SYS.M_relay2_flag,STATU_SYS.M_sw_level1_flag,STATU_SYS.M_sw_level2_flag,STATU_SYS.M_sw_level3_flag);
							
					 }
					 else 
					 {
						 
					 }
				}
         //复位
        else if(strstr((const char*)USART_05.USART_RX_BUF,"AT+REST")!= NULL)	
				{		
            ctemp = 0; 
		        AT24CXX_Write(EE_BOARD_ID, &(ctemp), 1);
					  time_set.board_id=ctemp;
					  u5_printf("RESET OK");
				}					
				
			}
			else if((USART_05.USART_RX_BUF[0]==0x68)&&(USART_05.USART_RX_BUF[USART_05.USART_RX_STA-1]==0x16))
			{
				
				Uart4SendBuffer(USART_05.USART_RX_BUF,USART_05.USART_RX_STA);
				u5_printf("node send ok!\r\n");
			}
			else if((USART_05.USART_RX_BUF[0]==0x5A)&&(USART_05.USART_RX_BUF[1]==0xA5))
			{
				Uart3SendBuffer(USART_05.USART_RX_BUF,USART_05.USART_RX_STA);
				u5_printf("display send ok!\r\n");
			}
		
		}
		
		
		/*数据的判断和任务的添加----------end*/
		for(count=0;count<USART_REC_LEN;count++)
		{
			USART_05.USART_RX_BUF[count]=0;      	  //缓存复位
		}
		USART_05.USART_RX_STA=0;             		 	//标志位复位	
		USART_05.usart_time_count=0;
		USART_05.start_rec_flag=1;     		 	      //重新开始接收	
	
	
   }
}
