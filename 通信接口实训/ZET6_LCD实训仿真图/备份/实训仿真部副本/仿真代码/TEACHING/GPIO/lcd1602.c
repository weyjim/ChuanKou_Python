#include "stm32f10x.h"
#include "lcd1602.h"
#include "stdio.h"
void GPIO_Configuration(void)
{
        GPIO_InitTypeDef        GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
        GPIO_Init(GPIOC, &GPIO_InitStructure);                                //��ʼ��GPIOD0~7
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO���ٶ�Ϊ50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);                                //��ʼ��GPIB15,14,13
}
void delay_1ms(unsigned char x)   //��� -0.651041666667us
{
    unsigned char a,b,c;
	for(c=x;c>0;c--)
    {
		for(b=102;b>0;b--)
        for(a=3;a>0;a--);
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
            delay_1ms(5);        //��ʱ5ms���ǳ���Ҫ
            sta = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);//��ȡ״̬��
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
    //printf("%d",cmd);
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
    GPIO_Configuration();
    LCD1602_Write_Cmd(0x38);        //16*2��ʾ��5*7����8λ���ݿ�
    LCD1602_Write_Cmd(0x0c);        //����ʾ�����ر�
    LCD1602_Write_Cmd(0x06);        //���ֲ�������ַ�Զ�+1
    LCD1602_Write_Cmd(0x01);        //����
              
  
}

