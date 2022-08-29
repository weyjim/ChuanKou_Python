#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"

extern int Rcount;
extern int A;
extern int B;

void Timerx_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);

#endif
