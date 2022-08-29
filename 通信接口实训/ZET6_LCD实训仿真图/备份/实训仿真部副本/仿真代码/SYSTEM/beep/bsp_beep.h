#ifndef __BEEP_H
#define __BEEP_H     
#include "sys.h"

#define BEEP PBout(1)  

void BEEP_Init(void);         
void Sound(u16 frq);
void Sound2(u16 time);
void play_music(void);
void play_music2(void);

void play_successful(void);
void play_failed(void);

#endif

