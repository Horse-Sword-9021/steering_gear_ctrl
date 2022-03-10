#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "adc.h"
#include "oled.h"
#include "timer.h"
 
#include <math.h>
#include <string.h>



#define PI 3.1415f


float datas[5];		//datas[3]，测试通过后将三角函数波形取消掉
int cmd_P,cmd_I,cmd_D, pid_p,pid_i,pid_d=1.0;	//PID;

 int command=500;

int SOM_In,SOM_Out,SOM1_In,SOM1_Out;

u8 JD=0, table_dat2[201];
u8 flag1=0,flag2=0;//定时器计数20ms到了的标志
u16 table_dat[200];//, SOM1_In,SOM1_Out;
u32 a0,a1, time_num=0;

void send_wave(void);
void getdatas(void);
void get_cmd(void);
int lastError=0, sumError=0; //sum??? 

/*
//float pid_p=0.2,pid_i=0.001,pid_d=1.0;	//PID

//int sumError=0;//sum???
//u8 flag1 = 0;
//u32 time_num=0;
//u8 table_dat2[201];
//D0 = 1逆,D1 = 1顺
*/

/*
 int main(void)
 {	u16 t=0, t1=0, t2=0, adcx,aim=2024;
	u8 t3=0, flag2=0, YS[6]={0,60,120,180,120,60};
	//u16 adcx,aim=2024;
	float num1, B;
	//u8 flag2=0;
	//float B;
	int Error=0, dError=0;
	//int dError=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	//usart_init(115200);	 	//串口初始化为115200	
 	Adc_Init();		  		//ADC初始化
	PWM_Init();   
	PWM_ParameterConfiguration();
	TIM_SetCompare1(TIM2,0);//0-99
	TIM_SetCompare2(TIM2,0);
	TIM4_Int_Init(200-1,7200-1);//20ms
	//TIM3_Int_Init(200-1,72-1);//200us
	flag1=0;
	for(t2=0;t2<200;t2++)
	{
		table_dat2[t3]=' ';
	}
	
	usart_init(9600);	 //串口初始化为115200
 	//PWM_Init();			     //LED端口初始化
	TIM3_Int_Init(9,71);//10us
	t1=(t1/180)*2000;
	//delay_init();	    //延时函数初始化	  
	usart_init(115200);
	
	while(1)
	{
	///////////////////////
		PWM0=1;
		delay_us(500+t1);//延时
		PWM0=0;
		delay_ms(20);//延时
		if(flag2==1)
		{
			flag2=0;
			JD=YS[t2];
			t2++;
			if(t2>=6)
			{
				t2=0;
			}
		}
		//////////////////////////////
		if(flag1==1)
		{
			flag1=0;
			adcx=Get_Adc_Average(ADC_Channel_2,3);//顺大
			if(t<200)
			{
				table_dat[t] =adcx;
				t++;
			}
			Error=adcx-aim;//????
			sumError=Error+sumError;//???
			dError=Error-lastError;//????
			lastError=Error;
			if(sumError>10000)sumError=10000;
			if(sumError<-10000)sumError=-10000;
			B=pid_p*Error+pid_i*sumError+pid_d*dError;
			num1=B;
			if(num1>49)num1=49;
			if(num1<-49)num1=-49;
			if((adcx-aim)>10)
			{
				TIM_SetCompare1(TIM2,50+num1);//0-99
				TIM_SetCompare2(TIM2,0);
			}else if((adcx-aim)<-10)
			{
				TIM_SetCompare1(TIM2,0);//0-99
				TIM_SetCompare2(TIM2,50-num1);
			}else
			{
				TIM_SetCompare1(TIM2,0);//0-99
				TIM_SetCompare2(TIM2,0);
				if(flag2==1)
				{
					TIM_Cmd(TIM3, DISABLE);  //??TIMx
					TIM_Cmd(TIM4, DISABLE);  //??TIMx
					printf("time=%dus\r\n",time_num*200);
					printf("adcx=%d,aim=%d\r\n",adcx,aim);
					printf("num1=%f\r\n",num1);
					printf("t=%d\r\n",t);
					for(t3=0;t3<200;t3++)
					{
						table_dat[t3]=table_dat[t3]*100/4000;
					}
					for(t3=99;t3>0;t3--)
					{
						for(t2=0;t2<200;t2++)
						{
							table_dat2[t2]=' ';
						}
						for(t2=0;t2<200;t2++)
						{
							if(table_dat[t2]==t3)
							table_dat2[t2]='-';
						}
						table_dat2[200]='\0';
						printf("%d%s",t3,table_dat2);
						printf("\r\n");
					}
					t=0;
					flag2=0;
				}
			}
		}
		if(USART_RX_STA&0x8000)
		{		
			if(USART_RX_BUF[0]=='A')
			{
				aim = ((USART_RX_BUF[1]-'0')*100+(USART_RX_BUF[2]-'0')*10+(USART_RX_BUF[3]-'0'))*20+50;
				if((aim>4048)|(aim<48))aim = 2024;
				printf("%d\r\n",aim);//????
				flag2=1;
				USART_RX_STA=0;
				time_num=0;
				TIM_Cmd(TIM4, ENABLE);  //??TIMx
				TIM_Cmd(TIM3, ENABLE);  //??TIMx	
			}else if(USART_RX_BUF[0]=='P')
			{
				pid_p = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
				printf("P=%f\r\n",pid_p);
				printf("I=%f\r\n",pid_i);
				printf("D=%f\r\n",pid_d);
				USART_RX_STA=0;
			}else if(USART_RX_BUF[0]=='I')
			{
				pid_i = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
				printf("P=%f\r\n",pid_p);
				printf("I=%f\r\n",pid_i);
				printf("D=%f\r\n",pid_d);
				USART_RX_STA=0;
			}else if(USART_RX_BUF[0]=='D')
			{
				pid_d = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
				printf("P=%f\r\n",pid_p);
				printf("I=%f\r\n",pid_i);
				printf("D=%f\r\n",pid_d);
				USART_RX_STA=0;
			}
		
		}
	}
 }
 */
 
 //////////////////////////////////////////////////////////////
 /*
 
 int main(void)
 {	
	u16 t1=0,t2=0;
	u8 YS[6]={0,60,120,180,120,60};
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	usart_init(9600);	 //串口初始化为115200
 	PWM_Init();			  
	TIM3_Int_Init(9,71);//10us
	t1=(t1/180)*2000;
	delay_init();	    //延时函数初始化	  
	usart_init(115200);
	OLED_Init();
	
	while(1)
	{
		//send_wave();
		
		PWM0=1;
		
		
		///////////////////////////
		send_wave();
		getdatas();
		get_cmd();
		
		//SOM_In=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		//SOM_Out=GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0);
		
		//SOM1_In=GPIO_ReadInputData(GPIOA);
		//SOM1_Out=GPIO_ReadOutputData(GPIOA);
		
		
		//OLED_ShowChar(1, 1, 'S');
		//OLED_ShowString(1, 1, "Parameter");
		//OLED_ShowSignedNum(2, 1, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0), 4);
		//OLED_ShowSignedNum(2, 1,datas[0],6);
		//USART_RX_STA=0;
		//OLED_ShowSignedNum(2, 8, SOM_Out, 6);
		//OLED_ShowSignedNum(3, 1, SOM1_In, 6);
		//OLED_ShowSignedNum(3, 8, SOM1_Out, 6);
		//OLED_ShowSignedNum(3, 1,sinf(PI/4), 8);
		//OLED_ShowSignedNum(3, 6, datas[4], 8);
		//OLED_ShowSignedNum(4, 1, datas[6], 8);
		//OLED_ShowHexNum(3, 1, cmd_P, 4);//0xAA55
		//OLED_ShowBinNum(3, 6, cmd_I, 8);
		
		
		delay_us(500+t1);//延时
		///////////////////////////////////////	

		
		PWM0=0;
	////////////////////////////
		send_wave();
		getdatas();
		get_cmd();
		
		SOM_In=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		SOM_Out=GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0);
		
		SOM1_In=GPIO_ReadInputData(GPIOA);
		SOM1_Out=GPIO_ReadOutputData(GPIOA);
		
		//OLED_ShowChar(1, 1, 'S');
		OLED_ShowSignedNum(2, 1,datas[0],6);
		USART_RX_STA=0;
		//OLED_ShowSignedNum(2, 8, SOM_Out, 6);
		//OLED_ShowSignedNum(3, 1, SOM1_In, 6);
		//OLED_ShowSignedNum(3, 8, SOM1_Out, 6);
		//OLED_ShowSignedNum(3, 6, datas[4], 8);
		//OLED_ShowSignedNum(4, 1, datas[6], 8);
		//OLED_ShowHexNum(3, 1, cmd_P, 4);//0xAA55
		//OLED_ShowBinNum(3, 6, cmd_I, 8);
		//////////////////////////
		
		delay_ms(100);//延时
		///////////////////////////////////////////////////////////////

		if(flag1==1)
		{
			flag1=0;
			t2++;
			if(t2==50)
			JD=60;
			if(t2==100)
			JD=120;
			if(t2==150)
			JD=180;
			if(t2==200)
			JD=120;
			if(t2==250)
			JD=60;
			if(t2==300)
			{
				JD=0;
				t2=0;
			}
	}

		//getdatas();
		
		if(flag2==1)
		{
			flag2=0;
			JD=YS[t2];
			t2++;
			if(t2>=6)
			{
				t2=0;
			}
		}
		
		send_wave();
		getdatas();
		get_cmd();
		
		SOM_In=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		SOM_Out=GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0);
		SOM1_In=GPIO_ReadInputData(GPIOA);
		SOM1_Out=GPIO_ReadOutputData(GPIOA);
		
		//OLED_ShowChar(1, 1, 'S');
		OLED_ShowString(1, 1, "Parameter");
		OLED_ShowBinNum(2, 1,datas[7],6);
		USART_RX_STA=0;
		OLED_ShowBinNum(2, 9, datas[8], 6);
		OLED_ShowSignedNum(3, 1, datas[9], 6);
		OLED_ShowSignedNum(3, 9, datas[10], 6);
		//OLED_ShowSignedNum(4, 1, datas[4], 5);
		//OLED_ShowSignedNum(4, 1, datas[6], 8);
		//OLED_ShowHexNum(3, 1, cmd_P, 4);//0xAA55
		//OLED_ShowBinNum(3, 6, cmd_I, 8);

	}
 }

 */
 //////////////////////////////////////
 
 
 int main(void)
 {
	 delay_init();
	 TIM3_Init(39999,71);//T=20ms(arr+1)(psc+1)/Tclk   20000*72/72000000
	 usart_init(115200);
	 OLED_Init();
	 OLED_ShowString(1, 1, "Parameter");
//	 20ms
//	 0.5ms-0
//	 1.0ms-45
//	 1.5ms-90
//	 2.0ms-135
//	 2.5-180
	 while(1)
	 {
		 getdatas();
		 send_wave();
		 
		 SOM_In=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
		 SOM_Out=GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_6);
		
		 SOM1_In=GPIO_ReadInputData(GPIOA);
		 SOM1_Out=GPIO_ReadOutputData(GPIOA);
		 
		 OLED_ShowSignedNum(2, 1,SOM_In,6);
		 //USART_RX_STA=0;
		 OLED_ShowSignedNum(2, 9, SOM_Out, 6);
		 OLED_ShowSignedNum(3, 1,SOM1_In, 6);
		 OLED_ShowSignedNum(3, 9, SOM1_Out, 6);
		 
		 //占空比=x/20000
		 TIM_SetCompare1(TIM3,command);		//500/20000==0.5/20
		 delay_ms(1000);
//		 TIM_SetCompare1(TIM3,1000);
//		 delay_ms(1000);
//		 TIM_SetCompare1(TIM3,1500);
//		 delay_ms(1000);
//		 TIM_SetCompare1(TIM3,2000);
//		 delay_ms(1000);
//		 TIM_SetCompare1(TIM3,2500);
//		 delay_ms(1000);
//		 TIM_SetCompare1(TIM3,3000);
//		 delay_ms(1000);
		 getdatas();
		 send_wave();
		 
		 get_cmd();
		 
		 SOM_In=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
		 SOM_Out=GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_6);
		
		 SOM1_In=GPIO_ReadInputData(GPIOA);
		 SOM1_Out=GPIO_ReadOutputData(GPIOA);
		 
		 OLED_ShowSignedNum(2, 1,SOM_In,6);
		 //USART_RX_STA=0;
		 OLED_ShowSignedNum(2, 9, SOM_Out, 6);
		 OLED_ShowSignedNum(3, 1,SOM1_In, 6);
		 OLED_ShowSignedNum(3, 9, SOM1_Out, 6);
	 }
	 
 }
 
