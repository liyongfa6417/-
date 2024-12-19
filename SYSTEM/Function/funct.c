#include "funct.h"  

/*
*******************************************************************************
**��    ��:System_Configuration(void)
**��    ��:ϵͳ������ģ��ĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u16 HostAddress = 10;								    // �豸���ߵ�ַ
u8 HostAddress_chan=8;
void System_Configuration(void)
{
  RCC_Configuration();          //����ϵͳʱ��Ϊ72Mhz	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	delay_init();	    	          //��ʱ������ʼ��	
	
	LED_GPIO_Configuration(); 

  E32_SWI_TO_SLEEP();	
	
	//Buzzer_GPIO_Configuration();
	
	KEY_Init();                   //�����ĳ�ʼ��
	
	RELAY_GPIO_Configuration();
	
	//RGB_LED_Init();
	
  //RTC_Init();
	
	//DHT11_Init();
	
  AT24CXX_Init();               //24c02��ʼ�� 
	
//  while(AT24CXX_Check())       //���ж�д���	
//	{
//		delay_ms(100);
//		LED0_RED=!LED0_RED; 
//	}
	while(AT24CXX_JMCheck())     
	{
		delay_ms(50);
		LED0_RED=!LED0_RED; 
	}
	EEprom_check();              //eeprom�ڲ����ݵ�У�� 
	
	Adc_Configuration();
	
	TIM2_Configuration();         //��ʱΪ1MS����ϵͳ�ڲ�������л�
	
	//TIM4_Configuration();
	
	//EXTI_one_Config();
	
	#if EN_USART1
	USART1_Configuration(115200);
	#endif
	
	#if EN_USART2
	USART2_Configuration(115200);
	#endif
	
	#if EN_USART3
	USART3_Configuration(115200);
	#endif
	
	#if EN_USART4
	USART4_Configuration(115200);
	#endif
	
	#if EN_USART5
	USART5_Configuration(115200);
	#endif
	
	/*CAN��ʼ������ģʽ,������500Kbps��36M/((1+8+3)*6)=500Kbps----*/
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_5tq,CAN_BS1_2tq,9,CAN_Mode_Normal);
	
	Data_init();
	
	TIM8_PWM_Init(999,8);        //����PWM������ڿ��Ƶ���Ķ���  50HZƵ�� 19999  71
	TIM3_PWM_Init(999,8);        //���ڶ���ǰ������
	//����
	TIM_SetCompare1(TIM8,100);
	
	//����
	TIM_SetCompare2(TIM8,10);
	TIM_SetCompare3(TIM8,10);
  TIM_SetCompare4(TIM8,10);
	
	TIM_SetCompare1(TIM3,10);
  TIM_SetCompare2(TIM3,10);
	
	SHT_Init();
	
//	RTC_Get();                    //��ȡʱ��
	
	TIM_Cmd(TIM2, ENABLE);  		  //��ʼ��TIM2��������ʱ��
	
	//delay_ms(1000); 
	
	//��ȡlora������Ϣ///////////////////////////
//	while(AUX_P);
//	
//	SetE32Com[1]=HostAddress>>8;
//	SetE32Com[2]=HostAddress;
//	SetE32Com[4]=HostAddress_chan;

//	Uart4SendBuffer(SetE32Com,6);   //����������Ϣ
//						
//	delay_ms(100);
//	
//	Uart4SendBuffer(ReadE32ParCom,3);//��ȡ������Ϣ	

//  while(USART_04.start_rec_flag==1)//�ȴ���������
//	{
//		LED0_RED=!LED0_RED;
//		delay_ms(50);
//	}
//  usart4_rec();                      //��ȡ����ģ�����Ϣ
//	u1_printf("Lora inf:\r\n");	
//	u1_printf("address:%d/speed:%d/chan:%d/option:%d\r\n",POINT_IN.point_address,POINT_IN.point_speed,POINT_IN.point_chan,POINT_IN.point_option);
//	
//	E32_SWI_TO_TRANSMIT();             //����ģʽ 
	//��ȡlora������Ϣend///////////////////////////////
	
		SHT_Init();  //��ʪ�Ȳɼ�AHT10/AHT20
	#if TEMP_ENABLE 
	//LED3_RED=1; 
	#endif
}

