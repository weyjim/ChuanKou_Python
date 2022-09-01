#include "sys.h"
#include "usart3.h"
#include "stdio.h"
#include "stm32f10x.h"

static u8 Cx=0,Cy=0,Cw=0,Ch=0;
u8 RX_1=0;

void USART3_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;     //���ڶ˿����ýṹ�����
		USART_InitTypeDef USART_InitStructure;   //���ڲ������ýṹ�����
		NVIC_InitTypeDef NVIC_InitStructure;     //�����ж����ýṹ�����

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

    	//USART3_TX   PB10
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          		
   		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //�趨IO�ڵ�����ٶ�Ϊ50MHz
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //�����������
    	GPIO_Init(GPIOB, &GPIO_InitStructure);             	 	 
    	//USART3_RX	  PB11
    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            
    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
    	GPIO_Init(GPIOB, &GPIO_InitStructure);               

    	//USART3 NVIC ����
    	NVIC_InitStructure.NVIC_IRQChannel = 39;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;  //��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		    //�����ȼ�2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      					                 //IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���

    	//USART ��ʼ������
		USART_InitStructure.USART_BaudRate = 9600;                  //���ڲ�����Ϊ115200
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;        //һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;           //����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //�շ�ģʽ
    	USART_Init(USART3, &USART_InitStructure);                     //��ʼ������1

    	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //ʹ���ж�
   		USART_Cmd(USART3, ENABLE);                     //ʹ�ܴ���3
	  	USART_ClearFlag(USART3, USART_FLAG_TC);        //�崮��3���ͱ�־
		
}

//USART3 ȫ���жϷ�����
void USART3_IRQHandler(void)			 
{
	
		u8 com_data; 
		u8 i;
		static u8 RxCounter1=0;					//�����������������str[i]��
		static u16 RxBuffer1[10]={0};			//��������ֵ���������
		static u8 RxState = 0;					//���ݽ��ս׶α�־λ
		static u8 RxFlag1 = 0;					//�Զ��������ϱ�־

		if( USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  	   //�����ж�  
		{
				USART_ClearITPendingBit(USART3,USART_IT_RXNE);   //����жϱ�־
				com_data = USART_ReceiveData(USART3);
			
				if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)					//֡ͷȷ����Ϻ�ͣ��������
				{
					RxBuffer1[RxCounter1++]=com_data;		//��������

					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1��������,���յ���ֹ��
					{
						RxState=3;
						RxFlag1=1;
						Cx=RxBuffer1[RxCounter1-5];				//���ݴ������
						Cy=RxBuffer1[RxCounter1-4];
						Cw=RxBuffer1[RxCounter1-3];
						Ch=RxBuffer1[RxCounter1-2];
						RX_1 = Cx;
					}
				}
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//�ر�DTSABLE�ж�
									if(RxFlag1)
									{
										
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
						}
						else   //���մ��󡪡���������ǽ����ֽڱ�־
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣��������û��ƥ�䵽��ʼ�ֽڱ�־
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}

		}
		
}
