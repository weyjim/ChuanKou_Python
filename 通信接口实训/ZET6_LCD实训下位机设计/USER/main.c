#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "gpio.h"
#include "lcd1602.h"
#include "timer.h"
#include "24l01.h"
#include "spi.h"
#include "delay.h"
#include "dht11.h"

extern int Rcount,minute,hour;
extern u8 RX_1;
int Stop_Rcount=20,Stop_minute=0,Stop_hour=0;
u8 LCD_Display_Stop[16];
u8 temperature[8];


u8 RunSYS=0;
u8 key,mode;
u8 tmp_buf[64];
u8 nrf_buf1,nrf_buf2,nrf_buf3;
void Init_Buffer (unsigned char *P,unsigned int Count,unsigned char Type);
void nRF24L01(void);

void KEY_Scan(void);
void BEEP_Alert(void);
void DHT11_Scan(void);

int main(void)
{
	uart_init(9600);
	Timerx_Init(1999,3599);		//计数一次1s
	NVIC_Configuration();
	
	BEEP_Init();
	LCD1602_Init();
	NRF24L01_Init();		
	Dht11_Init();
	
	while(1)
	{
//		printf("Time(%2d:%2d:%2d)\n",hour,minute,Rcount);
		printf("Tunnel1: 19\n");
		printf("Tunnel2: 89\n");
//		KEY_Scan();
//		BEEP_Alert();
//		DHT11_Scan();			
		nRF24L01();
		delay_s(10);
		
	}
}

void DHT11_Scan()				//判断Dht11_Start()是否为0，如果为0则调用Dht11_Read函数，并输出温湿度。
{
	if(Dht11_Start()==0)
	{
		Dht11_Read(temperature);
		
		LCD1602_Show_Str(1, 0, (u8*)"               ");
		LCD1602_Show_Str(1, 0, temperature);			//显示温度
	}
	
}

void KEY_Scan()
{
	if(KEY1==0)
	{
		delay_1ms(10);					//软件消抖
		if(KEY1==0)
		{
			Stop_Rcount++;				//秒数+
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY1==0);				//抬手检测
		}
	}
	else if(KEY2==0)			
	{
		delay_1ms(10);					//软件消抖
		if(KEY2==0)
		{
			Stop_Rcount--;				//秒数-
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY2==0);
		}
	}
	else if(KEY3==0)
	{
		delay_1ms(10);					//软件消抖
		if(KEY3==0)
		{
			Stop_minute++;				//分钟+
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY3==0);
		}
	}
	else if(KEY4==0)
	{
		delay_1ms(10);					//软件消抖
		if(KEY4==0)
		{
			Stop_minute--;				//分钟-
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY4==0);
		}
	}
	else if(KEY5==0)
	{
		delay_1ms(10);					//软件消抖
		if(KEY5==0)
		{
			Stop_hour++;				//小时++
			
			sprintf((char*)LCD_Display_Stop,"STOP++%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY5==0);
		}
	}
	else if(KEY6==0)
	{
		delay_1ms(10);					//软件消抖
		if(KEY6==0)
		{
			Stop_hour--;				//小时--
			
			sprintf((char*)LCD_Display_Stop,"STOP--%2d:%2d:%2d",Stop_hour,Stop_minute,Stop_Rcount);
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, LCD_Display_Stop);			//显示更改的时间
			
			while(KEY6==0);
		}
	}
}


void BEEP_Alert()
{
	if(Stop_Rcount==Rcount && Stop_minute==minute && Stop_hour==hour)
	{
		while(1)
		{
			BEEP_1;
			delay_s(1);
			BEEP_0;
			delay_s(1);
			printf("Time reached,play music!\n");
			
			if(KEY1==0) 		//KEY1取消报警（长按）
			{				
				delay_1ms(10);
				if(KEY1==0)
				{
					while(KEY1==0);
					break;
				}
			}	
		}
	}
}


