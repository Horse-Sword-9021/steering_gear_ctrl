#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define PWM0 PAout(0)

void PWM_Init(void);//��ʼ��
void TIM3_Init(u16 arr, u16 psc);//��ʱ��3
		 				    
#endif
