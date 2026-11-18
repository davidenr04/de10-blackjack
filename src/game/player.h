#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "../cards/card.h"

/* 11 cards is the most a hand can hold without busting (A,A,A,A,2,2,2,2,3,3,3 = 21). */
#define MAX_HAND 11

typedef struct {
    Card cards[MAX_HAND];
    int  count;
} Hand;

typedef struct {
    Hand hand;
    int  chips;   /* bankroll */
    int  bet;     /* amount wagered this round */
} Player;

/* ---- Hand helpers (shared by player and dealer) ---- */
void hand_clear(Hand *h);
void hand_add(Hand *h, Card c);
int  hand_value(const Hand *h);       /* best total, aces counted as 1 or 11 */
bool hand_is_bust(const Hand *h);
bool hand_is_blackjack(const Hand *h);

/* ---- Player ---- */
void player_init(Player *p, int starting_chips);
bool player_place_bet(Player *p, int amount);

#endif
