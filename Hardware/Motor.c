#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"


void MotorInit(void)
{		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

void Motor_Stop(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

void Motor_1_Nrun(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

void Motor_1_Prun(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void Motor_2_Nrun(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void Motor_2_Prun(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}

void Motor_Nrun()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void Motor_Prun()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}

void Motor_Outwerd(void)  //去程
{
		TIM_SetCompare3(TIM4,15000);
		TIM_SetCompare4(TIM4,13998);
		Motor_1_Prun();
		Motor_2_Prun();
		delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(300);
		Motor_Stop();
		delay_ms(500);
		Motor_1_Nrun();
		Motor_2_Prun();
		delay_ms(620);
		Motor_Stop();
		delay_ms(500);
		TIM_SetCompare4(TIM4,15700);
		Motor_1_Prun();
		Motor_2_Prun();
		delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(410);
		Motor_Stop();
		delay_ms(500);
}

void Motor_Retnrn(void)  //回程
{
			TIM_SetCompare3(TIM4,15000);
			TIM_SetCompare4(TIM4,14000);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(930);
			Motor_Stop();
			delay_ms(500);
			Motor_1_Prun();
			Motor_2_Prun();
			delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(300);
			Motor_Stop();
			delay_ms(500);
			Motor_1_Prun();
			Motor_2_Nrun();
			delay_ms(460);
			Motor_Stop();
			delay_ms(500);
			Motor_1_Prun();
			Motor_2_Prun();
			delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);
			Motor_Stop();
}

