#include "stm32f10x.h"
#include "sys.h"
#include "dht11.h"
#include "delay.h"

void Dht11_Init(void)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				//��9������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//���ŵ��ٶ����Ϊ100MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//��ʪ��ģ�黹û�й�������ô���Ĵ��������Ǹߵ�ƽ
	PCout(2)=1;
}

//����ģʽ���
void Dht11_Pin_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;				//��9������
	GPIO_InitStructure.GPIO_Mode  = mode;					//����/���ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//���ŵ��ٶ����Ϊ100MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

//����DHT11��������0 �쳣����-1����������ʱ��ͼ��д�����д��룩
int32_t Dht11_Start(void)
{
	u32 t = 0;

	//�����ź�
	Dht11_Pin_Mode(GPIO_Mode_Out_PP);
	PCout(2) = 1;
	delay_us(50);
	PCout(2) = 0;
	delay_ms(20);
	PCout(2) = 1;
	delay_us(30);
	
	Dht11_Pin_Mode(GPIO_Mode_IN_FLOATING);
	
	t = 0;
	//�ȴ��͵�ƽ����
	while(PCin(2) == 1)
	{
		t++;
		delay_us(2);
	
		if(t >= 1000) //�ȴ�2msδ�ܵȴ����͵�ƽ
		{
			return -1;
		}		
	}
	
	delay_us(40);
	t = 0;
	
	//�ȴ��ߵ�ƽ���� ���˵͵�ƽ
	while(PCin(2) == 0)
	{
		t++;
		delay_us(2);
	
		if(t >= 80) //�ȴ�160usδ�ܵȴ����ߵ�ƽ
		{
			return -1;
		}		
	}		
	
	delay_us(40);
	t = 0;	
	//�ȴ��͵�ƽ���� ���˸ߵ�ƽ
	while(PCin(2) == 1)
	{
		t++;
		delay_us(2);
	
		if(t >= 80) //�ȴ�160usδ�ܵȴ����͵�ƽ
		{
			return -1;
		}		
	}

	return 0;
}

//һ���Զ�ȡ��λ����
int16_t Dht11_Read_Byte(void)
{
	u8 i, data = 0;  //0000 0000
	u32 t = 0;
	
	for(i=0; i<8; i++)
	{
		t = 0;	
		//�ȴ��ߵ�ƽ���� ���˵͵�ƽ
		while(PCin(2) == 0)
		{
			t++;
			delay_us(2);
		
			if(t >= 50) //�ȴ�100usδ�ܵȴ����ߵ�ƽ
			{
				return 0;
			}	
		
		}		
	
		delay_us(40);
		
		if(PCin(2) == 1)
		{
			data |= (1<<(7-i));
			t = 0;
			//�ȴ��͵�ƽ���� ���˸ߵ�ƽ
			while(PCin(2) == 1)
			{
				t++;
				delay_us(2);
			
				if(t >= 50) //�ȴ�100usδ�ܵȴ����͵�ƽ
				{
					return -1;
				}		
			}				
		}	
	}
	
	return data;	
}

//�ɹ�����0��ʧ�ܷ���-1
int32_t Dht11_Read(u8 *data)
{
	u8 i=0;
	
	for(i=0; i<5; i++)
	{
		data[i] = Dht11_Read_Byte();
	}
	
	if(data[4] == data[0]+data[1]+data[2]+data[3])
	{
		return 0;
	}
	else
	{
		return -1;	
	}

}
