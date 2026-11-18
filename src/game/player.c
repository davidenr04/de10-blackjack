#include "player.h"

void hand_clear(Hand *h)
{
    h->count = 0;
}

void hand_add(Hand *h, Card c)
{
    /* Silently ignore overflow; a legal hand never gets this big. */
    if (h->count < MAX_HAND) {
        h->cards[h->count++] = c;
    }
}

int hand_value(const Hand *h)
{
    /*
     * TODO: Return the best blackjack total for this hand.
     *
     * Steps:
     *   1. Add up card_value() for every card (aces count as 1).
     *   2. Count how many aces are in the hand.
     *   3. If there's at least one ace and total + 10 <= 21,
     *      add 10 (that ace now counts as 11).
     *
     * You only ever need to upgrade ONE ace: two aces as 11 would be 22.
     *
     * Examples to test with:
     *   A, K       -> 21
     *   A, A, 9    -> 21
     *   A, 6, 9    -> 16
     *   K, Q, 5    -> 25
     */
    (void)h;
    return 0;
}

bool hand_is_bust(const Hand *h)
{
    return hand_value(h) > 21;
}

bool hand_is_blackjack(const Hand *h)
{
    /*
     * TODO: A "blackjack" (natural) is exactly 2 cards totalling 21.
     * A 3-card 21 is NOT a blackjack.
     */
    (void)h;
    return false;
}

void player_init(Player *p, int starting_chips)
{
    hand_clear(&p->hand);
    p->chips = starting_chips;
    p->bet   = 0;
}

bool player_place_bet(Player *p, int amount)
{
    /* Reject bets the player can't cover or that make no sense. */
    if (amount <= 0 || amount > p->chips) {
        return false;
    }
    /* Take the chips off the table now; payouts add them back later. */
    p->chips -= amount;
    p->bet    = amount;
    return true;
}
