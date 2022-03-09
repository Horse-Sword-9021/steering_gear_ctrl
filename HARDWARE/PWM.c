#include "pwm.h"
	   

//��ʼ��PA0-7Ϊ�����.��ʹ����ʱ��  
//PWM IO��ʼ��
void PWM_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PWM0-7 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA0-7
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0-7���Ϊ��
}
 
//��ʱ��3
//PA6��PA7 TIM3CH1|2
//���������еĲ���������pwm�������ڣ�main�����������ڣ�
void TIM3_Init(u16 arr, u16 psc)
{
	 
	GPIO_InitTypeDef  GPIO_InitStructure;				//GPIO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;		//��ʱ��
	TIM_OCInitTypeDef TIM_OCInitStruct;					//ͨ��

	
	//����ʱ������	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 //PWM0-7 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA0-7
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);						 //PA0-7���Ϊ��
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ����
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period=arr;//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//Ԥ��Ƶϵ��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);//ͨ��1
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);//ͨ��2
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Ԥװ����
	TIM_Cmd(TIM3,ENABLE);//ʹ��TIM3
	
	
	TIM_SetCompare2(TIM3,1500);
	TIM_SetCompare3(TIM3,2000);

}
