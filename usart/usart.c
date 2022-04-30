#include "usart.h"

void USART_Config(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
    USART_InitTypeDef   USART_InitStruct;

    DEBUG_USART_GPIO_ClockCmd(DEBUG_USART_GPIO_CLK,ENABLE);
    DEBUG_USART_ClockCmd(DEBUG_USART_CLK,ENABLE);


    GPIO_InitStruct.GPIO_Pin = DEBUG_USART_TX_GPIO_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = DEBUG_USART_RX_GPIO_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);


    USART_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(DEBUG_USART_X, &USART_InitStruct);

    USART_Cmd(DEBUG_USART_X, ENABLE);                                           // 开启USART工作时钟

}

void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
  USART_SendData(pUSARTx, ch);  

  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET){

  }
}

void USART_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int t = 0;

    do
    {
        USART_SendByte(pUSARTx, *(str+t));
        t++;
    } while (*(str+t) != '\0');
    
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET){
    }
    
}
/*------------------------------------------------------------------------------------------------------------------------*/
//重定向
int fputc(int ch, FILE *f)
{
   USART_SendData(DEBUG_USART_X, (uint8_t)ch);

   while(USART_GetFlagStatus(DEBUG_USART_X, USART_FLAG_TXE) == RESET); 

   return (ch);
}

int fgetc(FILE *f)
{
    while(USART_GetFlagStatus(DEBUG_USART_X, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USART_X);
}

