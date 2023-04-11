#ifndef __OPENMV_H
#define __OPENMV_H
#include "stm32f10x.h"                  // Device header

void Openmv_Receive_Data(int16_t data);
void USART1_Rx_Task(void);

#endif
