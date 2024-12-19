#include "funct.h"

//��ʾ����ͼ��
void Auto_display(void)
{
	u8 i=0;
  delay_ms(5);
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x05;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x10;
	USART_03.USART_TX_BUF[5]=0x13;
	//����
	USART_03.USART_TX_BUF[6]=0;
//  USART_03.USART_TX_BUF[7]=STATU_SYS.anto_run_flag;
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
}

//ͼ��
void Biling_pic(u16 addr,u8 show)   
{
	u8 i=0;    
	
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x05;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=addr>>8;
	USART_03.USART_TX_BUF[5]=addr;
	
	USART_03.USART_TX_BUF[6]=0x00;
	USART_03.USART_TX_BUF[7]=show;
	
	
	for(i=0;i<=7;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}


//�����л�
void Change_pic(u16 addr,u8 pic_num)   
{
  u8 i=0;    
	
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x07;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=addr>>8;
	USART_03.USART_TX_BUF[5]=addr;
	
  USART_03.USART_TX_BUF[6]=0x5A;
	USART_03.USART_TX_BUF[7]=0x01;
	
	USART_03.USART_TX_BUF[8]=0x00;
	USART_03.USART_TX_BUF[9]=pic_num;
	
	
	for(i=0;i<10;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	mypri_flag=pic_num;
	
}
//����������Ϣ
void Sysconf_display(void)
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x11;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x10;
	USART_03.USART_TX_BUF[5]=0x20;
	//��������
	USART_03.USART_TX_BUF[6]=0;
//  USART_03.USART_TX_BUF[7]=CONFG_SYS.voice_flag;
	//ǿ����ҩ��
	USART_03.USART_TX_BUF[8]=0x00;
//  USART_03.USART_TX_BUF[9]=CONFG_SYS.ql_add_med_num;
	//ǿ������ʱ��
	USART_03.USART_TX_BUF[10]=0x00;
//  USART_03.USART_TX_BUF[11]=CONFG_SYS.ql_runtime;
	//�����ҩ��
	USART_03.USART_TX_BUF[12]=0x00;
//  USART_03.USART_TX_BUF[13]=CONFG_SYS.gc_add_med_num;
	//���湤��ʱ��
	USART_03.USART_TX_BUF[14]=0x00;
//  USART_03.USART_TX_BUF[15]=CONFG_SYS.gc_runtime;
	//���ҩƬ������  202102025
	USART_03.USART_TX_BUF[16]=0x00;
//  USART_03.USART_TX_BUF[17]=CONFG_SYS.med_maxnum;
	//��������20210118
	USART_03.USART_TX_BUF[18]=0;
//  USART_03.USART_TX_BUF[19]=CONFG_SYS.voice_vol;
	
	
	for(i=0;i<=19;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//������ʾϵͳ���
void Sysid_display(void)
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x09;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x10;
	USART_03.USART_TX_BUF[5]=0xC1;
	//��
	USART_03.USART_TX_BUF[6]=0;
  USART_03.USART_TX_BUF[7]=time_set.sys_year;
	//��
	USART_03.USART_TX_BUF[8]=time_set.sys_id>>8;
  USART_03.USART_TX_BUF[9]=time_set.sys_id;
	//���
	USART_03.USART_TX_BUF[10]=0;
  USART_03.USART_TX_BUF[11]=0;
	
	for(i=0;i<=11;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//����¼���������ʾ
void Sysluyin_display(void)
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x09;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x10;
	USART_03.USART_TX_BUF[5]=0xB1;
	//��
	USART_03.USART_TX_BUF[6]=0;
  USART_03.USART_TX_BUF[7]=LUYIN_SYS.ly_start_flag;
	//��
	USART_03.USART_TX_BUF[8]=0x00;
//  USART_03.USART_TX_BUF[9]=CONFG_SYS.luyin_enable;
	//���
	USART_03.USART_TX_BUF[10]=0;
  USART_03.USART_TX_BUF[11]=LUYIN_SYS.ly_time_num;
	
	for(i=0;i<=11;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//��������������ʾ
//void Syspeiw_display(void)
//{
//	u8  i=0;
//	USART_03.USART_TX_BUF[0]=0x5A;
//	USART_03.USART_TX_BUF[1]=0xA5;
//	
//	USART_03.USART_TX_BUF[2]=0x05;
//	
//	USART_03.USART_TX_BUF[3]=0x82;
//	
//	USART_03.USART_TX_BUF[4]=0x10;
//	USART_03.USART_TX_BUF[5]=0xE1;
//	//����
//	USART_03.USART_TX_BUF[6]=0;
//  USART_03.USART_TX_BUF[7]=(lora_connect_time*100/LORA_CONNECT_OUT);
//	
//	for(i=0;i<=7;i++)
//	{
//		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
//	}
//	
//}
//ϵͳʱ�������ʾ
void Systime_display(void)
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
		
	USART_03.USART_TX_BUF[2]=0x0B;
		
	USART_03.USART_TX_BUF[3]=0x82;
		
	USART_03.USART_TX_BUF[4]=0x00;
	USART_03.USART_TX_BUF[5]=0x9C;
		
	USART_03.USART_TX_BUF[6]=0x5A;
	USART_03.USART_TX_BUF[7]=0xA5;
		
	//��
	USART_03.USART_TX_BUF[8]=(u8)(calendar.w_year-2000);
	//��
  USART_03.USART_TX_BUF[9]=calendar.w_month;
	//��
  USART_03.USART_TX_BUF[10]=calendar.w_date;
	//ʱ
  USART_03.USART_TX_BUF[11]=calendar.hour;
	//��
  USART_03.USART_TX_BUF[12]=calendar.min;
	//��
  USART_03.USART_TX_BUF[13]=calendar.sec;
	USART_03.USART_TX_BUF[14]=0x00;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
}
//������Ϣ�ĸ�����ʾ
void Config_display(u8 conf_num)   
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x15;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x10;
	USART_03.USART_TX_BUF[5]=0x21;
	//�䷽  1 ����ʱ ���� ҩ��
//	USART_03.USART_TX_BUF[6]=0x00;
//  USART_03.USART_TX_BUF[7]=ONECONFG[conf_num].time11_hour;
//	
//	USART_03.USART_TX_BUF[8]=0x00;
//  USART_03.USART_TX_BUF[9]=ONECONFG[conf_num].time11_min;
//	
//	USART_03.USART_TX_BUF[10]=0x00;
//  USART_03.USART_TX_BUF[11]=ONECONFG[conf_num].run1_flag;
//	
//	//�䷽  2 ����ʱ ���� ҩ��
//	USART_03.USART_TX_BUF[12]=0x00;
//  USART_03.USART_TX_BUF[13]=ONECONFG[conf_num].time12_hour;
//	
//	USART_03.USART_TX_BUF[14]=0x00;
//  USART_03.USART_TX_BUF[15]=ONECONFG[conf_num].time12_min;
//	
//	USART_03.USART_TX_BUF[16]=0x00;
//  USART_03.USART_TX_BUF[17]=ONECONFG[conf_num].run2_flag;
//	
//	//�䷽  3 ����ʱ ���� ҩ��
//	USART_03.USART_TX_BUF[18]=0x00;
//  USART_03.USART_TX_BUF[19]=ONECONFG[conf_num].time13_hour;
//	
//	USART_03.USART_TX_BUF[20]=0x00;
//  USART_03.USART_TX_BUF[21]=ONECONFG[conf_num].time13_min;
//	
//	USART_03.USART_TX_BUF[22]=0x00;
//  USART_03.USART_TX_BUF[23]=ONECONFG[conf_num].run3_flag;
	
	for(i=0;i<=23;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//��ʾ������Ϣ
void Test_display(char *txt)   
{
	u8  i=0;
	u8 slen=0;
	slen = strlen(txt);
	
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=slen+5;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0xFE;
	USART_03.USART_TX_BUF[5]=0x00;
	
	for(i=0;i<slen;i++)
	{
		USART_03.USART_TX_BUF[6+i]=txt[i];
	}
	
	USART_03.USART_TX_BUF[slen+6]=0xFF;
	USART_03.USART_TX_BUF[slen+7]=0xFF;
	
	for(i=0;i<=(slen+7);i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//����1������Ϣ��ʾ
void Statu_display(void)   
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x1B;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x51;
	USART_03.USART_TX_BUF[5]=0x01;
	//���� 5101
	USART_03.USART_TX_BUF[6]=0x00;
  USART_03.USART_TX_BUF[7]=CJ_SYS.env_day;
	//�¶�
	USART_03.USART_TX_BUF[8]=0x00;
	USART_03.USART_TX_BUF[9]=CJ_SYS.temp;
	//ʪ��
	USART_03.USART_TX_BUF[10]=0;
	USART_03.USART_TX_BUF[11]=CJ_SYS.humity;
	//co2
	USART_03.USART_TX_BUF[12]=CJ_SYS.co2_num>>8;
  USART_03.USART_TX_BUF[13]=CJ_SYS.co2_num;
	//pm2.5
	USART_03.USART_TX_BUF[14]=CJ_SYS.pm2_5_num>>8;
	USART_03.USART_TX_BUF[15]=CJ_SYS.pm2_5_num;
	//tvoc
	USART_03.USART_TX_BUF[16]=CJ_SYS.tvoc_num>>8;
  USART_03.USART_TX_BUF[17]=CJ_SYS.tvoc_num;
	//��ȩ
	USART_03.USART_TX_BUF[18]=CJ_SYS.ch20_num>>8;
  USART_03.USART_TX_BUF[19]=CJ_SYS.ch20_num;
	
	//�·翪��ͼ��
	USART_03.USART_TX_BUF[20]=0;
	USART_03.USART_TX_BUF[21]=QF_SYS.run_flag;
	//����ת��
	USART_03.USART_TX_BUF[22]=0;
	USART_03.USART_TX_BUF[23]=QF_SYS.fan_speed;
	//ѭ��ģʽ
	USART_03.USART_TX_BUF[24]=0;
	USART_03.USART_TX_BUF[25]=QF_SYS.xhuan_mode;
	//��������
	USART_03.USART_TX_BUF[26]=0;
	USART_03.USART_TX_BUF[27]=CONFG_SYS.wifi_connect_flag;
	//����
	USART_03.USART_TX_BUF[28]=0;
	USART_03.USART_TX_BUF[29]=QF_SYS.qf_fanchong_flag;
	
	//����
	for(i=0;i<=29;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
	//ϵͳʱ�����ʾ
	delay_ms(5);
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
		
	USART_03.USART_TX_BUF[2]=0x0B;
		
	USART_03.USART_TX_BUF[3]=0x82;
		
	USART_03.USART_TX_BUF[4]=0x00;
	USART_03.USART_TX_BUF[5]=0x9C;
		
	USART_03.USART_TX_BUF[6]=0x5A;
	USART_03.USART_TX_BUF[7]=0xA5;
		
	//��
	USART_03.USART_TX_BUF[8]=(u8)(calendar.w_year-2000);
	//��
  USART_03.USART_TX_BUF[9]=calendar.w_month;
	//��
  USART_03.USART_TX_BUF[10]=calendar.w_date;
	//ʱ
  USART_03.USART_TX_BUF[11]=calendar.hour;
	//��
  USART_03.USART_TX_BUF[12]=calendar.min;
	//��
  USART_03.USART_TX_BUF[13]=calendar.sec;
	USART_03.USART_TX_BUF[14]=0x00;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//����2������Ϣ��ʾ
void Statu_display1(void)   
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x17;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x52;
	USART_03.USART_TX_BUF[5]=0x01;
	//��翪��
	USART_03.USART_TX_BUF[6]=0x00;
  USART_03.USART_TX_BUF[7]=QF_SYS.auto_flag;
	//ѭ��ģʽ
	USART_03.USART_TX_BUF[8]=0x00;
	USART_03.USART_TX_BUF[9]=QF_SYS.xhuan_mode;
	//ɱ������
	USART_03.USART_TX_BUF[10]=0;
	USART_03.USART_TX_BUF[11]=SD_SYS.run_flag;
	
	
	//��������
	USART_03.USART_TX_BUF[12]=0;
  USART_03.USART_TX_BUF[13]=FQ_SYS.fq_keting_sw1;
	//��������
	USART_03.USART_TX_BUF[14]=0;
	USART_03.USART_TX_BUF[15]=FQ_SYS.fq_chanting_sw2;
	//���Կ���
	USART_03.USART_TX_BUF[16]=0;
  USART_03.USART_TX_BUF[17]=FQ_SYS.fq_zhuwo_sw3;
	//���Կ���
	USART_03.USART_TX_BUF[18]=0;
	USART_03.USART_TX_BUF[19]=FQ_SYS.fq_ciwo_sw4;
	
	//��ʪ����
	USART_03.USART_TX_BUF[20]=0;
	USART_03.USART_TX_BUF[21]=JS_SYS.run_flag;
	//��ʪ�Զ�����
	USART_03.USART_TX_BUF[22]=0;
	USART_03.USART_TX_BUF[23]=JS_SYS.auto_mode_flag;
	//����
	USART_03.USART_TX_BUF[24]=0;
	USART_03.USART_TX_BUF[25]=QF_SYS.qf_fanchong_flag;
	
	//����
	for(i=0;i<=25;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
	//ϵͳʱ�����ʾ
	delay_ms(5);
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
		
	USART_03.USART_TX_BUF[2]=0x0B;
		
	USART_03.USART_TX_BUF[3]=0x82;
		
	USART_03.USART_TX_BUF[4]=0x00;
	USART_03.USART_TX_BUF[5]=0x9C;
		
	USART_03.USART_TX_BUF[6]=0x5A;
	USART_03.USART_TX_BUF[7]=0xA5;
		
	//��
	USART_03.USART_TX_BUF[8]=(u8)(calendar.w_year-2000);
	//��
  USART_03.USART_TX_BUF[9]=calendar.w_month;
	//��
  USART_03.USART_TX_BUF[10]=calendar.w_date;
	//ʱ
  USART_03.USART_TX_BUF[11]=calendar.hour;
	//��
  USART_03.USART_TX_BUF[12]=calendar.min;
	//��
  USART_03.USART_TX_BUF[13]=calendar.sec;
	USART_03.USART_TX_BUF[14]=0x00;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
//����3������Ϣ��ʾ
void Statu_display2(void)   
{
	u8  i=0;
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
	
	USART_03.USART_TX_BUF[2]=0x0F;
	
	USART_03.USART_TX_BUF[3]=0x82;
	
	USART_03.USART_TX_BUF[4]=0x53;
	USART_03.USART_TX_BUF[5]=0x01;
	//���˷���
	USART_03.USART_TX_BUF[6]=0x00;
  USART_03.USART_TX_BUF[7]=FQ_SYS.fq_old_room_sw5;
	//Ӥ������
	USART_03.USART_TX_BUF[8]=0x00;
	USART_03.USART_TX_BUF[9]=FQ_SYS.fq_baby_room_sw6;
	//�鷿
	USART_03.USART_TX_BUF[10]=0;
	USART_03.USART_TX_BUF[11]=FQ_SYS.fq_book_room_sw7;
	//��ñ��
	USART_03.USART_TX_BUF[12]=0;
  USART_03.USART_TX_BUF[13]=FQ_SYS.fq_kit_room_sw8;
	//��̨
	USART_03.USART_TX_BUF[14]=0;
	USART_03.USART_TX_BUF[15]=FQ_SYS.fq_ytai_sw9;
	//������
	USART_03.USART_TX_BUF[16]=0;
	USART_03.USART_TX_BUF[17]=FQ_SYS.fq_toillet_sw10;

	
	//����
	for(i=0;i<=17;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
	//ϵͳʱ�����ʾ
	delay_ms(5);
	USART_03.USART_TX_BUF[0]=0x5A;
	USART_03.USART_TX_BUF[1]=0xA5;
		
	USART_03.USART_TX_BUF[2]=0x0B;
		
	USART_03.USART_TX_BUF[3]=0x82;
		
	USART_03.USART_TX_BUF[4]=0x00;
	USART_03.USART_TX_BUF[5]=0x9C;
		
	USART_03.USART_TX_BUF[6]=0x5A;
	USART_03.USART_TX_BUF[7]=0xA5;
		
	//��
	USART_03.USART_TX_BUF[8]=(u8)(calendar.w_year-2000);
	//��
  USART_03.USART_TX_BUF[9]=calendar.w_month;
	//��
  USART_03.USART_TX_BUF[10]=calendar.w_date;
	//ʱ
  USART_03.USART_TX_BUF[11]=calendar.hour;
	//��
  USART_03.USART_TX_BUF[12]=calendar.min;
	//��
  USART_03.USART_TX_BUF[13]=calendar.sec;
	USART_03.USART_TX_BUF[14]=0x00;
	
	for(i=0;i<=14;i++)
	{
		USART_SendData(USART3,USART_03.USART_TX_BUF[i]);	
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET){}	//�ȴ�ֱ���������
	}
	
}
/*
*******************************************************************************
**��    ��:modbus_rec
**��    ��:�봥��������ͨ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
struct LUYIN_CONFG  LUYIN_SYS;

u8 rc522_flag=0;
u8 mypri_flag=0;//��ǰ����

u8 delay_time=0;

u8 sys_flag=0;//ϵͳ����  0Ϊ������   1Ϊ�����尴����

u8 chum_run_flag=0;
u8 chum_vol_num=0;
u8 chum_error_num=0;

u16 drum_time_count=0;   //��¼����ˮ�ÿ�����ʱ�䳤��
u8 start_flag=0;
void modbus_rec(void)
{
	u8 i=0;
  //u16 year=0;
	u16 psword=0;
  //u8 month,day,hour,min,sec;
//	u8 num=0;
	if(USART_03.start_rec_flag==0)
	{
		//����������
		if((USART_03.USART_RX_BUF[0]==0x5A)&&(USART_03.USART_RX_BUF[1]==0xA5))
		{
			ask_ennable=0;//�ر���ѯ
			sys_flag=0;
			if(USART_03.USART_RX_BUF[3]==0x83)
			{
			delay_time=0;//ͨ�ų�ʱ
				
				if((USART_03.USART_RX_BUF[4]==0xFF)&&(USART_03.USART_RX_BUF[5]==0xFF))
			 {
				mypri_flag=USART_03.USART_RX_BUF[8];
				//����ʱ�����ý������Ƚ��н���ĸ���
				if(mypri_flag==2)
				{
					Systime_display();
				}
				else if(mypri_flag==1)
				{
					Sysconf_display();
				}
				else if(mypri_flag==0x0b)//�����豸���
				{
					Sysid_display();
				}
				else if(mypri_flag==0x0a)//¼����ʼ��
				{

					Biling_pic(0x10B6,0);
					delay_ms(20);
					//������ʾ
					Sysluyin_display();
					
				}
			}
			//�������
			else if((USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0x81))
			{
					psword=((u16)USART_03.USART_RX_BUF[7]<<8)+((u16)USART_03.USART_RX_BUF[8]);
					if(psword==1234)
					{
						Change_pic(0x0084,5);//������ȷֱ����ת//�л�����0
					}
					else
					{
						//��ʾ�������
						Biling_pic(0x1091,1);
						delay_ms(500);
						Biling_pic(0x1091,0);
					}
				}
			
			//��������
			if(mypri_flag==0)
			{
				if((USART_03.USART_RX_BUF[2]==0x06)&&(USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10))
				{
					
				}
			}
			//����1
			else if(mypri_flag==1)
			{
				//�·翪��
				 if((USART_03.USART_RX_BUF[4]==0x51)&&(USART_03.USART_RX_BUF[5]==0x11))
				{
					if(QF_SYS.auto_flag==0)
					{
						if((USART_03.USART_RX_BUF[8]==0x00))
						{
							Control_node(0xB0,0xBB,0xFF);	
							QF_SYS.run_flag=0;	
							Biling_pic(0x5111,1);	
							if(SD_SYS.run_flag==1)
							{							
									delay_ms(200);
									Control_node(0xC0,0xBB,0);
									SD_SYS.run_flag=0;
									Biling_pic(0x5213,1);
							}
													
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))
						{
							Control_node(0xB0,0xBB,0);		
							QF_SYS.run_flag=1;
							Biling_pic(0x5111,0);								
						}
				  }
					
				}
				//���ȵ���
				else if((USART_03.USART_RX_BUF[4]==0x51)&&(USART_03.USART_RX_BUF[5]==0x12))
				{
           if((USART_03.USART_RX_BUF[8]==0x00))
					{
						Control_node(0xB0,0xC2,0);
						QF_SYS.fan_speed=0;
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))
					{
						Control_node(0xB0,0xC2,1);
						QF_SYS.fan_speed=1;
					}
					else if((USART_03.USART_RX_BUF[8]==0x02))
					{
						Control_node(0xB0,0xC2,2);
						QF_SYS.fan_speed=2;
					}
					else if((USART_03.USART_RX_BUF[8]==0x03))
					{
						Control_node(0xB0,0xC2,3);
						QF_SYS.fan_speed=3;
					}
					
				
				}
				//ѭ������
				else if((USART_03.USART_RX_BUF[4]==0x51)&&(USART_03.USART_RX_BUF[5]==0x13))
				{
						if((USART_03.USART_RX_BUF[8]==0x00))//����
						{
							Control_node(0xB0,0xC1,0);
							QF_SYS.xhuan_mode=0;
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//����
						{
							Control_node(0xB0,0xC1,1);
							QF_SYS.xhuan_mode=1;
						}
						else if((USART_03.USART_RX_BUF[8]==0x02))//����
						{
							Control_node(0xB0,0xC3,0);
							QF_SYS.qf_fanchong_flag=1;
						}
				  
				}
				//��������
				 if((USART_03.USART_RX_BUF[4]==0x51)&&(USART_03.USART_RX_BUF[5]==0x14))
				{
          //ִ����������
				
				}
				delay_ms(10);
				Statu_display();
			}
			//����2
			else if(mypri_flag==2)
			{
				

				//�·����Զ�����
				 if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x11))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))
					{
						Control_node(0xB0,0xD1,0xFF);
            QF_SYS.auto_flag=0;	
						 Biling_pic(0x5211,1);									
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))
					{
						Control_node(0xB0,0xD1,0);	
            QF_SYS.auto_flag=1;	
            Biling_pic(0x5211,0);							
					}
					
				}
				//ѭ������
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x12))
				{
						if((USART_03.USART_RX_BUF[8]==0x00))//����
						{
							Control_node(0xB0,0xC1,0);
							QF_SYS.xhuan_mode=0;
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//����
						{
							Control_node(0xB0,0xC1,1);
							QF_SYS.xhuan_mode=1;
						}
						else if((USART_03.USART_RX_BUF[8]==0x02))//����
						{
							Control_node(0xB0,0xC3,0);
							QF_SYS.qf_fanchong_flag=1;
						}
				  
				}
				//ɱ������
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x13))
				{
						if((USART_03.USART_RX_BUF[8]==0x00))//��
						{
							if(QF_SYS.run_flag==1)//�·�ϵͳ���������ִ��
							{
							  Control_node(0xC0,0xBB,0xFF);
								SD_SYS.run_flag=0;
								Biling_pic(0x5213,1);
								if(QF_SYS.xhuan_mode==0)//���������ѭ����������ѭ��
								{
									delay_ms(200);
									Control_node(0xB0,0xC1,1);//������ѭ��
									QF_SYS.xhuan_mode=0;
								}
								
							}
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//��
						{
							Control_node(0xC0,0xBB,0);
							SD_SYS.run_flag=1;
							Biling_pic(0x5213,0);
						}
				  
				}
				//��ʪ����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x18))
				{
					if(JS_SYS.auto_mode_flag==0)
					{
						if((USART_03.USART_RX_BUF[8]==0x00))//��
						{
							Control_node(0xA0,0xBB,0xFF);
							JS_SYS.run_flag=0;
							Biling_pic(0x5218,1);
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//��
						{
							Control_node(0xA0,0xBB,0);
							JS_SYS.run_flag=1;
							Biling_pic(0x5218,0);
						}
					}
				  
				}
				//��ʪ���Զ�����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x19))
				{
						if((USART_03.USART_RX_BUF[8]==0x00))//�Զ�
						{
							Control_node(0xA0,0xBB,0xAA);
							JS_SYS.auto_mode_flag=1;
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//�ֶ�
						{
							Control_node(0xA0,0xBB,0xBB);
							JS_SYS.auto_mode_flag=0;
						}
				  
				}
				//����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x14))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_keting_sw1=1;
						Biling_pic(0x5214,1);
						FQ_Control_node(0xD0,0xBB,1,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_keting_sw1=0;
						Biling_pic(0x5214,0);
						FQ_Control_node(0xD0,0xBB,1,0xFF);
					}
							
				}
				//����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x15))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_chanting_sw2=1;
						Biling_pic(0x5215,1);
						FQ_Control_node(0xD0,0xBB,2,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_chanting_sw2=0;
						Biling_pic(0x5215,0);
						FQ_Control_node(0xD0,0xBB,2,0xFF);
					}
				}
				//����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x16))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_zhuwo_sw3=1;
						Biling_pic(0x5216,1);
						FQ_Control_node(0xD0,0xBB,3,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_zhuwo_sw3=0;
						Biling_pic(0x5216,0);
						FQ_Control_node(0xD0,0xBB,3,0xFF);
					}
				}
				//����
				else if((USART_03.USART_RX_BUF[4]==0x52)&&(USART_03.USART_RX_BUF[5]==0x17))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_ciwo_sw4=1;
						Biling_pic(0x5217,1);
						FQ_Control_node(0xD0,0xBB,4,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_ciwo_sw4=0;
						Biling_pic(0x5217,0);
						FQ_Control_node(0xD0,0xBB,4,0xFF);
					}
				}
				
				delay_ms(10);
				Statu_display1();
				delay_ms(10);
			}
			//����3���ý���
			else if(mypri_flag==3)
			{
				//��ȡϵͳ������Ϣ
				 if((USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0x71))
				{
					Sysconf_display();
				}
				//д��ϵͳ������Ϣ
				 else if((USART_03.USART_RX_BUF[4]==0xF2)&&(USART_03.USART_RX_BUF[5]==0x01)&&(USART_03.USART_RX_BUF[6]==0x05))
				{
					
					//��ʾ���óɹ�
					Biling_pic(0x1F02,1);
					delay_ms(500);
					Biling_pic(0x1F02,0);
					
				}
				//�������
				else if((USART_03.USART_RX_BUF[4]==0x54)&&(USART_03.USART_RX_BUF[5]==0x01))
				{
						if((USART_03.USART_RX_BUF[8]==0x00))//Ĭ��
						{
							Control_node(0xB0,0xC1,0xAA);
						}
						else if((USART_03.USART_RX_BUF[8]==0x01))//����ȸ���
						{
							Control_node(0xB0,0xC1,2);
						}
				}
				//���˷�
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x11))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_old_room_sw5=1;
						Biling_pic(0x5311,1);
						FQ_Control_node(0xD0,0xBB,5,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_old_room_sw5=0;
						Biling_pic(0x5311,0);
						FQ_Control_node(0xD0,0xBB,5,0xFF);
					}
							
				}
				//Ӥ����
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x12))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_baby_room_sw6=1;
						Biling_pic(0x5312,1);
						FQ_Control_node(0xD0,0xBB,6,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_baby_room_sw6=0;
						Biling_pic(0x5312,0);
						FQ_Control_node(0xD0,0xBB,6,0xFF);
					}
				}
				//�鷿
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x13))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_book_room_sw7=1;
						Biling_pic(0x5313,1);
						FQ_Control_node(0xD0,0xBB,7,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_book_room_sw7=0;
						Biling_pic(0x5313,0);
						FQ_Control_node(0xD0,0xBB,7,0xFF);
					}
				}
				//����
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x14))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_kit_room_sw8=1;
						Biling_pic(0x5314,1);
						FQ_Control_node(0xD0,0xBB,8,0);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_kit_room_sw8=0;
						Biling_pic(0x5314,0);
						FQ_Control_node(0xD0,0xBB,8,0xFF);
					}
				}
				//��̨
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x15))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_ytai_sw9=1;
						Biling_pic(0x5315,1);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_ytai_sw9=0;
						Biling_pic(0x5315,0);
					}
				}
				//������
				else if((USART_03.USART_RX_BUF[4]==0x53)&&(USART_03.USART_RX_BUF[5]==0x16))
				{
					if((USART_03.USART_RX_BUF[8]==0x00))//��
					{
						FQ_SYS.fq_toillet_sw10=1;
						Biling_pic(0x5316,1);
					}
					else if((USART_03.USART_RX_BUF[8]==0x01))//��
					{
						FQ_SYS.fq_toillet_sw10=0;
						Biling_pic(0x5316,0);
					}
				}
				delay_ms(10);
				Statu_display2();
			}
			//�������
			else if(mypri_flag==4)
			{
				
				
			}
			//¼������
			else if(mypri_flag==0x0a)
			{
				//¼��
				if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xB4))
				{
				
				}
				//ֹͣ
				else if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xB5))
				{
					
					//������ʾ
					Sysluyin_display();

				}
				//����
				else if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xB6))
				{
					
					
				}
				//����
				else if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xB7))
				{
					if(USART_03.USART_RX_BUF[8]==1)
					{
						
						Biling_pic(0x10B6,1);
					}
					else if(USART_03.USART_RX_BUF[8]==0)
					{
					
					  Biling_pic(0x10B6,0);
					}
					//������ʾ
					Sysluyin_display();
				}
				
			}
			//���ý���
			else if(mypri_flag==0x0b)
			{
				//�����豸����
				if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xC5))
				{
				
		      
				}
				
			}
			//��������
			else if(mypri_flag==14)
			{
				if((USART_03.USART_RX_BUF[3]==0x83)&&(USART_03.USART_RX_BUF[4]==0x10)&&(USART_03.USART_RX_BUF[5]==0xE2))
				{
					
				}
			}
			
		}
	  ask_ennable=1;//���¿�����ѯ
	}
		//����
	  else if((USART_03.USART_RX_BUF[0]==0x41)&&(USART_03.USART_RX_BUF[1]==0x54))
		{
			u3_printf("OK\r\n");  
		}
		//��̬�ɼ�
		else if((USART_03.USART_RX_BUF[0]==ZTSYS_ADDR)&&(USART_03.USART_RX_BUF[1]==0x03))
		{
			STATU_SYS.m6050_time=0;
			if(ask_flag==2)
			{
				STATU_SYS.roll_h=USART_03.USART_RX_BUF[3];
				STATU_SYS.roll_l=USART_03.USART_RX_BUF[4];
				
				STATU_SYS.pitch_h=USART_03.USART_RX_BUF[5];
				STATU_SYS.pitch_l=USART_03.USART_RX_BUF[6];
				
				STATU_SYS.yaw_h=USART_03.USART_RX_BUF[7];
				STATU_SYS.yaw_l=USART_03.USART_RX_BUF[8];
				//��̬�Ǽ���
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
				STATU_SYS.ax_h=USART_03.USART_RX_BUF[3];
				STATU_SYS.ax_l=USART_03.USART_RX_BUF[4];
				
				STATU_SYS.ay_h=USART_03.USART_RX_BUF[5];
				STATU_SYS.ay_l=USART_03.USART_RX_BUF[6];
				
				STATU_SYS.az_h=USART_03.USART_RX_BUF[7];
				STATU_SYS.az_l=USART_03.USART_RX_BUF[8];
			}
			else if(ask_flag==4)
			{
				STATU_SYS.wx_h=USART_03.USART_RX_BUF[3];
				STATU_SYS.wx_l=USART_03.USART_RX_BUF[4];
				
				STATU_SYS.wy_h=USART_03.USART_RX_BUF[5];
				STATU_SYS.wy_l=USART_03.USART_RX_BUF[6];
				
				STATU_SYS.wz_h=USART_03.USART_RX_BUF[7];
				STATU_SYS.wz_l=USART_03.USART_RX_BUF[8];
			}
			else if(ask_flag==5)
			{
				STATU_SYS.hx_h=USART_03.USART_RX_BUF[3];
				STATU_SYS.hx_l=USART_03.USART_RX_BUF[4];
				
				STATU_SYS.hy_h=USART_03.USART_RX_BUF[5];
				STATU_SYS.hy_l=USART_03.USART_RX_BUF[6];
				
				STATU_SYS.hz_h=USART_03.USART_RX_BUF[7];
				STATU_SYS.hz_l=USART_03.USART_RX_BUF[8];
				
				STATU_SYS.hh_h=USART_03.USART_RX_BUF[9];
				STATU_SYS.hh_l=USART_03.USART_RX_BUF[10];
			}
			else if(ask_flag==6)
			{
				STATU_SYS.q0_h=USART_03.USART_RX_BUF[3];
				STATU_SYS.q0_l=USART_03.USART_RX_BUF[4];
				
				STATU_SYS.q1_h=USART_03.USART_RX_BUF[5];
				STATU_SYS.q1_l=USART_03.USART_RX_BUF[6];
				
				STATU_SYS.q2_h=USART_03.USART_RX_BUF[7];
				STATU_SYS.q2_l=USART_03.USART_RX_BUF[8];
				
				STATU_SYS.q3_h=USART_03.USART_RX_BUF[9];
				STATU_SYS.q3_l=USART_03.USART_RX_BUF[10];
			}
			if(ask_flag==7)
			{
				if(USART_03.USART_RX_BUF[3]>=0x80)
				{
			    STATU_SYS.zf_num=0xffff-((((u16)USART_03.USART_RX_BUF[3])<<8)+(u16)USART_03.USART_RX_BUF[4])+1;
				}
				else
				{
					STATU_SYS.zf_num=((((u16)USART_03.USART_RX_BUF[3])<<8)+(u16)USART_03.USART_RX_BUF[4]);
				}
			  //STATU_SYS.zf_num=(((u16)USART_03.USART_RX_BUF[3])<<8)+(u16)USART_03.USART_RX_BUF[4];
			}
		}
		//����������
		else if((USART_03.USART_RX_BUF[0]==ZF_ADDR)&&(USART_03.USART_RX_BUF[1]==0x03))
		{
			if(ask_flag==7)
			{
				if(USART_03.USART_RX_BUF[3]>=0x80)
				{
			    STATU_SYS.zf_num=0xffff-((((u16)USART_03.USART_RX_BUF[3])<<8)+(u16)USART_03.USART_RX_BUF[4])+1;
				}
				else
				{
					STATU_SYS.zf_num=((((u16)USART_03.USART_RX_BUF[3])<<8)+(u16)USART_03.USART_RX_BUF[4]);
				}
				
			}
			
		}
		//����
		else if((USART_03.USART_RX_BUF[0]==0x49)&&(USART_03.USART_RX_BUF[USART_03.USART_RX_STA-1]==0xFC))
		{
			Uart1SendBuffer(USART_03.USART_RX_BUF,USART_03.USART_RX_STA);
		}
		//ģ������
		else if((USART_03.USART_RX_BUF[0]==0xFE)&&(USART_03.USART_RX_BUF[USART_03.USART_RX_STA-1]==0xFD))
		{
			Back_sn_test();
		}
	/*���ݵ��жϺ���������----------end*/
	for(i=0;i<USART_REC_LEN;i++)
	{
		USART_03.USART_RX_BUF[i]=0;      	      //���渴λ
	}
	USART_03.USART_RX_STA=0;             		 	//��־λ��λ	
	USART_03.usart_time_count=0;
	USART_03.start_rec_flag=1;     		 	      //���¿�ʼ����	
		
	}
	

}
//¼����ʱ����
void luyin_task(void)
{
	if(LUYIN_SYS.ly_start_flag==1)
	{
		LUYIN_SYS.ly_time_num++;
		Sysluyin_display();
		if(LUYIN_SYS.ly_time_num>=60)
		{
			LUYIN_SYS.ly_start_flag=0;
			LUYIN_SYS.ly_time_num=0;
//			ly_voice_stop_ly();
			//������ʾ
			Sysluyin_display();
			
		}
		
		
	}
	
}





