#include "card.h"

int card_value(Card c)
{
    /* Face cards (J, Q, K) are all worth 10. */
    if (c.rank >= 10) {
        return 10;
    }
    /* Ace (1) and 2..9 are worth their rank. Ace-as-11 is handled in
     * hand_value() because it depends on the rest of the hand. */
    return c.rank;
}
