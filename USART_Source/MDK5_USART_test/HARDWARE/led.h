#ifndef __LED_H
#define __LED_H

void LED_Init(void);

#define LED0 PBout(5)
#define LED1 PEout(5)		//定义后可以像51一样编程

#endif
