#ifndef CARD_H
#define CARD_H

#include <stdint.h>

typedef enum { SUIT_CLUBS, SUIT_DIAMONDS, SUIT_HEARTS, SUIT_SPADES } Suit;

/*
 * Rank uses 1..13: 1 = Ace, 2..10 = number cards, 11 = J, 12 = Q, 13 = K.
 * Using uint8_t keeps a whole deck small (52 * 2 bytes).
 */
typedef struct {
    uint8_t rank;
    uint8_t suit;
} Card;

/* Blackjack value of a single card. Ace returns 1 here; the hand code
 * decides whether to count it as 11. */
int card_value(Card c);

#endif
