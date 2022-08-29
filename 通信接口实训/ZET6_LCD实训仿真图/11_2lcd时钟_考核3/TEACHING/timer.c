#include "timer.h"
#include "gpio.h"
#include "stdio.h"
#include "lcd1602.h"

u8 LCD_Display[16];
int Rcount=0,minute=0,hour=0;

void Timerx_Init(u16 arr , u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//TIM3ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//��ʼ����ʱ��
	TIM_TimeBaseStructure.TIM_Period = arr;				//�Զ���װ�Ĵ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;			//ʱ��Ԥ��Ƶ����Ϊ��ʱ����ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷָ�ϵ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);
	
	//�����ж�����
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);		//�����ж�
	
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
}

void NVIC_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

	//�жϷ�����
void TIM3_IRQHandler(void)									
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);			//���TIM3�����жϱ�־λ 
		Rcount++;
		if(Rcount>=60)			//�ж���������ʱ�����������ж���ff
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

