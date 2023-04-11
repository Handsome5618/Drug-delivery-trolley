#include "stm32f10x.h"                  // Device header
#include "usart3.h"
#include "delay.h"

u8 num;
u8 Date[4];
u8 flat;
u8 PassFlag;

void USART3_Config(void)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能USART3，GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    //USART3_TX   GPIOB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10

    //USART3_RX	  GPIOB.11初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11

    //Usart1 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    //USART 初始化设置

    USART_InitStructure.USART_BaudRate = 9600;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口3
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART3, ENABLE);                    //使能串口3
}
void PC_SendChar(uint8_t DataToSend)

{

    USART_SendData (USART3 ,DataToSend);

    while((USART3->SR&0x40)==0 );

}
void PC_SendString(uint8_t *str)
{

    while(*str)

    {

        PC_SendChar (*str);

        str++;

    }

}

/*发送一个字节数据*/
void UART3SendByte(unsigned char SendData)
{
    USART_SendData(USART3,SendData);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/*接收一个字节数据*/
unsigned char UART3GetByte(unsigned char* GetData)
{
    if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
    {   return 0;//没有收到数据
    }
    *GetData = USART_ReceiveData(USART3);
    return 1;//收到数据
}
/*接收一个数据，马上返回接收到的这个数据*/
void UART3Test(void)
{
    unsigned char i = 0;

    while(1)
    {
        while(UART3GetByte(&i))
        {
            USART_SendData(USART3,i);
        }
    }
}

void Receive_Data(int16_t data)
{
	static u8 state = 0;
	num = data;
	if(state == 0 && data != 0)
	{
		num = data;
		state = 1;
	}
	
	else if(state == 1 && data != 0 && PassFlag == 1)
	{
		Date[0] = data;
		state = 2;
	}
	
	else if(state == 2 && data != 0 && PassFlag == 1)
	{
		Date[1] = data;
		state = 3;
	}
	
	else if(state == 3 && data != 0 && PassFlag == 1)
	{
		Date[2] = data;
		state = 1;
	}
}

void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 temp;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        USART_ClearFlag(USART3,USART_FLAG_RXNE);
		flat = 1;
		temp = USART_ReceiveData(USART3);
		Receive_Data(temp);
    }
}
