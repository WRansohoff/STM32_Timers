#include "main.h"

/**
 * Main program.
 */
int main(void) {
  // Define starting values for global variables.
  tim_counter = 0;
  led_state = 0;

  // Enable the GPIOA clock (use pin A0 for now.)
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // Enable the TIM3 clock.
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  // Enable the SYSCFG clock for hardware interrupts.
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // Setup GPIO pin A12 as push-pull output, no pupdr,
  // 10MHz max speed.
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_MEDIUM);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_12, LL_GPIO_PULL_NO);

  // Enable the TIM3 NVIC channel.
  NVIC_SetPriority(TIM3_IRQn, 0x03);
  NVIC_EnableIRQ(TIM3_IRQn);
  // Setup the TIM3 timer as a counter.
  //start_timer(TIM3, 0x400);
  uint16_t interrupt_period = 16384;
  set_timer_interrupt(TIM3, 0x400, interrupt_period);

  while (1) {
    // Get the current timer counter value.
    // This can act as a PRNG counter.
    tim_counter = LL_TIM_GetCounter(TIM3);

    if (led_state) {
      GPIOA->ODR |= LL_GPIO_PIN_12;
    }
    else {
      GPIOA->ODR &= ~LL_GPIO_PIN_12;
    }

    // Delay?
    //delay_us(250);
  }

  return 0;
}
