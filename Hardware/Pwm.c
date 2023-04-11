#include "stm32f10x.h"                  // Device header
#include "Pwm.h"

void TIM4_PWM_Init(u16 arr,u16 psc)
{  
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;     
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;   
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB,&GPIO_InitStrue);               
    
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //映射，重映射只用于64、100、144脚单片机
   //当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
   //当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
   //当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr;  
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;       
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;   
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;       
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;
	
    TIM_OC3Init(TIM4,&TIM_OCInitStrue);        
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);  

    TIM_OC4Init(TIM4,&TIM_OCInitStrue);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);  

    
    TIM_Cmd(TIM4,ENABLE);       
    
}
