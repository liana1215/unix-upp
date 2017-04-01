/*
 * Functions related to paddle used in one man pong.
 * date: 3/28/2017
 * author: Tasuku Miura
 */

#include "paddle.h"
#include "pongglobal.h"
#include <curses.h>


static void draw_paddle(int top, int bot, int col, char symbol)
/*
 * Draws paddle on screen.
 * @args: top - location of top end of paddle.
 * @args: bot - location of bottom end of paddle.
 * @args: col - location of paddle on court.
 * @args: symbol - symbol to use to draw/clear paddle.
 */
{
    int r;
    for (r = top; r < bot; r++)
        mvaddch(r, col, symbol);
}
    
static void clear_paddle()
/*
 * Clears paddle from screen.
 */
{
    draw_paddle(the_paddle.pad_top, the_paddle.pad_bot, 
                the_paddle.pad_col, ' ');
}

/* 
 * Initializes paddle on the screen by initializing the global struct.
 */
void paddle_init()
{
    the_paddle.pad_top = LINES / 2;
    the_paddle.pad_len = PADLEN;
    the_paddle.pad_bot = the_paddle.pad_top + the_paddle.pad_len;
    the_paddle.pad_col = COLS - 5;
    the_paddle.pad_char = PAD_SYMBOL;

    draw_paddle(the_paddle.pad_top, the_paddle.pad_bot, 
                the_paddle.pad_col, the_paddle.pad_char);

}

/*
 * Moves paddle up by one unit, if not at top edge.
 */
void paddle_up()
{
    
    clear_paddle();

    if (the_paddle.pad_top - 1 > the_court.top_edge) {
        the_paddle.pad_top -= 1;
        the_paddle.pad_bot = the_paddle.pad_top + the_paddle.pad_len;
    }

    draw_paddle(the_paddle.pad_top, the_paddle.pad_bot, 
                the_paddle.pad_col, the_paddle.pad_char);
}

/*
 * Moves paddle down by one unit, if not at bottom edge.
 */
void paddle_down()
{
    clear_paddle();

    if (the_paddle.pad_bot < the_court.bot_edge) {
        the_paddle.pad_top += 1;
        the_paddle.pad_bot = the_paddle.pad_top + the_paddle.pad_len;
    }

    draw_paddle(the_paddle.pad_top, the_paddle.pad_bot, 
                the_paddle.pad_col, the_paddle.pad_char);
}
