#ifndef _VVC_UTIL_ASM
#define _VVC_UTIL_ASM

/*
 * Utility functions, for better legibility.
 */

.syntax unified
#ifdef VVC_F0
  .cpu cortex-m0
#elif VVC_L0
  .cpu cortex-m0plus
#elif VVC_F1
  .cpu cortex-m3
#elif  VVC_F3
  .cpu cortex-m4
#endif
.fpu softvfp
.thumb

// Instead of #include'ing this file everywhere, we can
// just declare the methods 'global' and make sure our
// Makefile compiles/links with this source file.
.global delay_cycles
.global delay_us
.global delay_ms
.global delay_s

/*
 * Delay a given number of MCU cycles.
 * Expects:
 *  r0 contains the number of cycles to wait.
 */
.type delay_cycles,%function
.section .text.delay_cycles,"ax",%progbits
delay_cycles:
  // TODO: Currently delays (r0+4) cycles, I think.
  // PUSH/LSRS/CMP/BEQ (no branch) in the beginning.
  PUSH { r0, lr }
  // Divide the number of cycles by 4 (loop takes 4 cycles)
  LSRS r0, r0, #2
  // (Pre-loop cycle, in case 0-3 is passed in)
  // CMP, BEQ (no branch) = 2 cycles.
  CMP  r0, #0
  BEQ  delay_cycles_done
  cycle_delay_loop:
  // Subtract takes 1 instruction
  SUBS r0, r0, #1
  // SUBS already sets condition flags, but this CMP makes
  // it an even four cycles per loop.
  CMP  r0, #0
  // Branch takes 2 instructions (except the last time)
  BNE  cycle_delay_loop
  delay_cycles_done:
  POP  { r0, pc }
.size delay_cycles, .-delay_cycles

/*
 * Delay a given number of microseconds.
 * TODO: Allow for PLL clock speeds other than 48MHz.
 * Expects:
 *  r0 contains the number of microseconds to wait.
 */
.type delay_us,%function
.section .text.delay_us,"ax",%progbits
delay_us:
  PUSH { r0, r1, lr }
  // @48MHz PLL, 1 microsecond should = 48 cycles.
  MOVS r1, #48
  MULS r0, r0, r1
  BL   delay_cycles
  POP  { r0, r1, pc }
.size delay_us, .-delay_us


/*
 * Delay a given number of milliseconds.
 * TODO: Allow for PLL clock speeds other than 48MHz.
 * Expects:
 *  r0 contains the number of milliseconds to wait.
 */
.type delay_ms,%function
.section .text.delay_ms,"ax",%progbits
delay_ms:
  PUSH { r0, r1, lr }
  // @48MHz PLL, 1 millisecond should = 48,000 cycles.
  LDR  r1, =0x0000BB80
  MULS r0, r0, r1
  BL   delay_cycles
  POP  { r0, r1, pc }
.size delay_ms, .-delay_ms


/*
 * Delay a given number of seconds.
 * TODO: Allow for PLL clock speeds other than 48MHz.
 * Expects:
 *  r0 contains the number of seconds to wait.
 */
.type delay_s,%function
.section .text.delay_s,"ax",%progbits
delay_s:
  PUSH { r0, r1, lr }
  // @48MHz PLL, 1 second should = 48,000,000 cycles.
  LDR  r1, =0x02DC6C00
  MULS r0, r0, r1
  BL   delay_cycles
  POP  { r0, r1, pc }
.size delay_s, .-delay_s

#endif
