#include "blackjack.h"
#include "../utils/random.h"
#include "../hardware/buttons.h"

/* ---------- helpers ---------- */

/* Push the current game state out to the 7-seg displays and LEDs. */
static void refresh_display(const Game *g)
{
    int player_total = hand_value(&g->player.hand);
    int dealer_total;

    if (g->dealer.hole_revealed) {
        dealer_total = hand_value(&g->dealer.hand);
    } else if (g->dealer.hand.count > 0) {
        /* Only the up-card is visible during the player's turn. */
        dealer_total = card_value(g->dealer.hand.cards[0]);
    } else {
        dealer_total = -1;   /* blank */
    }

    display_totals(player_total, dealer_total);
    display_message(g->last_msg);
    display_chips(g->player.chips);
}

static void deal_initial_cards(Game *g)
{
    hand_clear(&g->player.hand);
    dealer_init(&g->dealer);

    /*
     * TODO: Deal the opening hands, alternating like a real table:
     *   player, dealer, player, dealer
     * Use deck_draw(&g->deck) and hand_add().
     *
     * Tip: reshuffle first if the deck is running low, e.g.
     *   if (deck_remaining(&g->deck) < 15) deck_shuffle(&g->deck);
     */
}

/*
 * Decide who won, pay out chips, and return the message to show.
 * Remember the bet was already subtracted in player_place_bet(), so:
 *   lose        -> add nothing
 *   push (tie)  -> give the bet back           (+bet)
 *   win         -> bet back + equal winnings   (+2 * bet)
 *   blackjack   -> bet back + 3:2 winnings     (+bet + bet*3/2)
 */
static DisplayMsg resolve_round(Game *g)
{
    const Hand *ph = &g->player.hand;
    const Hand *dh = &g->dealer.hand;
    int bet = g->player.bet;

    /*
     * TODO: Check these cases IN THIS ORDER (order matters!):
     *   1. Player bust                 -> MSG_BUST (dealer wins even if
     *                                     the dealer would also bust)
     *   2. Player and dealer both have blackjack -> MSG_PUSH
     *   3. Player blackjack only        -> MSG_BJ, pay 3:2
     *   4. Dealer bust                  -> MSG_WIN
     *   5. Compare hand_value() totals  -> MSG_WIN / MSG_LOSE / MSG_PUSH
     * Add chips to g->player.chips for each case using the table above.
     */
    (void)ph; (void)dh; (void)bet;

    g->player.bet = 0;
    return MSG_NONE;
}

/* ---------- public API ---------- */

void game_init(Game *g)
{
    deck_init(&g->deck);
    player_init(&g->player, STARTING_CHIPS);
    dealer_init(&g->dealer);
    g->state    = STATE_BETTING;
    g->last_msg = MSG_NONE;
    g->ticks    = 0;
    g->seeded   = false;
    display_clear();
    display_chips(g->player.chips);
}

void game_step(Game *g, uint32_t pressed, uint32_t switches)
{
    g->ticks++;

    switch (g->state) {

    case STATE_BETTING: {
        /* Bet comes from the slide switches (binary), capped to a sane range. */
        int bet = (int)switches;
        if (bet > MAX_BET)        bet = MAX_BET;
        if (bet > g->player.chips) bet = g->player.chips;

        /* Preview the bet on the left display while choosing. */
        display_totals(bet, -1);

        if (pressed & BTN_STAND) {
            /* First deal: seed RNG from how long the player took.
             * Human timing is unpredictable, so every game differs. */
            if (!g->seeded) {
                rng_seed(g->ticks);
                deck_shuffle(&g->deck);
                g->seeded = true;
            }

            if (player_place_bet(&g->player, bet)) {
                g->last_msg = MSG_NONE;
                deal_initial_cards(g);

                /* A natural 21 ends the player's turn immediately. */
                if (hand_is_blackjack(&g->player.hand)) {
                    g->state = STATE_DEALER_TURN;
                } else {
                    g->state = STATE_PLAYER_TURN;
                }
                refresh_display(g);
            }
        }
        break;
    }

    case STATE_PLAYER_TURN:
        if (pressed & BTN_HIT) {
            hand_add(&g->player.hand, deck_draw(&g->deck));
            if (hand_is_bust(&g->player.hand)) {
                /* No need for the dealer to play; go straight to results. */
                g->dealer.hole_revealed = true;
                g->last_msg = resolve_round(g);
                g->state    = STATE_RESULT;
            }
            refresh_display(g);
        }
        /*
         * TODO: Handle BTN_STAND: move to STATE_DEALER_TURN.
         *
         * Optional: auto-stand when the player reaches exactly 21.
         */
        break;

    case STATE_DEALER_TURN:
        dealer_play(&g->dealer, &g->deck);
        g->last_msg = resolve_round(g);
        g->state    = STATE_RESULT;
        refresh_display(g);
        break;

    case STATE_RESULT:
        /* Leave the result up until the player presses KEY1. */
        if (pressed & BTN_STAND) {
            g->state = (g->player.chips > 0) ? STATE_BETTING : STATE_GAME_OVER;
            g->last_msg = MSG_NONE;
            display_clear();
            display_chips(g->player.chips);
        }
        break;

    case STATE_GAME_OVER:
        /*
         * TODO (optional): show something fun, e.g. flash the LEDs,
         * and let KEY1 restart with game_init(g).
         */
        break;
    }
}
