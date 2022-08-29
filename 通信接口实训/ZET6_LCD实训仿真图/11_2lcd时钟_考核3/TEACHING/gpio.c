#include "gpio.h"
#include "stm32f10x.h"


void KEY_Init(void)		
{
	GPIO_InitTypeDef   GPIO_InitStructure;				
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure. GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure. GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.	GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void BEEP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//时钟使能
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//结构体变量设置
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//结构体变量写入初始化函数
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	
}

void IR_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//时钟使能
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;				//结构体变量设置
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//结构体变量写入初始化函数

}

void LCDGPIO_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	TIM_Cmd(TIM3,DISABLE);	
}
