#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define PWM0 PAout(0)

void PWM_Init(void);//初始化
void TIM3_Init(u16 arr, u16 psc);//定时器3
		 				    
#endif