void nRF24L01()
{
	u16 t,len;
	mode=10;
	if(mode==0)//RX模式
	{
		Init_Buffer(tmp_buf,64,0);//初始化缓冲区
		LCD1602_Show_Str(1, 0, (u8*)"               ");
		LCD1602_Show_Str(1, 0, tmp_buf);			
		NRF24L01_RX_Mode();		

		RunSYS=0;
		
		while(NRF24L01_Check())	//检查NRF24L01是否在位.	
		{
			LCD1602_Show_Str(1, 0, (u8*)"               ");
			LCD1602_Show_Str(1, 0, (u8*)"NRF24L01 Error");				
			delay_1ms(200);
		}								   
		printf("NRF24L01 OK");
		
		while(RunSYS==0)
		{				
			if(KEY5==0)			//KEY5取消接收模式
			{
				delay_1ms(10);
				mode=1;
				RunSYS=0xAA;
			}
			
			if(NRF24L01_RxPacket(tmp_buf)==0)	//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD1602_Show_Str(1, 0, (u8*)"               ");
				LCD1602_Show_Str(1, 0, (u8*)"  Received DATA");					//和无线串口模块通信的时候，无线数据缓冲区的第一字节是数据帧有效数据长度。  		
			}else delay_us(100);	   
			t++;
			if(t==10000)//大约1s钟改变一次状态
			{
				t=0;
				printf("24L01已接收\n");
			} 				    
		};	
		
	}
	else if(mode==1)//TX模式
	{
		Init_Buffer(tmp_buf,64,0);//初始化缓冲区
		
		LCD1602_Show_Str(1, 0, (u8*)"               ");
		LCD1602_Show_Str(1, 0, (u8*)"  24L01 TX_Mode");	
		
		NRF24L01_TX_Mode();
		
		mode=' ';//从空格键开始  
		
		tmp_buf[0]=31;//发送接收的第一字节作为描述有效数据长度字节
				
		RunSYS=0;
		
		while(RunSYS==0)
		{				
			if(KEY6==0)				//KEY6取消发送模式
			{
				delay_1ms(10);
				mode=0;
				RunSYS=0x55;								
			}

			
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				LCD1602_Show_Str(1, 0, (u8*)"               ");
				LCD1602_Show_Str(1, 0, (u8*)"  Sended DATA:");	
				for(t=0;t<29;t++)
				{
					key++;
					if(key>('~'))key=' ';//此处用来填充一下缓冲区ASCII
					tmp_buf[t+1]=00000001;	
				}
				mode++; 
				if(mode>'~')mode=' '; 
				tmp_buf[0]=31;		//加入换行符号	 
				
				tmp_buf[30]=0x0D;	//加入换行符号	 
				tmp_buf[31]=0x0A;	//加入回车符号	
				tmp_buf[32]=0x00;	//加入结束显示符号				
				//sprintf(tmp_buf,"%d\r\n",key);	
			}
			printf("24L01已发送\n");
			delay_s(10);				    	 
		}
	}
	else
	{
		if(USART_RX_STA&0x8000)
		{ 
			len=USART_RX_STA&0x3f; //得到此次接收到的数据长度
			printf("\r\n Recived:\r\n\r\n");
			printf("\r\n\r\n"); //插入换行
			
			nrf_buf1=USART_RX_BUF[0];
			nrf_buf2=USART_RX_BUF[1];
			nrf_buf3=USART_RX_BUF[2];
			
			printf("%d\n",nrf_buf1);
			printf("%d\n",nrf_buf2);
			printf("%d\n",nrf_buf3);
			
			USART_RX_STA=0;
		}
		else
		{ 
			delay_s(5); 
		}
	}
}

void Init_Buffer (unsigned char *P,unsigned int Count,unsigned char Type) 
{
	unsigned int i;

	if(Type==0)
	{
		for(i=0;i<Count;i++)*P++=0x0;
	}
	else
	{
		for(i=0;i<Count;i++)*P++=0xFF;
	}

}

