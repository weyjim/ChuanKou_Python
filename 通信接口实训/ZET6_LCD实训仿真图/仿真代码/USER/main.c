#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "usart.h"
#include "lcd1602.h"
#include "timer.h"
#include "bsp_beep.h"
#include "stdio.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)  //����        1
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)  //����ʱ��        2
#define KEY4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)  //����ʱ��        3
#define KEY5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)  //�и�       4
#define KEY6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)  //����ʱ����֮���л�    5
//#define KEY12 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
//#define KEY13 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
//#define KEY14 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
//#define KEY_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

int S_Hr=0;
int S_Min=0;
int S_Rcount=0;

extern int Rcount,minute,hour;
int Stop_Rcount=20,Stop_minute=0,Stop_hour=0;
u8 LCD_Display_Stop[16];


vu8 flag=0;	//��־λ����Ϊ0
vu8 count=0;//�л�ʱ����
u8 ST[16];
int music=0;

void KEY_Scan(void);


int main(void)
{
	delay_init();
	NVIC_Configuration();
	uart_init(9600);
	KEY_Init();
	BEEP_Init();
	GPIO_Configuration();
	LCD1602_Init();
	Timerx_Init(999,4999);
	
	delay_ms(5000);
	while(1)
	{
		KEY_Scan();
		delay_s(10);
	}
}

void KEY_Scan()
{
	if(KEY1==0)
	{
		delay_1ms(10);					//�������
		if(KEY1==0)
		{
			Stop_Rcount++;				//����+
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY1==0);				//̧�ּ��
		}
	}
	else if(KEY2==0)			
	{
		delay_1ms(10);					//�������
		if(KEY2==0)
		{
			Stop_Rcount--;				//����-
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY2==0);
		}
	}
	else if(KEY3==0)
	{
		delay_1ms(10);					//�������
		if(KEY3==0)
		{
			Stop_minute++;				//����+
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY3==0);
		}
	}
	else if(KEY4==0)
	{
		delay_1ms(10);					//�������
		if(KEY4==0)
		{
			Stop_minute--;				//����-
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY4==0);
		}
	}
	else if(KEY5==0)
	{
		delay_1ms(10);					//�������
		if(KEY5==0)
		{
			Stop_hour++;				//Сʱ++
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY5==0);
		}
	}
	else if(KEY6==0)
	{
		delay_1ms(10);					//�������
		if(KEY6==0)
		{
			Stop_hour--;				//Сʱ--
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//��ʾ���ĵ�ʱ��
			
			while(KEY6==0);
		}
	}
}

//void user()
//{
//		if(flag==1)
//		{
//			if((S_Rcount+S_Min*60+S_Hr*3600)==(Rcount+B*60+A*3600))
//			{
//				TIM_Cmd(TIM3,DISABLE);
//				LCD1602_Show_Str(1,0,(u8*)"                ");
//				LCD1602_Show_Str(1,0,(u8*)"TIME OVER!");
//				printf("TIME OVER");
//				printf("++++++++++++++++++++++++++++++++++++++++++++++");
//				printf("\r\n");
//				if(music==0)
//				{   
//					play_music();	//���ŵ�һ������
//					if(KEY0==0)
//					{
//						GPIO_SetBits(GPIOA,GPIO_Pin_4);
//					}
//				}
//				if(music==1)
//				{
//					play_music2();
//					if(KEY0==0)
//					{
//						GPIO_SetBits(GPIOA,GPIO_Pin_4);
//					}
//				}
//					S_Hr=0;
//					S_Min=0;
//					S_Rcount=0;
//					flag=0;
//					Rcount=0;
//					count=0;
//			}
//		}
//		else
//		{
//			if(KEY2==0)//����
//			{
//				LCD1602_Show_Str(1,0,(u8*)"            ");
////				LCD1602_Show_Str(1,0,"TIME OPEN!");
//				LCD1602_Show_Str(1,1,(u8*)"             ");
//				LCD1602_Show_Str(1,1,ST);
//				TIM_Cmd(TIM3,ENABLE);
//				flag=1;
//			}
//			if(KEY3==0)//�����趨ʱ��
//			{
//				sprintf((char*)ST,"%2d:%2d:%2d",S_Hr,S_Min,S_Rcount);
//				LCD1602_Show_Str(1,1,(u8*)"             ");
//				LCD1602_Show_Str(1,1,ST);
////				LCD1602_Show_Str(1,0,"over Time:");
//				LCD1602_Show_Str(1,0,(u8*)"             ");
//				LCD1602_Show_Str(1,0,ST);
//				if(count==0)
//				{
//					S_Rcount+=1;
//				}
//				if(count==1)
//				{
//					S_Min+=1;
//				}
//				if(count==2)
//				{
//					S_Hr+=1;
//				}
//				printf("SET TIME:%2d:%2d:%2d\r\n",S_Hr,S_Min,S_Rcount);
//				
//			}

//			if(KEY4==1)//��
//			{
//				sprintf((char*)ST,"%2d:%2d:%2d:",S_Hr,S_Min,S_Rcount);
//				LCD1602_Show_Str(1,1,(u8*)"             ");
//				LCD1602_Show_Str(1,1,ST);
//				LCD1602_Show_Str(1,0,(u8*)"Over Time:");
//				if(count==0)
//				{
//					S_Rcount-=1;
//				}
//				if(count==1)
//				{
//					S_Min-=1;
//				}
//				if(count==2)
//				{
//					S_Hr-=1;
//				}
//			}
//			
//					if(KEY6==1)//����ʱ����֮���л�
//				{
//					count++;
//					if(count==3)
//					{
//						count=0;
//					}
//				}
//				if(KEY5==1)//�и�
//				{
//					sprintf((char*)ST,"%2d:%2d:%2d:",S_Hr,S_Min,S_Rcount);
//					LCD1602_Show_Str(1,1,(u8*)"             ");
//					LCD1602_Show_Str(1,1,ST);
//					LCD1602_Show_Str(1,0,(u8*)"Switch songs");
//					 music++;
//					 if(music==2)	
//					 {
//						 music=0;
//					 }
//				}
//			}
//}


