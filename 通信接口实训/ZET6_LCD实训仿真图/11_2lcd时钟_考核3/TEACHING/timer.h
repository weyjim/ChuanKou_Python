#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"

extern int Rcount,minute,hour;

void Timerx_Init(u16 arr,u16 psc);
void NVIC_Configuration(void);

#endif
