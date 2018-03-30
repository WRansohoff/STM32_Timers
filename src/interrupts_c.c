#include "interrupts_c.h"

// C-language hardware interrupt method definitions.
void TIM3_IRQ_handler(void) {
  if (LL_TIM_IsActiveFlag_UPDATE(TIM3)) {
    LL_TIM_ClearFlag_UPDATE(TIM3);
    led_state = !led_state;
  }
  return;
}
