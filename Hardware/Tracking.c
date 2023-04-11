#include "stm32f10x.h" // Device header
#include "Motor.h"
#include "Drug.h"
#include "Delay.h"
#include "usart3.h"

extern u8 RubbishFlat;
u8 banana = 0;

void Tracking(void)
{
		if(Left_Get()==1)
		{
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(10);
		}
		if(Right_Get()==1)
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(10);
		}
}

void Left1_Tracking(void)
{
	Motor_Prun();
	if(Left_Get()==1&&Right_Get()==1&&banana==3)//起点
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(970);
			Motor_Stop();
			banana = 4;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
			PC_SendString((u8*)"\n\n已回到起点\n\n");
		}
	if(Left_Get()==1&&Right_Get()==1&&banana==2)//回程第一个十字路口
		{
			banana = 3;
			Motor_Prun();
			delay_ms(270);
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(500);
		}
	if(Left_Get()==1&&Right_Get()==1&&banana==1)//终点
	{
		Motor_Stop();
		PC_SendString((u8*)"\n\n已到达指定地点\n");
		PC_SendString((u8*)"等待垃圾取走\n\n");
		while(RubbishFlat == 1)
		{
			delay_ms(1);
		}
		PC_SendString((u8*)"\n\n检测到垃圾已取走\n");
		PC_SendString((u8*)"正在回程\n");
		Motor_1_Prun();
		Motor_2_Nrun();
		delay_ms(1050);
		banana = 2;
	}
		if(Left_Get()==1&&Right_Get()==1)//去程第一个十字路口
		{
			banana = 1;
			Motor_Prun();
			delay_ms(200);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(500);
		}
		if(Left_Get()==1)
		{
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(10);
		}
		if(Right_Get()==1)
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(10);
		}
}

void Left2_Tracking(void)
{
		if(Left_Get()==1&&Right_Get()==1&&banana==5)//回到起点
		{
			Motor_Stop();
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==4)//回程二第个十字路口
		{
			banana = 5;
			Motor_Prun();
			delay_ms(130);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==3)//回程第一个十字路口
		{
			banana = 4;
			Motor_Prun();
			delay_ms(270);
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(480);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==2)//到达终点
		{
			Motor_Stop();
			delay_ms(500);delay_ms(500);
			banana = 3;
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(870);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==1)//去程第二个十字路口
		{
			banana = 2;
			Motor_Prun();
			delay_ms(200);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(400);
		}
		if(Left_Get()==1&&Right_Get()==1)//去程第一个十字路口
		{
			banana = 1;
			Motor_Prun();
			delay_ms(200);
		}
		if(Left_Get()==1)
		{
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(10);
		}
		if(Right_Get()==1)
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(10);
		}
}

void Right1_Tracking(void)
{
	if(Left_Get()==1&&Right_Get()==1&&banana==3)//起点
		{
			Motor_Stop();
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
		}
	if(Left_Get()==1&&Right_Get()==1&&banana==2)//回程第一个十字路口
		{
			banana = 3;
			Motor_Prun();
			delay_ms(270);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(480);
		}
	if(Left_Get()==1&&Right_Get()==1&&banana==1)//终点
	{
		Motor_Stop();
		delay_ms(500);delay_ms(500);
		Motor_1_Prun();
		Motor_2_Nrun();
		delay_ms(870);
		banana = 2;
	}
		if(Left_Get()==1&&Right_Get()==1)//去程第一个十字路口
		{
			banana = 1;
			Motor_Prun();
			delay_ms(200);
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(400);
		}
		if(Left_Get()==1)
		{
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(10);
		}
		if(Right_Get()==1)
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(10);
		}
}

void Right2_Tracking(void)
{
		Motor_Prun();
		if(Left_Get()==1&&Right_Get()==1&&banana==5)//回到起点
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(970);
			Motor_Stop();
			banana = 6;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE);
			PC_SendString((u8*)"\n\n已回到起点\n\n");
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==4)//回程二第个十字路口
		{
			banana = 5;
			Motor_Prun();
			delay_ms(130);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==3)//回程第一个十字路口
		{
			banana = 4;
			Motor_Prun();
			delay_ms(270);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(500);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==2)//到达终点
		{
			Motor_Stop();
			PC_SendString((u8*)"\n\n已到达指定地点\n");
			PC_SendString((u8*)"等待垃圾取走\n\n");
			while(RubbishFlat)
		{
			delay_ms(1);
		}
			PC_SendString((u8*)"\n\n检测到垃圾已取走\n");
			PC_SendString((u8*)"正在回程\n");
			banana = 3;
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(1050);
		}
		if(Left_Get()==1&&Right_Get()==1&&banana==1)//去程第二个十字路口
		{
			banana = 2;
			Motor_Prun();
			delay_ms(200);
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(500);
		}
		if(Left_Get()==1&&Right_Get()==1)//去程第一个十字路口
		{
			banana = 1;
			Motor_Prun();
			delay_ms(200);
		}
		if(Left_Get()==1)
		{
			Motor_2_Prun();
			Motor_1_Nrun();
			delay_ms(10);
		}
		if(Right_Get()==1)
		{
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(10);
		}
}
