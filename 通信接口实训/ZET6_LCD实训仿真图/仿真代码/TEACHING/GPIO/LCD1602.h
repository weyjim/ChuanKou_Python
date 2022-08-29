#ifndef __lcd1602_H
#define __lcd1602_H	 
#include "sys.h"

//1602Һ��ָ��/����ѡ������
#define	LCD_RS_Set()	GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define	LCD_RS_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_0)

//1602Һ����д����
#define	LCD_RW_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define	LCD_RW_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_1)

//1602Һ��ʹ������
#define	LCD_EN_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define	LCD_EN_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_2)

//1602Һ�����ݶ˿�	PD0~7
#define	DATAOUT(x)	GPIO_Write(GPIOC, x)
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);
void LCD1602_ClearScreen(void);
void GPIO_Configuration(void);

void delay_1ms(unsigned char x);  
void delay_s(int j);

#endif