/*
*******************************************************************************
**��    ��:Data_init(void)
**��    ��:�������ĳ�ʼ��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
void Data_init(void)
{
	USART_01.start_rec_flag=1;
	start_rec_time_out=0;
  USART_03.start_rec_flag=1; 
	USART_02.start_rec_flag=1; 
	USART_04.start_rec_flag=1; 
	USART_05.start_rec_flag=1; 	
	time2_counter=1;
//	node_num=REC_NODE_NUM;
//	node_address[0]=0XA0;
//	node_address[1]=0XB0;
//	node_address[2]=0XC0;
//	node_address[3]=0XD0;
//	node_address[4]=0XE0;
//	node_address[5]=0XF0;
//	
//	CJ_SYS.temp=10;
//	CJ_SYS.humity=60;
//	CJ_SYS.pm2_5_num=113;
//	CJ_SYS.co2_num=312;
//	CJ_SYS.tvoc_num=62;
//	CJ_SYS.ch20_num=11;
	ask_ennable=1;
}
/*
*******************************************************************************
**��    ��:EEprom_check(void)
**��    ��:eeprom�ڲ����ݵ�У��
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
_ee_time_set time_set; 
struct _STATU  STATU_SYS;
struct _CONFG  CONFG_SYS;
struct _CJ_SYS  CJ_SYS;
struct _JS_SYS  JS_SYS;
struct _QF_SYS  QF_SYS;
struct _SD_SYS  SD_SYS;
struct _FQ_SYS  FQ_SYS;
char password[4]={'R','Y','W','L'};
void EEprom_check(void)
{
	u8 ctemp,cff;
	AT24CXX_Read(EE_INIT_FLAG_ADDR, &ctemp, 1);								// ��ȡEEPROM��ʼ����־

	if (ctemp != EE_INIT_FLAG)													      // EEPROMû�г�ʼ����,����������Ҫ�����Ĭ������
	{
		delay_ms(10);
		AT24CXX_Read(EE_INIT_FLAG_ADDR, &ctemp, 1);							// ��ȡEEPROM��ʼ����־

		if (ctemp != EE_INIT_FLAG)												      // EEPROMû�г�ʼ����,����������Ҫ�����Ĭ������
		{
	 		delay_ms(10);
			AT24CXX_Read(EE_INIT_FLAG_ADDR, &ctemp, 1);						// ��ȡEEPROM��ʼ����־ 
  	}
	}
  //���ݻָ�
	if(ctemp != EE_INIT_FLAG)
	{
		//REC_sys_id  
		ctemp = REC_sys_id; 
		AT24CXX_Write(EE_SYS_ID,  &(ctemp), 1);
		ctemp = REC_sys_id>>8; 
		AT24CXX_Write(EE_SYS_ID+1,  &(ctemp), 1);
		time_set.sys_id=REC_sys_id; 
		
		ctemp = REC_sys_year;  
		AT24CXX_Write(EE_SYS_ID_YEAR,  &(ctemp), 1);
		time_set.sys_year=REC_sys_year; 
		
		//д��Ĭ������
		for(cff=0;cff<4;cff++)
		{
			ctemp=password[cff];
			AT24CXX_Write((EE_LOCK_ID+cff),&ctemp,1); 
		}
		//д���·�����
    ctemp = sys_soft_ver; 
		AT24CXX_Write(EE_BOARD_ID, &(ctemp), 1);
		time_set.board_id=sys_soft_ver;

		//д�븺ѹ��У׼ֵ
		ctemp = REC_FY_SET_ADD; 
		AT24CXX_Write(EE_FY_SET_ADD, &(ctemp), 1);
		STATU_SYS.fy_set_add=REC_FY_SET_ADD;
		
		////////////////////////////////////////////
		ctemp = EE_INIT_FLAG;
		AT24CXX_Write(EE_INIT_FLAG_ADDR,  &ctemp, 1);
	}
	//��ȡeeprom�ڲ�������䷽
	else
	{
		// ��ȡ������
		//REC_sys_id
		AT24CXX_Read(EE_SYS_ID+1, &ctemp, 1);
		time_set.sys_id= ctemp<<8;	
    AT24CXX_Read(EE_SYS_ID, &ctemp, 1);		
		time_set.sys_id+=ctemp;
		
		AT24CXX_Read(EE_SYS_ID_YEAR, &ctemp, 1);
		time_set.sys_year= ctemp;	
		
		//��ȡ�ڲ�������
		for(cff=0;cff<4;cff++)
		{
			AT24CXX_Read(EE_LOCK_ID+cff, &ctemp, 1);
			password[cff] = ctemp;	
			
		}
		//��ȡ��·�����
		AT24CXX_Read(EE_BOARD_ID, &(time_set.board_id), 1);
		if(time_set.board_id!=sys_soft_ver)
		{
			ctemp = sys_soft_ver; 
		  AT24CXX_Write(EE_BOARD_ID, &(ctemp), 1);
		  time_set.board_id=sys_soft_ver;
			
		}
		
		
		AT24CXX_Read(EE_FY_SET_ADD, &ctemp, 1);
		STATU_SYS.fy_set_add= ctemp;	
		if(STATU_SYS.fy_set_add>100)
		{
			//д�븺ѹ��У׼ֵ
			ctemp = REC_FY_SET_ADD; 
			AT24CXX_Write(EE_FY_SET_ADD, &(ctemp), 1);
			STATU_SYS.fy_set_add=REC_FY_SET_ADD;
		}
	}
	
}
/*
*******************************************************************************
**��    ��:void led_update(void)
**��    ��:״ָ̬ʾ�Ƶĸ���
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u8 led_blink_count=0;

void led_update(void)
{

//	LED1_RED=!LED1_RED;
	LED0_RED=!LED0_RED;
	
}
//����ɨ��
void switch_scan(void)
{
	//����1 
	if(SW_1==0)  
	{
		delay_ms(100);
		if(SW_1==0)  
		{
			
			RELAY1_EN=!RELAY1_EN;
			RELAY2_EN=!RELAY2_EN;
		}
		while(SW_1==0);  //�ȴ��ͷ�
	}
	//����2 
	if(SW_2==0)  
	{
		delay_ms(100);
		if(SW_2==0)  
		{
			RELAY1_EN=!RELAY1_EN;
			RELAY2_EN=!RELAY2_EN;
		}
		while(SW_2==0);  //�ȴ��ͷ�
	}
}
/*
*******************************************************************************
**��    ��:void SYS_control(void)
**��    ��:״ָ̬ʾ�Ƶĸ���
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
_ee_time_set time_set; 

u8 Temp[2]={0};  
u8 Humi[2]={0};
#if SHT20_ENABLE
//��ȡ�¶�
void ReadTemperature(void)
{
	int temp_y=0;
	u16 Data_M=0;
	u8 Data_L=0; 
	float DataSum;
	IIC_Start();
	IIC_Send_Byte(0x80);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xF3);
	IIC_Wait_Ack();
	///////////////
	do
	{
		delay_us(50);
 	  IIC_Start();
	  IIC_Send_Byte(0x81);
	}
	while(IIC_Wait_Ack()==1);
	////////////////
	Data_M=IIC_Read_Byte(1);
	Data_L=IIC_Read_Byte(1)&0XFC;
	IIC_Read_Byte(0);
	IIC_Stop();

	DataSum=Data_M<<8;
	DataSum=DataSum+Data_L;
	
	//Temp[0]=(int)(DataSum*0.00268127)-46.85+30;
	temp_y=(int)(DataSum*0.00268127)-46.85;
	if(temp_y<=-30)
	{
		Temp[0]=0;
	}
	else
	{
		Temp[0]=(int)(DataSum*0.00268127)-46.85+30;
	}
	
	Temp[1]=DataSum-Temp[0];
	
	POINT_IN.temp=Temp[0];
}



//��ȡʪ��
void ReadHumidity(void)
{
	u16 Data_M=0;
	u8 Data_L=0; 
	float DataSum;
	IIC_Start();
	IIC_Send_Byte(0x80);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xF5);
	IIC_Wait_Ack();
	///////////////
	do
	{
		delay_us(50);
		IIC_Start();
		IIC_Send_Byte(0x81);
	}
	while(IIC_Wait_Ack()==1);
	
	////////////////
	Data_M=IIC_Read_Byte(1);
	Data_L=IIC_Read_Byte(1)&0XFC;
	IIC_Read_Byte(0);
	IIC_Stop();
	
	DataSum=Data_M<<8;
	DataSum=DataSum+Data_L;
	//POINT_IN.hum=DataSum;
	Humi[0]=(int)(DataSum*0.00190735)-6;
	Humi[1]=DataSum-Temp[0];
	
  POINT_IN.hum=Humi[0];
}

#endif

/*
*******************************************************************************
**��    ��:void o3o_cal(void)
**��    ��:״ָ̬ʾ�Ƶĸ���
**��    ��:��
**�� �� ֵ:��
**��������:
**�޸ļ�¼:
**˵    ��:
*******************************************************************************
*/
u16 o3o_cal_time_count=0;
u16 o3o_ss_min=200;
u16 o3o_ss_max=0;
u8  o3o_ss_p=0;
u8 count_t=0;
void o3o_cal(void)
{
	u16 zjcal=0;
	o3o_cal_time_count++;
	//У׼ֵ����
	if((o3o_cal_time_count>50)&&(o3o_cal_time_count<=300))
	{
		if(o3o_ss<200)
		{
			 o3o_ss_max+=o3o_ss;
			 count_t++;
		
			 zjcal=o3o_ss_max/count_t;
			 //����У׼ֵ
			if((zjcal<200)&&(zjcal>40))
			{
				o3o_ss_p=zjcal-30;
			}
	
			if(o3o_cal_time_count==300)
			{
				count_t=0;
				o3o_ss_max=0;
				o3o_ss_min=200;
			}
			
	  }
		//POINT_IN.O3O=o3o_ss-o3o_ss_p;
	}
	else
	{
		//POINT_IN.O3O=o3o_ss-o3o_ss_p;
		//��¼��Сֵ
		if(o3o_ss<o3o_ss_min)
		{
			 o3o_ss_min=o3o_ss;
		}
		//30СʱУ׼���һ��У׼��
		if(o3o_cal_time_count%1800==0)
		{
			if(o3o_ss_min<200)
			{
				o3o_ss_p=o3o_ss_min-30;
			}
		}
	}
	//�������ս��
	if(o3o_ss>o3o_ss_p)
	{
	   POINT_IN.O3O=o3o_ss-o3o_ss_p;
	}
	else//��ֹ��Ե����
	{
		 o3o_ss_p=o3o_ss_p/2;
		 POINT_IN.O3O=o3o_ss-o3o_ss_p;
	}
	
}
//IO��ƽ�Ķ�ȡ
void Relay_upload_back(void) 
{
	if(RELAY_1==1)
	{
		STATU_SYS.M_relay1_flag=1;
	}
	else
	{
		STATU_SYS.M_relay1_flag=0;
	}
	
	if(RELAY_2==1)
	{
		STATU_SYS.M_relay2_flag=1;
	}
	else
	{
		STATU_SYS.M_relay2_flag=0;
	}
	
	if(SW_1==0)
	{
		STATU_SYS.M_sw_level1_flag=1;
	}
	else
	{
		STATU_SYS.M_sw_level1_flag=0;
	}
	
	if(SW_2==0)
	{
		STATU_SYS.M_sw_level2_flag=1;
	}
	else
	{
		STATU_SYS.M_sw_level2_flag=0;
	}

}
//����ϵͳ״̬
void  Update_sys_ststu(void)
{
	if(STATU_SYS.lora_connect_flag==1)
	{
		STATU_SYS.sys_statu|=(0x01<<0);
	}
	else
	{
		STATU_SYS.sys_statu&=(~(0x01<<0));
	}
	
	if(STATU_SYS.M_sw_level2_flag==1)
	{
		STATU_SYS.sys_statu|=(0x01<<1);
	}
	else
	{
		STATU_SYS.sys_statu&=(~(0x01<<1));
	}
	
	if(STATU_SYS.M_sw_level1_flag==1)
	{
		STATU_SYS.sys_statu|=(0x01<<2);
	}
	else
	{
		STATU_SYS.sys_statu&=(~(0x01<<2));
	}
	
	if(STATU_SYS.M_relay1_flag==1)
	{
		STATU_SYS.sys_statu|=(0x01<<3);
	}
	else
	{
		STATU_SYS.sys_statu&=(~(0x01<<3));
	}
	
//	if(STATU_SYS.charge_flag==1)
//	{
//		STATU_SYS.sys_statu|=(0x01<<4);
//	}
//	else
//	{
//		STATU_SYS.sys_statu&=(~(0x01<<4));
//	}
	
	STATU_SYS.sys_statu&=0x08;//��λ����
	STATU_SYS.sys_statu|=(STATU_SYS.run_mode<<4);
	//error
	if(STATU_SYS.bat_low_flag==1)
	{
		STATU_SYS.error_code|=(0x01<<0);
	}
	else
	{
		STATU_SYS.error_code&=(~(0x01<<0));
	}
	///////////////Ӳ��״̬����//////////////////
	if(STATU_SYS.wifi_time>SYS_COM_OUT)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<0));
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<0);
	}
	
	if(STATU_SYS.canl_time>SYS_COM_OUT)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<1));
		//ͨ���쳣ͣ��
		motor_stop();
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<1);
	}
	
	if(STATU_SYS.canr_time>SYS_COM_OUT)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<2));
		//ͨ���쳣ͣ��
		motor_stop();
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<2);
	}
	
	if(STATU_SYS.m6050_time>SYS_COM_OUT)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<3));
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<3);
	}
	
	if(STATU_SYS.zf_num>100)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<4));
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<4);
	}
	
	if(STATU_SYS.adc_fy>100)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<5));
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<5);
	}
	
	if(STATU_SYS.humity_h>1)
	{
		STATU_SYS.sys_statu_show&=(~(0x01<<6));
	}
	else
	{
		STATU_SYS.sys_statu_show|=(0x01<<6);
	}
	
	if((STATU_SYS.motor_r_error_code&0x5fffffff)>0)
	{
		//ͨ���쳣ͣ��
		motor_stop();
		
	}
	
	if((STATU_SYS.motor_l_error_code&0x5fffffff)>0)
	{
		//ͨ���쳣ͣ��
		motor_stop();
		
	}
}



