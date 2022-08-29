#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f10x.h"

void LED_Init(void);
void BEEP_Init(void);
void KEY_Init(void);

#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define KEY3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
#define KEY4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define KEY5 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define KEY6 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

#define LED0_0 GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define LED0_1 GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define LED1_0 GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define LED1_1 GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define LED2_0 GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define LED2_1 GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define LED3_0 GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define LED3_1 GPIO_SetBits(GPIOB,GPIO_Pin_7)


#define BEEP_0 GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define BEEP_1 GPIO_SetBits(GPIOB,GPIO_Pin_8)

#endif
