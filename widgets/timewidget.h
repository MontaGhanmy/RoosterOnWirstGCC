#include <stm32f4xx.h>
#include <misc.h>			 // I recommend you have a look at these in the ST firmware folder
#include <stm32f4xx_adc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx_pwr.h>

#define RTC_CLOCK_SOURCE_LSI            /* LSI used as RTC source clock */
#define FIRST_DATA         0x4321

void RTC_Configuration(int hours, int minutes);
void TimeWidget();
