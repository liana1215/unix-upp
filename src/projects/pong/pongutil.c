/*
 *date: 3/23/2017
 *author: Tasuku Miura
 */
#include "pongutil.h"
#include <curses.h>
#include "pongglobal.h"

/*
 * Prints the current score to the screen by referencing the global variable,
 * balls_left.
 */
void print_score()
{
    move(2,2);
    addstr("                ");
    move(2,2);
    addstr("BALLS LEFT: ");
    char balls[2];
    snprintf(balls, 3, "%d", balls_left);
    addstr(balls);
}

