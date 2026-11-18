#include "buttons.h"
#include "de10_io.h"

/*
 * In the DE10 Computer system the KEY port reads 1 while a button is held.
 * If you wire the raw KEY pins yourself they are active-LOW instead;
 * set this to 1 in that case.
 */
#define KEYS_ACTIVE_LOW 0

static uint32_t prev_state = 0;

static uint32_t read_raw(void)
{
    uint32_t v = io_read(KEY_BASE);
#if KEYS_ACTIVE_LOW
    v = ~v;
#endif
    return v & 0x3u;
}

void buttons_init(void)
{
    /* Start from the current state so a button held at reset
     * doesn't count as a press. */
    prev_state = read_raw();
}

uint32_t buttons_poll(void)
{
    uint32_t now = read_raw();

    /*
     * TODO: Edge detection. Return only the buttons that are down NOW
     * but were up LAST time:
     *
     *     pressed = now & ~prev_state;
     *
     * Then save `now` into prev_state for the next call.
     *
     * Without this, holding KEY0 for half a second would "hit" thousands
     * of times because the main loop runs very fast.
     *
     * Bonus: mechanical buttons "bounce". If you see double presses,
     * ignore changes that happen within ~10-20 ms of the last one.
     */
    (void)now;
    return 0;
}