void send_wave(void)
{
	//定义通道名帧头帧尾
	u8 frameNameHead[] = "AABBCC";
	u8 frameNameEnd[] = "CCBBAA";
	
	//定义数据帧头帧尾
	u8 frameDataHead[] = "DDEEFF";
	u8 frameDataEnd[] = "FFEEDD";
	
	//定义通道名
	u8 name[] = {"sin(x)_test,SOM_In,SOM_Out,SOM1_In,SOM1_Out"};
	
	
	/*
	u8 name[] = {"P,I,D"};
	//赋值数据
	float channels[3];
	channels[0] = cmd_P;
	channels[1] = cmd_I;
	channels[2] = cmd_D;
	*/
	
	
	float channels[5];
	channels[0] = datas[0];
	channels[1] = datas[1];
	channels[2] = datas[2];
	channels[3] = datas[3];
	channels[4] = datas[4];//cmd_P;
	
//	channels[5] = datas[5];//cmd_I;
//	channels[6] = datas[6];//cmd_D;
//	channels[7] = datas[7];
//	channels[8] = datas[8];
//	channels[9] = datas[9];
//	channels[10]= datas[10];
	

	//通过串口1，向上位机发送数据
	usart_senddatas(USART1,frameNameHead,sizeof(frameNameHead)-1);
	usart_senddatas(USART1,name,sizeof(name)-1);
	usart_senddatas(USART1,frameNameEnd,sizeof(frameNameEnd)-1);
	
	usart_senddatas(USART1,frameDataHead,sizeof(frameDataHead)-1);
	usart_senddatas(USART1,(u8*)channels,sizeof(channels));
	usart_senddatas(USART1,frameDataEnd,sizeof(frameDataEnd)-1);
	
}


