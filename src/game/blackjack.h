#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdint.h>
#include <stdbool.h>
#include "player.h"
#include "dealer.h"
#include "../cards/deck.h"
#include "../hardware/display.h"

#define STARTING_CHIPS 100
#define MAX_BET        50

/*
 * The game is a state machine. Each call to game_step() looks at the
 * current state + which buttons were pressed and decides what to do next.
 *
 *   BETTING --(KEY1)--> PLAYER_TURN --(KEY1 stand)--> DEALER_TURN --> RESULT
 *                          |  ^                                        |
 *                          |  +--(KEY0 hit, not bust)                  |
 *                          +--(bust or blackjack)--------------------->+
 *   RESULT --(KEY1)--> BETTING   (or GAME_OVER if out of chips)
 */
typedef enum {
    STATE_BETTING,
    STATE_PLAYER_TURN,
    STATE_DEALER_TURN,
    STATE_RESULT,
    STATE_GAME_OVER
} GameState;

typedef struct {
    GameState  state;
    Deck       deck;
    Player     player;
    Dealer     dealer;
    DisplayMsg last_msg;
    uint32_t   ticks;       /* loop counter, used to seed the RNG */
    bool       seeded;
} Game;

void game_init(Game *g);
void game_step(Game *g, uint32_t pressed_buttons, uint32_t switches);

#endif
