#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "timer.h"
#include "usart.h"
#include "lcd1602.h"

u8 LCD_Display_Stop[16];
extern int Rcount,minute,hour;
int Stop_Rcount=10,Stop_minute=0,Stop_hour=0;

void BEEP_Alert(void);

void test_1(void);
void test_2(void);
void test_3(void);

int main(void)
{
	BEEP_Init();
	KEY_Init();
	NVIC_Configuration();
	Timerx_Init(999,4999);		//计数一次1s
	uart_init(9600);
	LCDGPIO_Init();
	LCD1602_Init();
	
	test_1();
}

void test_1()
{
	LCD1602_Show_Str(1, 0, (u8*)"                  ");
	LCD1602_Show_Str(1, 0, (u8*)"   WEY    ");
	TIM_Cmd(TIM3,ENABLE);
	while(1)
	{
//		if(KEY0==0)
//		{
//			LCD1602_Show_Str(1, 0, (u8*)"                  ");
//			LCD1602_Show_Str(1, 0, (u8*)" TIMER START!");
//			
//			TIM_Cmd(TIM3,ENABLE);
//			
//			while(KEY0==0);
//		}
		if(KEY1==0)			//定时时间++
		{
			Stop_Rcount++;
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"                ");
			LCD1602_Show_Str(1, 0, (u8*)"19 degree 61 per");			//显示更改的时间
			
			while(KEY1==0);				
		}
		else if(KEY2==0)		//定时时间--
		{
			Stop_Rcount--;
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8 *)"              ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);	
			
			while(KEY2==0);				
		}
		
		BEEP_Alert();

	}
}

void test_2()
{
	LCD1602_Show_Str(1, 0, (u8*)"                  ");
	LCD1602_Show_Str(1, 0, (u8*)"   HELLO    ");
	delay(1000);
	LCD1602_Show_Str(1, 0, (u8*)"                  ");	
	LCD1602_Show_Str(1, 0, (u8*)"   TEST_2   ");
	
	while(1)
	{
		if(KEY0==0)
		{
			LCD1602_Show_Str(1, 0, (u8*)"                  ");
			LCD1602_Show_Str(1, 0, (u8*)" TIMER START!");
			TIM_Cmd(TIM3,ENABLE);
			while(KEY0==0);
		}
		else if(KEY1==0)
		{
			LCD1602_Show_Str(1, 0, (u8*)"                  ");
			LCD1602_Show_Str(1, 0, (u8*)"  TIMER STOP!");
			TIM_Cmd(TIM3,DISABLE);
			while(KEY1==0);
		}
		else if(KEY2==0)
		{
			Rcount=0,minute=0,hour=0;
			sprintf((char*)LCD_Display_Stop,"%2d:%2d:%2d",hour,minute,Rcount);
			LCD1602_Show_Str(1,1,LCD_Display_Stop);
			while(KEY2==0);
		}
	}
}

void test_3()
{
	char KEY_Swtich=0;
	TIM_Cmd(TIM3,ENABLE);	
	
	while(1)
	{
		if(KEY0==0)
		{
			KEY_Swtich++;
			if(KEY_Swtich>=3)
				KEY_Swtich=0;
			while(KEY0==0);
		}
		else if(IR0==1)
		{
			TIM_Cmd(TIM3,DISABLE);
			LCD1602_Show_Str(1, 0, (u8*)"                  ");
			LCD1602_Show_Str(1, 0, (u8*)"   HELLO    ");
			delay(1000);
			TIM_Cmd(TIM3,ENABLE);			
			
			while(IR0==1);
		}
		
		switch(KEY_Swtich)
		{
			case 0:
				TIM_Cmd(TIM3,ENABLE);
				break;
			case 1: 
				TIM_Cmd(TIM3,DISABLE);
				break;
			case 2: 
				Rcount=0,minute=0,hour=0;
				sprintf((char*)LCD_Display_Stop,"%2d:%2d:%2d",hour,minute,Rcount);
				LCD1602_Show_Str(1,1,LCD_Display_Stop);
		}	
		
	}
}


void BEEP_Alert()
{
	int i;
	if(Stop_Rcount==Rcount && Stop_minute==minute && Stop_hour==hour)		//闹钟检测
	{
		TIM_Cmd(TIM3,DISABLE);
		LCD1602_Show_Str(1, 0, (u8 *)"                  ");
		LCD1602_Show_Str(1, 1, (u8 *)"                  ");
		LCD1602_Show_Str(1, 0, (u8 *)"   TIMER ALERT");
		
		for(i=0;i<5;i++)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);				//蜂鸣器警报
			delay(100);
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
			delay(100);
		}
		while(1);
	}
}
