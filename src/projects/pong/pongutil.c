/*
 *date: 3/23/2017
 *author: Tasuku Miura
 */
#include "pongutil.h"
#include <curses.h>
#include <signal.h>
#include "alarmlib.h"
#include "court.h"
#include "pongglobal.h"


/*
 * Prints the current score to the screen by referencing the global variable,
 * balls_left.
 */
void print_score()
{
    move(2,2);                      /* Moves cursor to top left corner */
    addstr("                ");     /* Blanks to white out previous text */
    move(2,2);
    addstr("BALLS LEFT: ");
    char balls[2];
    snprintf(balls, 3, "%d", balls_left); 
    addstr(balls);                  /* Updates with new # of balls left */
}

/*
 * Turns alarm off, and ends the game.
 */
void end_game()
{
    move(2,2);                      /* Moves cursor to top left corner */
    addstr("                ");     /* Blanks to white out previous text */
    move(2,2);
    addstr("GAME OVER! Q to quit.");
    set_ticker(0);
}

/*
 * Initializes global variable wall_clock.
 */
void init_clock()
{
    wall_clock = time(NULL);
}

/*
 * Checks how much time has elapsed since start of game.
 */
time_t check_clock()
{
    time_t now = time(NULL);
    return now - wall_clock;
}

/*
 * Resets the global variable wall_clock.
 */
void reset_clock()
{
    wall_clock = time(NULL);
}
