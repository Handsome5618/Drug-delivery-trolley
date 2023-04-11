#include "stm32f10x.h"                  // Device header

void Infraed_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Rubbish_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
}

uint8_t Left_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

uint8_t Right_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
}
