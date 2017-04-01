/*
 * Paddle definition and related functions.
 * date: 3/28/2017
 * author: Tasuku Miura
 */

#ifndef PADDLE_H
#define PADDLE_H

#define PADLEN      6
#define PAD_SYMBOL '#'

struct pppaddle {
    int pad_top, pad_bot, pad_col, pad_len;
    char pad_char;   /*symbol to use for paddle*/
};

void paddle_init();
void paddle_up();
void paddle_down();

#endif
