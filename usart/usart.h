#ifndef __USART_H
#define __USART_H
/*------------------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
/*------------------------------------------------------------------------------------------------------------------------*/
//GPIO CLK
#define DEBUG_USART_GPIO_ClockCmd           RCC_APB2PeriphClockCmd
#define DEBUG_USART_GPIO_CLK                RCC_APB2Periph_GPIOA
//USART CLK
#define DEBUG_USART_ClockCmd                RCC_APB2PeriphClockCmd
#define DEBUG_USART_CLK                     RCC_APB2Periph_USART1
/*------------------------------------------------------------------------------------------------------------------------*/
//GPIO_PORT AND GPIO_PIN
#define DEBUG_USART_TX_GPIO_PORT            GPIOA
#define DEBUG_USART_TX_GPIO_Pin             GPIO_Pin_9

#define DEBUG_USART_RX_GPIO_PORT            GPIOA
#define DEBUG_USART_RX_GPIO_Pin             GPIO_Pin_10
/*------------------------------------------------------------------------------------------------------------------------*/
//USART_CONFIG
#define DEBUG_USART_BAUDRATE                115200
#define DEBUG_USART_X                       USART1

/*------------------------------------------------------------------------------------------------------------------------*/
void USART_Config(void);
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void USART_SendString(USART_TypeDef *pUSARTx, char *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
#endif /* __USART_H */
