#include "random.h"

/* Internal state. Must never be 0 or xorshift gets stuck at 0 forever. */
static uint32_t state = 0x12345678u;

void rng_seed(uint32_t seed)
{
    /* Guard against a zero seed (see note above). */
    state = (seed != 0) ? seed : 0x12345678u;
}

uint32_t rng_next(void)
{
    /* xorshift32: three shift/XOR steps scramble the bits. */
    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}

uint32_t rng_range(uint32_t n)
{
    /* Modulo has a tiny bias for non-power-of-two n; fine for a card game. */
    return (n == 0) ? 0 : rng_next() % n;
}
