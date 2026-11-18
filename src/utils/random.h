#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

/*
 * Small pseudo-random number generator (xorshift32).
 * We don't have rand()/time() seeding on bare-metal, so we roll our own.
 * Seed it with something unpredictable, e.g. a counter that runs while
 * the player waits to press the first button.
 */
void     rng_seed(uint32_t seed);
uint32_t rng_next(void);
uint32_t rng_range(uint32_t n);   /* returns a value in [0, n) */

#endif
