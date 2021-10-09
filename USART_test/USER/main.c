#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"

int main(void)
{
	delay_init();
	uart_init(115200);
	while(1)
	{
		printf("why\n");
		delay_ms(1000);
	}
}
