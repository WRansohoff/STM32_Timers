#include "util_c.h"

// Restart a timer using the LL library to count upwards.
void start_timer(TIM_TypeDef *TIMx, uint16_t prescaler) {
  // Ensure the timer is off.
  LL_TIM_DeInit(TIMx);
  // Use a prescaler of 1, for a fast clock.
  // @48MHz PLL, this comes out to about .02 us I think.
  timer_init_struct.Prescaler = prescaler;
  // Set the timer to count upwards.
  timer_init_struct.CounterMode = LL_TIM_COUNTERMODE_UP;
  // We won't be using 'autoreload'. Just reset at max value.
  timer_init_struct.Autoreload = 0xFFFF;
  // Set clock division to trigger on every event.
  timer_init_struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  // Set the repetition counter to 0; unused.
  timer_init_struct.RepetitionCounter = 0x00;
  // Initialize the peripheral.
  LL_TIM_Init(TIMx, &timer_init_struct);
  // Then finally, enable the timer.
  LL_TIM_EnableCounter(TIMx);
}

// Set a timer to trigger an 'update' interrupt after
// a given number of cycles at a certain prescaler.
// Note that this will not enable the NVIC channel.
void set_timer_interrupt(TIM_TypeDef *TIMx,
                         uint16_t prescaler,
                         uint16_t period) {
  // Ensure the timer is off.
  LL_TIM_DeInit(TIMx);
  // Use a prescaler of 1, for a fast clock.
  // @48MHz PLL, this comes out to about .02 us I think.
  timer_init_struct.Prescaler = prescaler;
  // Set the timer to count upwards.
  timer_init_struct.CounterMode = LL_TIM_COUNTERMODE_UP;
  // We won't be using 'autoreload'. Just reset at max value.
  timer_init_struct.Autoreload = period;
  // Set clock division to trigger on every event.
  timer_init_struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  // Set the repetition counter to 0; unused.
  timer_init_struct.RepetitionCounter = 0x00;
  // Initialize the peripheral.
  LL_TIM_Init(TIMx, &timer_init_struct);
  // Next, enable the 'Update' timer interrupt.
  LL_TIM_EnableIT_UPDATE(TIMx);
  // Then finally, enable the timer.
  LL_TIM_EnableCounter(TIMx);
}
