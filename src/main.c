/*
 * DE10 Blackjack
 *
 * Controls:
 *   SW9..SW0  set your bet (binary, max MAX_BET)
 *   KEY1      deal / stand / next round
 *   KEY0      hit
 *
 * Display:
 *   HEX5-4 = your total, HEX3-2 = result message, HEX1-0 = dealer total
 *   LEDR   = your chips (binary)
 */
#include "game/blackjack.h"
#include "hardware/buttons.h"
#include "hardware/de10_io.h"

int main(void)
{
    Game game;

    buttons_init();
    game_init(&game);

    /* Bare-metal programs never return: loop forever. */
    while (1) {
        uint32_t pressed  = buttons_poll();
        uint32_t switches = switches_read();
        game_step(&game, pressed, switches);
    }

    return 0;   /* never reached */
}
