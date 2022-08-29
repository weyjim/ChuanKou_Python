#ifndef __GPIO_H
#define __GPIO_H

void KEY_Init(void);
void BEEP_Init(void);
void IR_Init(void);
void LCDGPIO_Init(void);

#define KEY0 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define KEY2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)

#define IR0 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)

#endif
