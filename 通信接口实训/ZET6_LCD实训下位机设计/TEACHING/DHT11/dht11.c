#include "stm32f10x.h"
#include "sys.h"
#include "dht11.h"
#include "delay.h"

void Dht11_Init(void)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				//第9号引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//引脚的速度最大为100MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//温湿度模块还没有工作，那么它的触发引脚是高电平
	PCout(2)=1;
}

//引脚模式变更
void Dht11_Pin_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;				//第9号引脚
	GPIO_InitStructure.GPIO_Mode  = mode;					//输入/输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//引脚的速度最大为100MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

//启动DHT11正常返回0 异常返回-1（根据启动时序图，写出下列代码）
int32_t Dht11_Start(void)
{
	u32 t = 0;

	//启动信号
	Dht11_Pin_Mode(GPIO_Mode_Out_PP);
	PCout(2) = 1;
	delay_us(50);
	PCout(2) = 0;
	delay_ms(20);
	PCout(2) = 1;
	delay_us(30);
	
	Dht11_Pin_Mode(GPIO_Mode_IN_FLOATING);
	
	t = 0;
	//等待低电平到来
	while(PCin(2) == 1)
	{
		t++;
		delay_us(2);
	
		if(t >= 1000) //等待2ms未能等待到低电平
		{
			return -1;
		}		
	}
	
	delay_us(40);
	t = 0;
	
	//等待高电平到来 过滤低电平
	while(PCin(2) == 0)
	{
		t++;
		delay_us(2);
	
		if(t >= 80) //等待160us未能等待到高电平
		{
			return -1;
		}		
	}		
	
	delay_us(40);
	t = 0;	
	//等待低电平到来 过滤高电平
	while(PCin(2) == 1)
	{
		t++;
		delay_us(2);
	
		if(t >= 80) //等待160us未能等待到低电平
		{
			return -1;
		}		
	}

	return 0;
}

//一次性读取八位数据
int16_t Dht11_Read_Byte(void)
{
	u8 i, data = 0;  //0000 0000
	u32 t = 0;
	
	for(i=0; i<8; i++)
	{
		t = 0;	
		//等待高电平到来 过滤低电平
		while(PCin(2) == 0)
		{
			t++;
			delay_us(2);
		
			if(t >= 50) //等待100us未能等待到高电平
			{
				return 0;
			}	
		
		}		
	
		delay_us(40);
		
		if(PCin(2) == 1)
		{
			data |= (1<<(7-i));
			t = 0;
			//等待低电平到来 过滤高电平
			while(PCin(2) == 1)
			{
				t++;
				delay_us(2);
			
				if(t >= 50) //等待100us未能等待到低电平
				{
					return -1;
				}		
			}				
		}	
	}
	
	return data;	
}

//成功返回0，失败返回-1
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
