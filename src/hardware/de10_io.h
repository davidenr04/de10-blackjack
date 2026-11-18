#ifndef DE10_IO_H
#define DE10_IO_H

#include <stdint.h>

/*
 * Memory-mapped I/O addresses for the Intel FPGA University Program
 * "DE10 Computer" system (same map on DE10-Lite / DE10-Standard).
 * If you built your own Platform Designer system, copy the base
 * addresses from your system.h / .sopcinfo instead.
 */
#define LEDR_BASE     0xFF200000u   /* 10 red LEDs                       */
#define HEX3_0_BASE   0xFF200020u   /* 7-seg HEX3..HEX0, one byte each   */
#define HEX5_4_BASE   0xFF200030u   /* 7-seg HEX5..HEX4                  */
#define SW_BASE       0xFF200040u   /* 10 slide switches                 */
#define KEY_BASE      0xFF200050u   /* push buttons                      */

/*
 * `volatile` tells the compiler every read/write really touches hardware,
 * so it must not cache the value in a register or optimize it away.
 */

 
#define REG32(addr) (*(volatile uint32_t *)(uintptr_t)(addr))

static inline uint32_t io_read(uint32_t addr)              { return REG32(addr); }
static inline void     io_write(uint32_t addr, uint32_t v) { REG32(addr) = v; }

uint32_t switches_read(void);
void     leds_write(uint32_t pattern);

#endif
