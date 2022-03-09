#include "timer.h"
   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//ʱ��ѡ��72M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}


void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //????
	
	//TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx???????????
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //??????????TIMx???????
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //?????TIM3??,??????

	//SNVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?????0?
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //????3?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ?????
	NVIC_Init(&NVIC_InitStructure);  //???NVIC???

//	TIM_Cmd(TIM4, ENABLE);  //??TIMx					 
}


void PWM_ParameterConfiguration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = 99;//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;//�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
//	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
//	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
//	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
//	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
//	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
//	
//	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
//	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//����Tָ���Ĳ�����ʼ������TIM3 OC2
//	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
//	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
//	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);//ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
//	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	TIM_ARRPreloadConfig(TIM3, ENABLE);
//	TIM_CtrlPWMOutputs(TIM1,ENABLE);
//	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
//	TIM_Cmd(TIM3, ENABLE);
}











