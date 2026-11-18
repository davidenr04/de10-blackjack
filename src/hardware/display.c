#include "display.h"
#include "de10_io.h"

/*
 * Segment bit order (1 = segment ON in the DE10 Computer HEX ports):
 *
 *       --0--
 *      |     |
 *      5     1
 *      |--6--|
 *      4     2
 *      |     |
 *       --3--
 */
static const uint8_t DIGIT_SEGS[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,   /* 0-4 */
    0x6D, 0x7D, 0x07, 0x7F, 0x6F    /* 5-9 */
};

/* A few letters for the result messages. */
#define SEG_BLANK 0x00
#define SEG_A     0x77
#define SEG_b     0x7C
#define SEG_E     0x79
#define SEG_H     0x76
#define SEG_J     0x1E
#define SEG_L     0x38
#define SEG_n     0x54
#define SEG_o     0x5C
#define SEG_P     0x73
#define SEG_S     0x6D
#define SEG_t     0x78
#define SEG_U     0x3E

/* Shadow copy of what's on each digit (index 0 = HEX0 ... 5 = HEX5).
 * The hardware packs several digits into one register, so we keep a
 * copy and rewrite the whole register whenever one digit changes. */
static uint8_t hex[6];

static void flush(void)
{
    uint32_t lo = (uint32_t)hex[0]       | (uint32_t)hex[1] << 8 |
                  (uint32_t)hex[2] << 16 | (uint32_t)hex[3] << 24;
    uint32_t hi = (uint32_t)hex[4]       | (uint32_t)hex[5] << 8;
    io_write(HEX3_0_BASE, lo);
    io_write(HEX5_4_BASE, hi);
}

/* Write a 0..99 number into two adjacent digits starting at `pos`. */
static void put_two_digits(int pos, int value)
{
    if (value < 0) {                 /* negative = blank */
        hex[pos] = hex[pos + 1] = SEG_BLANK;
        return;
    }
    if (value > 99) value = 99;
    hex[pos]     = DIGIT_SEGS[value % 10];
    /* Leading zero is blanked so "7" shows as " 7", not "07". */
    hex[pos + 1] = (value >= 10) ? DIGIT_SEGS[value / 10] : SEG_BLANK;
}

void display_clear(void)
{
    for (int i = 0; i < 6; i++) hex[i] = SEG_BLANK;
    flush();
}

void display_totals(int player_total, int dealer_total)
{
    put_two_digits(4, player_total);   /* HEX5-HEX4 */
    put_two_digits(0, dealer_total);   /* HEX1-HEX0 */
    flush();
}

void display_message(DisplayMsg msg)
{
    /*
     * The message area is only two digits (HEX3 = hex[3], HEX2 = hex[2]),
     * so use two-letter abbreviations.
     *
     * Already done as an example:
     */
    switch (msg) {
    case MSG_WIN:
        hex[3] = SEG_U;  hex[2] = SEG_U;   /* "UU" looks like a W */
        break;

    /*
     * TODO: Fill in the rest using the SEG_ letters above, e.g.
     *   MSG_LOSE -> "Lo"
     *   MSG_PUSH -> "PU"
     *   MSG_BUST -> "bU"
     *   MSG_BJ   -> "bJ"
     * Feel free to add new SEG_ letters (light the segments you want
     * using the bit diagram at the top of this file).
     */

    case MSG_NONE:
    default:
        hex[3] = SEG_BLANK; hex[2] = SEG_BLANK;
        break;
    }
    flush();
}

void display_chips(int chips)
{
    /* 10 LEDs can show 0..1023 in binary. */
    if (chips < 0) chips = 0;
    leds_write((uint32_t)chips);
}
