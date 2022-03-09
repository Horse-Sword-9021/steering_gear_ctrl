#include "timer.h"
   	 

//通用定时器3中断初始化
//时钟选择72M
//arr：自动重装值。
//psc：时钟预分频数
//使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
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
	
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 99;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;//输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	
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
//	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//根据T指定的参数初始化外设TIM3 OC2
//	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
//	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
//	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);//使能TIM3在CCR2上的预装载寄存器
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











