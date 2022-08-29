#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "usart.h"
#include "lcd1602.h"
#include "timer.h"
#include "bsp_beep.h"
#include "stdio.h"

int S_Hr=0;
int S_Min=0;
int S_Rcount=50;

vu8 flag=0;	//标志位设置为0
vu8 count=0;//切换时分秒
u8 ST[16];
int music=0;

int main(void)
{
	delay_init();
	NVIC_Configuration();
	uart_init(9600);
	KEY_Init();
	BEEP_Init();
	GPIO_Configuration();
	LCD1602_Init();
	Timerx_Init(1999,35999);
	
	delay_ms(5000);
	while(1)
 {
			if(flag==1)
		{
			if((S_Rcount+S_Min*60+S_Hr*3600)==(Rcount+B*60+A*3600))
			{
				TIM_Cmd(TIM3,DISABLE);
				LCD1602_Show_Str(1,0,(u8*)"                ");
				LCD1602_Show_Str(1,0,(u8*)"TIMER ALERT");
				printf("TIMER ALERT");
				printf("++++++++++++++++++++++++++++++++++++++++++++++");
				printf("\r\n");
				if(music==0)
				{   
					play_music();	//播放第一首音乐
					if(KEY0==0)
					{
						GPIO_SetBits(GPIOA,GPIO_Pin_4);
					}
				}
				if(music==1)
				{
					play_music2();
					if(KEY0==0)
					{
						GPIO_SetBits(GPIOA,GPIO_Pin_4);
					}
				}
					S_Hr=0;
					S_Min=0;
					S_Rcount=0;
					flag=0;
					Rcount=0;
					count=0;
			}
		}
		else
		{
			if(KEY0==0)//启动音乐
			{
				LCD1602_Show_Str(1,0,(u8*)"            ");
//				LCD1602_Show_Str(1,0,"TIME OPEN!");
				LCD1602_Show_Str(1,1,(u8*)"             ");
				LCD1602_Show_Str(1,1,ST);
				TIM_Cmd(TIM3,DISABLE);
				flag=1;
			}
			else 	if(KEY1==0)//增加设定时间
			{
				sprintf((char*)ST,"%2d:%2d:%2d",S_Hr,S_Min,S_Rcount);
				LCD1602_Show_Str(1,1,(u8*)"             ");
				LCD1602_Show_Str(1,1,ST);
//				LCD1602_Show_Str(1,0,"over Time:");
				LCD1602_Show_Str(1,0,(u8*)"             ");
				LCD1602_Show_Str(1,0,ST);
				if(count==0)
				{
					S_Rcount+=1;
				}
				if(count==1)
				{
					S_Min+=1;
				}
				if(count==2)
				{
					S_Hr+=1;
				}
				printf("SET TIME:%2d:%2d:%2d\r\n",S_Hr,S_Min,S_Rcount);
				
			}

			else if(KEY2==1)//减
			{
				sprintf((char*)ST,"%2d:%2d:%2d:",S_Hr,S_Min,S_Rcount);
				LCD1602_Show_Str(1,1,(u8*)"             ");
				LCD1602_Show_Str(1,1,ST);
				LCD1602_Show_Str(1,0,(u8*)"Over Time:");
				if(count==0)
				{
					S_Rcount-=1;
				}
				if(count==1)
				{
					S_Min-=1;
				}
				if(count==2)
				{
					S_Hr-=1;
				}
			}
			
				else 	if(KEY6==1)//调节时分秒之间切换
				{
					count++;
					if(count==3)
					{
						count=0;
					}
				}
				else if(KEY5==1)//切歌
				{
					sprintf((char*)ST,"%2d:%2d:%2d:",S_Hr,S_Min,S_Rcount);
					LCD1602_Show_Str(1,1,(u8*)"             ");
					LCD1602_Show_Str(1,1,ST);
					LCD1602_Show_Str(1,0,(u8*)"Switch songs");
					 music++;
					 if(music==2)	
					 {
						 music=0;
					 }
				}
			}
	}
}

