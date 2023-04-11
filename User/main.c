#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Pwm.h"
#include "openmv.h"
#include "usart1.h"
#include "Drug.h"
#include "Delay.h"
#include "LED.h"
#include "Tracking.h"
#include "usart3.h"
#include "CountSensor.h"


int main(void)
{
	LED_Init();
	Infraed_Init();
	USART1_Init();
	MotorInit();
	delay_init();
	USART3_Config();
	CountSensor_Init();
	TIM4_PWM_Init(59999,23);
	TIM_SetCompare3(TIM4,17000);
	TIM_SetCompare4(TIM4,17000);
{
	while(1)
	{
//		Motor_Prun();
//		Left1_Tracking();
		USART1_Rx_Task();
	}
}
}
