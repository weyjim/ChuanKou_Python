#include "lcd1602.h"
#include "gpio.h"
#include "delay.h"

void delay(int j)
{
	int i;
	delay_init();
	for(i=1;i<j*200;i++)
	{
		delay_ms(1000);
	}
}


/* �ȴ�Һ��׼���� */
void LCD1602_Wait_Ready(void)
{
	u8 sta;
	
	DATAOUT(0xff);
	LCD_RS_Clr();
	LCD_RW_Set();
	do
	{
		LCD_EN_Set();
		delay(2);	//��ʱ5ms���ǳ���Ҫ
 		sta = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);//��ȡ״̬��
		LCD_EN_Clr();
	}while(sta & 0x80);//bit7����1��ʾҺ����æ���ظ����ֱ�������0Ϊֹ
}

/* ��LCD1602Һ��д��һ�ֽ����cmd-��д������ֵ */
void LCD1602_Write_Cmd(u8 cmd)
{
	LCD1602_Wait_Ready();
	LCD_RS_Clr();
	LCD_RW_Clr();
	DATAOUT(cmd);
	LCD_EN_Set();
	LCD_EN_Clr();
}

/* ��LCD1602Һ��д��һ�ֽ����ݣ�dat-��д������ֵ */
void LCD1602_Write_Dat(u8 dat)
{
	LCD1602_Wait_Ready();
	LCD_RS_Set();
	LCD_RW_Clr();
	DATAOUT(dat);
	LCD_EN_Set();
	LCD_EN_Clr();
}

/* ���� */
void LCD1602_ClearScreen(void)
{
	LCD1602_Write_Cmd(0x01);
	
}

/* ������ʾRAM��ʼ��ַ���༴���λ�ã�(x,y)-��Ӧ��Ļ�ϵ��ַ����� */
void LCD1602_Set_Cursor(u8 x, u8 y)
{
	u8 addr;
	
	if (y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_Cmd(addr | 0x80);
}

/* ��Һ������ʾ�ַ�����(x,y)-��Ӧ��Ļ�ϵ���ʼ���꣬str-�ַ���ָ�� */
void LCD1602_Show_Str(u8 x, u8 y, u8 *str)
{
	LCD1602_Set_Cursor(x, y);
	while(*str != '\0')
	{
		LCD1602_Write_Dat(*str++);
	}
}

/* ��ʼ��1602Һ�� */
void LCD1602_Init(void)
{
	LCDGPIO_Init();
	LCD1602_Write_Cmd(0x38);	//16*2��ʾ��5*7����8λ���ݿ�
	LCD1602_Write_Cmd(0x0c);	//����ʾ�����ر�
	LCD1602_Write_Cmd(0x06);	//���ֲ�������ַ�Զ�+1
	LCD1602_Write_Cmd(0x01);	//����
	
}

