#ifndef _VVC_GLOBAL_H
#define _VVC_GLOBAL_H

#include <stdio.h>

// Core includes.
#ifdef VVC_F0
  #include "stm32f0xx.h"
#elif VVC_F3
  // TODO: Support F3 chips
  #include "stm32f3xx.h"
#endif
#include "stm32_assert.h"

// LL/HAL includes.
#ifdef VVC_F0
  #include "stm32f0xx_ll_gpio.h"
  #include "stm32f0xx_ll_rcc.h"
  #include "stm32f0xx_ll_system.h"
  #include "stm32f0xx_ll_tim.h"
#elif VVC_F3
  #include "stm32f3xx_ll_gpio.h"
  #include "stm32f3xx_ll_rcc.h"
  #include "stm32f3xx_ll_system.h"
  #include "stm32f3xx_ll_tim.h"
#endif

// Assembly methods.
extern void delay_cycles(unsigned int d);
extern void delay_us(unsigned int d);
extern void delay_ms(unsigned int d);
extern void delay_s(unsigned int d);

// ----------------------
// Global variables.
uint32_t tim_counter;
unsigned char led_state;
// Global TIM (timer) initialization struct.
LL_TIM_InitTypeDef  timer_init_struct;

#endif
