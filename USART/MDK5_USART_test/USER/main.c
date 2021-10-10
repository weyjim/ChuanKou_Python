#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"

int main(void)
{
	int i=0;
	delay_init();
	uart_init(115200);
	
	
	
	while(1)
	{
		printf("PWM=%d,Angle=15.432\n",i+=10);
		delay_ms(1000);
	}
}
