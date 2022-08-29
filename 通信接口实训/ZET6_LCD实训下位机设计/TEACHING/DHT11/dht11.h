#ifndef __DHT11_H
#define __DHT11_H	 

#include "stm32f10x.h"

void Dht11_Init(void);
void Dht11_Pin_Mode(GPIOMode_TypeDef mode);

int32_t Dht11_Start(void);
int16_t Dht11_Read_Byte(void);
int32_t Dht11_Read(u8 *data);



#endif
