#ifndef __lcd1602_H
#define __lcd1602_H	 
#include "sys.h"

//1602Һ��ָ��/����ѡ������
#define	LCD_RS_Set()	GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define	LCD_RS_Clr()	GPIO_ResetBits(GPIOD, GPIO_Pin_15)

//1602Һ����д����
#define	LCD_RW_Set()	GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define	LCD_RW_Clr()	GPIO_ResetBits(GPIOD, GPIO_Pin_14)

//1602Һ��ʹ������
#define	LCD_EN_Set()	GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define	LCD_EN_Clr()	GPIO_ResetBits(GPIOD, GPIO_Pin_13)

//1602Һ�����ݶ˿�	P0~7
#define	DATAOUT(x)	GPIO_Write(GPIOD, x)
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);
void LCD1602_ClearScreen(void);

void delay_1ms(unsigned char x);  
void delay_s(int loop1);


#endif
