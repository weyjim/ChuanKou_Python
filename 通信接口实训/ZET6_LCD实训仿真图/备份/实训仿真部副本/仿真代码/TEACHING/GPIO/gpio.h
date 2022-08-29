#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

void KEY_Init(void);
void BEEP_Init(void);

#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)  //����        1
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)  //����ʱ��        2
#define KEY4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)  //����ʱ��        3
#define KEY5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)  //�и�       4
#define KEY6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)  //����ʱ����֮���л�    5
//#define KEY12 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
//#define KEY13 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
//#define KEY14 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
//#define KEY_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)


#endif


