#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
//IO��������
#define DHT11_IO_IN()  {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=8<<24;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=3<<24;}
////IO��������											   
#define	DHT11_DQ_OUT PAout(6) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PAin(6)  //���ݶ˿�	PA0 

extern u8 temperature;  	    
extern u8 humidity; 

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















