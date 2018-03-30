#ifndef _VVC_UTIL_C_H
#define _VVC_UTIL_C_H

#include "global.h"

// C-languages utility method signatures.
// Restart a timer to count upwards, looping from 65535->0.
void start_timer(TIM_TypeDef *TIMx, uint16_t prescaler);
// Restart a timer to count upwareds, and trigger an interrupt
// after a certain number of cycles.
void set_timer_interrupt(TIM_TypeDef *TIMx,
                         uint16_t prescaler,
                         uint16_t period);

#endif
