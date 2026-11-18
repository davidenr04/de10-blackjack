#include "de10_io.h"

uint32_t switches_read(void)
{
    /* Only the low 10 bits are wired to SW0..SW9. */
    return io_read(SW_BASE) & 0x3FFu;
}

void leds_write(uint32_t pattern)
{
    io_write(LEDR_BASE, pattern & 0x3FFu);
}
