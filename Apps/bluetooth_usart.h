#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>

void USART1_IRQHandler(void);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void init_USART1(uint32_t baudrate);
