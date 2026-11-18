#include "dealer.h"

void dealer_init(Dealer *d)
{
    hand_clear(&d->hand);
    d->hole_revealed = false;
}

bool dealer_should_hit(const Dealer *d)
{
    /*
     * TODO: House rule: the dealer must hit on 16 or less and stand on 17+.
     *
     * Optional extra: some casinos make the dealer hit "soft 17"
     * (a 17 that includes an ace counted as 11, e.g. A + 6).
     * Get the basic rule working first.
     */
    (void)d;
    return false;
}

void dealer_play(Dealer *d, Deck *deck)
{
    /* The dealer flips the face-down card before drawing. */
    d->hole_revealed = true;

    /*
     * TODO: Keep drawing cards into d->hand while dealer_should_hit()
     * says to. Use deck_draw(deck) and hand_add().
     */
    (void)deck;
}
