#include "openmv.h"
#include "stm32f10x.h"
#include "Motor.h"
#include "Delay.h"
#include "LED.h"
#include "Drug.h"
#include "Delay.h"
#include "Tracking.h"
#include "usart3.h"

u8 com_data; 
u8 i = 0;
u8 RxCounter1=0;
u8 RxBuffer1[10]={0};
//static u8 RxState = 0;	
u8 RxFlag1 = 0;
extern u8 RubbishFlat;

void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 state = 0;	
	if(state==0&&data==0x2C)
	{
		state=1;
		RxBuffer1[0]=data;
	}
	else if(state==1&&data==0x12)
	{
		state=2;
		RxBuffer1[1]=data;
	}
	else if(state==2)
	{
		RxBuffer1[2]=data;
		state=3;
	}
	else if(state==3)
	{
		RxBuffer1[3]=data;
		state=4;
	}
	else if(state==4)
	{
		RxBuffer1[4]=data;
		state=5;
	}
	else if(state==5)
	{
		RxBuffer1[5]=data;
		state=6;
	}
	else if(state==6)		//state == 3  检测是否接受到结束标志
	{
		RxBuffer1[6]=data;
        	if(RxBuffer1[6] == 0x5B)
        	{
				openMVreaday();
            	state = 0;
				RxFlag1 = 1;
				USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
        	}
        	else   //wrong thing
        	{
            	state = 0;
				RxCounter1=0;
        	}
	}    
	else	//wrong thing
	{
		state = 0;
		RxCounter1=0;
	}
}

void USART1_Rx_Task(void)
{
	u8 date;
	if(RxFlag1 == 1)
	{
		RxFlag1 = 0;
	   	RxCounter1 = 0;
	date = RxBuffer1[2];
//	if(date==0x0001)
//	{
//		delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);
//		Left1_Tracking();
//	}
	if(date==0x0002)
	{
		PC_SendString((u8*)"\n\n识别到为厨余垃圾\n");
		PC_SendString((u8*)"等待垃圾放置\n\n");
		while(RubbishFlat == 0)
		{
			delay_ms(1);
		}
		RubbishFlat = 1;
		PC_SendString((u8*)"\n\n检测已放置垃圾\n");
		PC_SendString((u8*)"正在前往厨余垃圾存放地点\n\n");
		while(1)
		{
			Left1_Tracking();
		}
	}
//	else if(date==0x0003)
//	{
//		delay_ms(500);delay_ms(500);delay_ms(500);delay_ms(500);
//		Right1_Tracking();
//	}
	else if(date==0x0004)
	{
		PC_SendString((u8*)"\n\n识别到为可回收垃圾\n");
		PC_SendString((u8*)"等待垃圾放置\n\n");
		while(!RubbishFlat)
		{
			delay_ms(1);
		}
		PC_SendString((u8*)"\n\n检测已放置垃圾\n");
		PC_SendString((u8*)"正在前往可回收垃圾存放地点\n\n");
		while(1)
		{
		Right2_Tracking();
		}
	}
	}
}

//void USART1_Rx_Task(void)
//{
//	u16 posX,posY;
//	if(RxFlag1 == 1)
//	{
////		for(i=0;i<bit_number-3;i++)
////		{
////			Buf[i] = openmv[i+2];	
////		}
//		posX = RxBuffer1[3]<<8 | RxBuffer1[2];
//		posY = RxBuffer1[5]<<8 | RxBuffer1[4];
//		sprintf((char*)Buf,"     X=%03d Y=%03d      ",posX,posY);
//		LCD_DisplayStringLine(Line4 ,Buf);
////      usart_send((char *)Buf,USART1);
//		RxFlag1 = 0;
//	   	RxCounter1 = 0;
//		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	}	
//}