//����ĳ�ʼ��
void Display_init(void)
{
	delay_ms(20);
	if(QF_SYS.run_flag==0)
	{
     Biling_pic(0x5111,1);	
	}
	else
	{
		Biling_pic(0x5111,0);	
	}
	delay_ms(20);
	if(QF_SYS.auto_flag==0)
	{
     Biling_pic(0x5211,1);	
	}
	else
	{
		Biling_pic(0x5211,0);	
	}
	delay_ms(20);
	if(SD_SYS.run_flag==0)
	{
     Biling_pic(0x5213,1);	
	}
	else
	{
		Biling_pic(0x5213,0);	
	}
	delay_ms(20);
	if(JS_SYS.run_flag==0)
	{
     Biling_pic(0x5218,1);	
	}
	else
	{
		Biling_pic(0x5218,0);	
	}
	
	
}
/*ϵͳ��������
0x00������
0x01ǰ��
0x02����
0x03��ת
0x04��ת
0x05����
0x06�³�
0x07��ͣ*/
void sys_run_task(void)
{
	if(STATU_SYS.run_mode==1)
	{
		
	}
	else if(STATU_SYS.run_mode==2)
	{
		
	}
	else if(STATU_SYS.run_mode==3)
	{
		
	}
	else if(STATU_SYS.run_mode==4)
	{
		
	}
	else if(STATU_SYS.run_mode==5)
	{
		cs_time_count++;
		if(cs_time_count>=CS_TIME_SET)
		{
			STATU_SYS.run_mode=0;
			STATU_SYS.sys_speed=0;
			
			Set_addr_l(2,06,40,0);
			delay_ms(10);
			Set_addr_r(3,06,40,0);
			cs_time_count=0;
		}
	}
	else if(STATU_SYS.run_mode==6)
	{
		cs_time_count++;
		if(cs_time_count>=CS_TIME_SET)
		{
			STATU_SYS.run_mode=0;
			STATU_SYS.sys_speed=0;
			
			Set_addr_l(2,06,40,0);
			delay_ms(10);
			Set_addr_r(3,06,40,0);
			cs_time_count=0;
		}
	}
	else if(STATU_SYS.run_mode==7)
	{
		
	}
//	TIM_SetCompare2(TIM8,1700);
//	TIM_SetCompare1(TIM8,1700);
	
	//void Set_addr(u8 addr,u8 cmd,u16 addr_begin,short data)
	
	
}
//ϵͳ��������
void sys_led_task(void)
{
	//ǰ����
	if(STATU_SYS.front_led_pwm<=100)
	{
		if(STATU_SYS.front_led_pwm==0)
		{
			TIM_SetCompare4(TIM8,0);
			TIM_SetCompare1(TIM3,0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		}
		else
		{
			TIM_SetCompare4(TIM8,9*(u16)STATU_SYS.front_led_pwm);
			TIM_SetCompare1(TIM3,9*(u16)STATU_SYS.front_led_pwm);
		}
	}
	//������
	if(STATU_SYS.back_led_pwm<=100)
	{
		if(STATU_SYS.back_led_pwm==0)
		{
			TIM_SetCompare3(TIM8,0);
			TIM_SetCompare2(TIM3,0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_8);
			GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		}
		else
		{
			TIM_SetCompare3(TIM8,9*(u16)STATU_SYS.back_led_pwm);
			TIM_SetCompare2(TIM3,9*(u16)STATU_SYS.back_led_pwm);
		}
	}
	//��������
	if(STATU_SYS.other_led_pwm<=100)
	{
		if(STATU_SYS.other_led_pwm==0)
		{
			TIM_SetCompare2(TIM8,0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		}
		else
		{
			TIM_SetCompare2(TIM8,9*(u16)STATU_SYS.other_led_pwm);
		}
	}
	
}
//�����ļ���
void bat_level_cal(void)
{
	if(STATU_SYS.adc_bat_vol>=410*BAT_NUM)
	{
		STATU_SYS.bat_vol=100;
	}
	else if(STATU_SYS.adc_bat_vol>=395*BAT_NUM)
	{
		STATU_SYS.bat_vol=90;
	}
	else if(STATU_SYS.adc_bat_vol>=385*BAT_NUM)
	{
		STATU_SYS.bat_vol=80;
	}
	else if(STATU_SYS.adc_bat_vol>=379*BAT_NUM)
	{
		STATU_SYS.bat_vol=70;
	}
	else if(STATU_SYS.adc_bat_vol>=373*BAT_NUM)
	{
		STATU_SYS.bat_vol=60;
	}
	else if(STATU_SYS.adc_bat_vol>=368*BAT_NUM)
	{
		STATU_SYS.bat_vol=50;
	}
	else if(STATU_SYS.adc_bat_vol>=365*BAT_NUM)
	{
		STATU_SYS.bat_vol=40;
	}
	else if(STATU_SYS.adc_bat_vol>=362*BAT_NUM)
	{
		STATU_SYS.bat_vol=30;
	}
	else if(STATU_SYS.adc_bat_vol>=358*BAT_NUM)
	{
		STATU_SYS.bat_vol=20;
	}
	else if(STATU_SYS.adc_bat_vol>=351*BAT_NUM)
	{
		STATU_SYS.bat_vol=10;
	}
	else if(STATU_SYS.adc_bat_vol>=345*BAT_NUM)
	{
		STATU_SYS.bat_vol=5;
	}
	else
	{
		STATU_SYS.bat_vol=0;
		
	}
	
}

//��ѯ�����Ԫ�ص�λ��
u8 findElement(u8 arr[], u8 size, u8 target) {
	u8 i=0;
    for ( i = 1; i < size; i++) {
        if (arr[i] == target) {
            return i; // ����Ԫ�ص�����λ��
        }
    }
    return 0; // ���δ�ҵ����򷵻�0
}

void motor_stop(void)
{
	STATU_SYS.run_mode=0;
	STATU_SYS.sys_speed=0;
	Set_addr_l(2,06,174,0);
	delay_ms(10);
	Set_addr_r(3,06,174,0);
	
	
}

/******************* (C) COPYRIGHT 2012 yunyi Team *****END OF FILE***********/

	






