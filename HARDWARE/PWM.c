#include "pwm.h"
	   

//初始化PA0-7为输出口.并使能这时钟  
//PWM IO初始化
void PWM_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PWM0-7 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA0-7
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0-7输出为低
}
 
//定时器3
//PA6，PA7 TIM3CH1|2
//函数变量中的参数，调节pwm波的周期（main函数参数调节）
void TIM3_Init(u16 arr, u16 psc)
{
	 
	GPIO_InitTypeDef  GPIO_InitStructure;				//GPIO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		//定时器
	TIM_OCInitTypeDef TIM_OCInitStruct;					//通道

	
	//开启时钟总线	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 //PWM0-7 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA0-7
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PA0-7输出为低
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频因子
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);//通道1
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);//通道2
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能预装载器
	TIM_Cmd(TIM3,ENABLE);//使能TIM3
	
	
	TIM_SetCompare2(TIM3,1500);
	TIM_SetCompare3(TIM3,2000);

}
