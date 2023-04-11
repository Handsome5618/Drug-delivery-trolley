#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_gpio.h"

void USART1_Init(void);
void USART1_IRQHandler(void);

#endif
