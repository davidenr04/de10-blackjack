#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

/* Messages shown at the end of a round. */
typedef enum { MSG_NONE, MSG_WIN, MSG_LOSE, MSG_PUSH, MSG_BUST, MSG_BJ } DisplayMsg;

void display_clear(void);

/*
 * Layout on the six 7-segment digits:
 *   HEX5 HEX4 | HEX3 HEX2 | HEX1 HEX0
 *    player   |  message  |  dealer
 * Pass a negative total to blank that side (e.g. hide dealer's hole card).
 */




void display_totals(int player_total, int dealer_total);
void display_message(DisplayMsg msg);

/* Show the player's chip count on the red LEDs (binary). */
void display_chips(int chips);

#endif