void getdatas(void)
{
	static float x = 0.00f * PI;
	datas[0] = sinf(x);//sinf(x)
	
//	datas[1] = cmd_P;
//	datas[2] = cmd_I;
//	datas[3] = cmd_D;
//	
//	datas[4] = pid_p;
//	datas[5] = pid_i;
//	datas[6] = pid_d;
	
	datas[1]=SOM_In;
	datas[2]=SOM_Out;
	datas[3]=SOM1_In;
	datas[4]=SOM1_Out;
	x += 0.05f * PI;
	
	/*
	OLED_ShowSignedNum(2, 1, datas[0], 5);
	OLED_ShowSignedNum(2, 7, datas[1], 5);
	OLED_ShowSignedNum(3, 1, datas[2], 5);
	OLED_ShowSignedNum(3, 7, datas[3], 5);
	OLED_ShowSignedNum(4, 1, datas[4], 5);
	OLED_ShowSignedNum(4, 7, datas[5], 5);
	*/
}



void get_cmd(void)
{
	char u_buff[10];
	int u_d1;//,u_d2,u_d3;
	/*
	cmd_P = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
	USART_RX_STA=0;
	cmd_I = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
	USART_RX_STA=0;
	cmd_D = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
	USART_RX_STA=0;
	*/
	//在usart_get_data()函数定义中可更改通信协议，（改变发送命令格式）
	if(usart_get_data(u_buff,&u_d1))//(usart_get_data(u_buff,&u_d1,&u_d2,&u_d3))
	{
		if(strcmp(u_buff,"cmd") == 0) //比较命令控制字符是否为指令字符
		{
			command=u_d1;
//			cmd_P = u_d1;
//			cmd_I = u_d2;
//			cmd_D = u_d3;
//			
//			pid_p = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
//			USART_RX_STA=0;
//			pid_i = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
//			USART_RX_STA=0;
//			pid_d = (float)((USART_RX_BUF[1]-'0')*10000+(USART_RX_BUF[2]-'0')*1000+(USART_RX_BUF[3]-'0')*100+(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0'))/10000;
//			USART_RX_STA=0;
//			
//			SOM_Out=GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
//			SOM1_Out=GPIO_ReadOutputData(GPIOA);
			
		}
	}

	
	memset(u_buff,0,sizeof(u_buff));
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			a0++;a1++;
/*************PWM0**************/			
			if(a0==(50+JD))
			{
				PWM0=0;
			}
			if(a0>=2000)
			{
				a0=0;
				PWM0=1;
				flag1=1;
			}
			if(a1>=100000)
			{
				a1=0;
				flag2=1;
			}
		}
}

void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
			flag1=1;
		}
}

