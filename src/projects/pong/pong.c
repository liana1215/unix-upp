/* One player pong, based on helper code found in the book by Bruce Molay
 * Understanding Unix/Linux Programming.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#include    <stdio.h>
#include    <curses.h>
#include    <signal.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    "alarmlib.h"
#include    "ball.h"
#include    "court.h"
#include    "paddle.h"
#include    "pongglobal.h"
#include    "pongutil.h"
/*
 *  pong 1.0    
 *
 *  user input:
 *          m move paddle down, k: move paddle up
 *          Q quit
 *
 *  blocks on read, but timer tick sets SIGALRM which are caught
 *  by ball_move
 */

struct ppball the_ball ;
struct ppcourt the_court;
struct pppaddle the_paddle;
int balls_left = 10;
time_t wall_clock = 0;

/** the main loop **/

int main()
{
    int c;
    void    set_up();

    set_up();

    while ( balls_left > 0 && ( c = getch()) != 'Q' ){
        if ( c == 'k' ) 
            paddle_up();
        else if ( c == 'm' ) 
            paddle_down();
    }
    wrap_up();
    return 0;
}

