#include "deck.h"
#include "../utils/random.h"

void deck_init(Deck *d)
{
    int i = 0;
    /* One card for every suit/rank combination: 4 * 13 = 52. */
    for (int suit = SUIT_CLUBS; suit <= SUIT_SPADES; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            d->cards[i].rank = (uint8_t)rank;
            d->cards[i].suit = (uint8_t)suit;
            i++;
        }
    }
    d->top = 0;
}

void deck_shuffle(Deck *d)
{
    /*
     * TODO: Implement a Fisher-Yates shuffle.
     *
     *   for i from DECK_SIZE-1 down to 1:
     *       j = rng_range(i + 1)      // random index 0..i
     *       swap d->cards[i] and d->cards[j]
     *
     * Then reset d->top to 0 so dealing starts from the top again.
     *
     * Why Fisher-Yates? Every ordering is equally likely. "Swap each card
     * with any random card" looks similar but is biased.
     */
    d->top = 0;
}

Card deck_draw(Deck *d)
{
    /* If we've run out, reshuffle the same 52 cards and keep going.
     * (Simple approach: the game should also reshuffle between rounds.) */
    if (d->top >= DECK_SIZE) {
        deck_shuffle(d);
    }
    return d->cards[d->top++];
}

int deck_remaining(const Deck *d)
{
    return DECK_SIZE - d->top;
}
