#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx_pwr.h>
#include <keyinputs.h>
#include <bluetooth_usart.h>
#include <timewidget.h>
#include <math.h>
#include <ili9163.h>

int main(void)
{
	initGPIO();
	initDMA();
	initSPI3();
	init_USART1(9600);
	initLCD();
	initButton();
	USART_puts(USART1, "Connected. Welcome!");
	SetScrn(Black);
	setMainScreen(0,0);
	RTC_Configuration(00,05);
	TimeWidget();
    return 1;
}
