#include "sys.h"
#include "usart3.h"
#include "stdio.h"
#include "stm32f10x.h"

static u8 Cx=0,Cy=0,Cw=0,Ch=0;
u8 RX_1=0;

void USART3_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;     //串口端口配置结构体变量
		USART_InitTypeDef USART_InitStructure;   //串口参数配置结构体变量
		NVIC_InitTypeDef NVIC_InitStructure;     //串口中断配置结构体变量

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

    	//USART3_TX   PB10
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          		
   		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //设定IO口的输出速度为50MHz
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //复用推挽输出
    	GPIO_Init(GPIOB, &GPIO_InitStructure);             	 	 
    	//USART3_RX	  PB11
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    	GPIO_Init(GPIOB, &GPIO_InitStructure);               

    	//USART3 NVIC 配置
    	NVIC_InitStructure.NVIC_IRQChannel = 39;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;  //抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		    //子优先级2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      					                 //IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	                          //根据指定的参数初始化VIC寄存器

    	//USART 初始化设置
		USART_InitStructure.USART_BaudRate = 9600;                  //串口波特率为115200
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;        //一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;           //无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //收发模式
    	USART_Init(USART3, &USART_InitStructure);                     //初始化串口1

    	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //使能中断
   		USART_Cmd(USART3, ENABLE);                     //使能串口3
	  	USART_ClearFlag(USART3, USART_FLAG_TC);        //清串口3发送标志
		
}

//USART3 全局中断服务函数
void USART3_IRQHandler(void)			 
{
	
		u8 com_data; 
		u8 i;
		static u8 RxCounter1=0;					//缓冲数组计数（类似str[i]）
		static u16 RxBuffer1[10]={0};			//缓冲区赋值给这个数组
		static u8 RxState = 0;					//数据接收阶段标志位
		static u8 RxFlag1 = 0;					//自定义接收完毕标志

		if( USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  	   //接收中断  
		{
				USART_ClearITPendingBit(USART3,USART_IT_RXNE);   //清除中断标志
				com_data = USART_ReceiveData(USART3);
			
				if(RxState==0&&com_data==0x2C)  //0x2c帧头
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)					//帧头确定完毕后停留在这里
				{
					RxBuffer1[RxCounter1++]=com_data;		//接收数据

					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1接受满了,或收到终止符
					{
						RxState=3;
						RxFlag1=1;
						Cx=RxBuffer1[RxCounter1-5];				//数据存入变量
						Cy=RxBuffer1[RxCounter1-4];
						Cw=RxBuffer1[RxCounter1-3];
						Ch=RxBuffer1[RxCounter1-2];
						RX_1 = Cx;
					}
				}
		
				else if(RxState==3)		//检测是否接受到结束标志
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
									if(RxFlag1)
									{
										
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
						}
						else   //接收错误————最后不是结束字节标志
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //将存放数据数组清零
									}
						}
				} 
	
				else   //接收异常————没有匹配到起始字节标志
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
				}

		}
		
}
