#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

/* Bit masks for the push buttons. DE10-Lite only has KEY0 and KEY1,
 * so the game is designed around those two. */
#define BTN_HIT    (1u << 0)   /* KEY0 */
#define BTN_STAND  (1u << 1)   /* KEY1 (also "deal" / "next round") */

void     buttons_init(void);

/* Returns a mask of buttons that were PRESSED since the last call
 * (a press is reported once, not every loop while held down). */
uint32_t buttons_poll(void);

#endif
