#ifndef DEALER_H
#define DEALER_H

#include <stdbool.h>
#include "player.h"
#include "../cards/deck.h"

typedef struct {
    Hand hand;
    bool hole_revealed;   /* false until the player's turn is over */
} Dealer;

void dealer_init(Dealer *d);
bool dealer_should_hit(const Dealer *d);
void dealer_play(Dealer *d, Deck *deck);

#endif
