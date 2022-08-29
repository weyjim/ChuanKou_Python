#include "timer.h"
#include "lcd1602.h"

void Timerx_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}



u8 NT[16];
int Rcount=0;
int A=0;
int B=0;

void TIM3_IRQHandler(void)   
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET)  
  {
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		Rcount++;
		if(Rcount==60)
		{
			Rcount=0;
			B++;
			if(B==60)
		  {
				B=0;
				A++;
				if(A==24)
				{
					A=0;
				}
			}
		}
		sprintf((char*)NT,"%2d:%2d:%2d",A,B,Rcount);
		LCD1602_Show_Str(1,1,"               "); 
		LCD1602_Show_Str(1,1,NT);
		printf("当前时间：%2d:%2d:%2d\r\n",A,B,Rcount);
	}
}


