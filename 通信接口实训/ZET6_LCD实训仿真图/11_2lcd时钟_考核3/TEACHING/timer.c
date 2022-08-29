#include "timer.h"
#include "gpio.h"
#include "stdio.h"
#include "lcd1602.h"

u8 LCD_Display[16];
int Rcount=0,minute=0,hour=0;

void Timerx_Init(u16 arr , u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//TIM3时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//初始化定时器
	TIM_TimeBaseStructure.TIM_Period = arr;				//自动重装寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;			//时钟预分频，作为定时器的时钟
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分割系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);
	
	//设置中断类型
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);		//更新中断
	
	
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
}

void NVIC_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

	//中断服务函数
void TIM3_IRQHandler(void)									
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);			//清除TIM3更新中断标志位 
		Rcount++;
		if(Rcount>=60)			//判断在做工程时尽量不放在中断里ff
		{
			Rcount=0;
			minute++;
			if(minute>=60)
			{
				minute=0;
				hour++;
				if(hour>=24)
				{
					hour=0;
				}
			}
		}
		sprintf((char*)LCD_Display,"%2d:%2d:%2d",hour,minute,Rcount);
		LCD1602_Show_Str(1, 1, (u8 *)"                  ");
		LCD1602_Show_Str(1, 1, LCD_Display);
	}
}

