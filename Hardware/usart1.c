#include "stm32f10x.h"                  // Device header
#include "usart1.h"
#include <stdarg.h>
#include "openmv.h"
#include "Motor.h"

void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //串口端口配置结构体变量
	USART_InitTypeDef USART_InitStructure;//串口参数配置结构体变量
	NVIC_InitTypeDef NVIC_InitStructure;//串口中断配置结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//打开串口复用时钟
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PC.10
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设定IO口的输出速度为50MHz
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC.10

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PC.11
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC.10  

  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
  	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率为115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式使能
	USART_Init(USART1, &USART_InitStructure); //初始化串口4
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口4
   	USART_ClearFlag(USART1, USART_FLAG_TC);       //清串口4发送标志
}


void USART1_IRQHandler(void)			   //串口中断
{
	u8 temp;
	if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET )
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志
		temp = USART_ReceiveData(USART1);
		Openmv_Receive_Data(temp);//openmv数据处理函数
	}
}
