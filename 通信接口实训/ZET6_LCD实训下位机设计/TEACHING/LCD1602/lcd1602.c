#include "stm32f10x.h"
#include "lcd1602.h"
#include "stdio.h"
void GPIO_Configuration(void)
{
        GPIO_InitTypeDef        GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
									GPIO_Pin_6|GPIO_Pin_7 | GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO口速度为50MHz
        GPIO_Init(GPIOD, &GPIO_InitStructure);                                //初始化GPIOD0~7
}
void delay_1ms(u8 x)   //误差 -0.651041666667us	软件延时
{
    u8 a,b,c;
	for(c=x;c>0;c--)
		for(b=102;b>0;b--)
			for(a=3;a>0;a--);
}

void delay_s(int loop1)
{
	int i;
	for(i=0;i<loop1;i++)
		delay_1ms(100);
}

/* 等待液晶准备好 */
void LCD1602_Wait_Ready(void)
{
        u8 sta;
        DATAOUT(0xff);
        LCD_RS_Clr();
        LCD_RW_Set();
        do
        {
            LCD_EN_Set();
            delay_1ms(10);        //延时5ms，非常重要
            sta = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);//读取状态字
            LCD_EN_Clr();
        }while(sta & 0x80);//bit7等于1表示液晶正忙，重复检测直到其等于0为止
}

/* 向LCD1602液晶写入一字节命令，cmd-待写入命令值 */
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

/* 向LCD1602液晶写入一字节数据，dat-待写入数据值 */
void LCD1602_Write_Dat(u8 dat)
{
        LCD1602_Wait_Ready();
        LCD_RS_Set();
        LCD_RW_Clr();
        DATAOUT(dat);
        LCD_EN_Set();
        LCD_EN_Clr();
}

/* 清屏 */
void LCD1602_ClearScreen(void)
{
        LCD1602_Write_Cmd(0x01);
}

/* 设置显示RAM起始地址，亦即光标位置，(x,y)-对应屏幕上的字符坐标 */
void LCD1602_Set_Cursor(u8 x, u8 y)
{
        u8 addr;
        
        if (y == 0)
                addr = 0x00 + x;
        else
                addr = 0x40 + x;
        LCD1602_Write_Cmd(addr | 0x80);
}

/* 在液晶上显示字符串，(x,y)-对应屏幕上的起始坐标，str-字符串指针 */
void LCD1602_Show_Str(u8 x, u8 y, u8 *str)
{
        LCD1602_Set_Cursor(x, y);
        while(*str != '\0')
        {
           LCD1602_Write_Dat(*str++);
        }
}

/* 初始化1602液晶 */
void LCD1602_Init(void)
{
    GPIO_Configuration();
    LCD1602_Write_Cmd(0x38);        //16*2显示，5*7点阵，8位数据口
    LCD1602_Write_Cmd(0x0c);        //开显示，光标关闭
    LCD1602_Write_Cmd(0x06);        //文字不动，地址自动+1
    LCD1602_Write_Cmd(0x01);        //清屏
              
  
}

