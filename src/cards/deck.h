#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_SIZE 52

typedef struct {
    Card cards[DECK_SIZE];
    int  top;          /* index of the next card to deal */
} Deck;

void deck_init(Deck *d);       /* fill with all 52 cards in order */
void deck_shuffle(Deck *d);    /* randomize order and reset top   */
Card deck_draw(Deck *d);       /* deal the next card              */
int  deck_remaining(const Deck *d);

#endif
