/*
 * Defines the functions related to the ball object.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#include "ball.h"
#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "alarmlib.h"
#include "court.h"
#include "pongglobal.h"
#include "pongutil.h"

/*
 * SIGALRM handler: ball moves when alarm signal is intercepted. Handle signal
 * and resets the handler after done with acting accordingly.
 */ 
void ball_move(int s)
{
    int y_cur, x_cur, moved;

    signal(SIGALRM , SIG_IGN);                  /* Ignores any other alarms*/
    y_cur = the_ball.y_pos ;                    /* Old location of ball */
    x_cur = the_ball.x_pos ;
    moved = 0 ;

    if (the_ball.y_delay > 0 && --the_ball.y_count == 0) {
        the_ball.y_pos += the_ball.y_dir ;      /* move */
        the_ball.y_count = the_ball.y_delay  ;  /* reset*/
        moved = 1;
    }

    if (the_ball.x_delay > 0 && --the_ball.x_count == 0) {
        the_ball.x_pos += the_ball.x_dir;       /* move */
        the_ball.x_count = the_ball.x_delay;    /* reset*/
        moved = 1;
    }

    if (moved){
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        if (bounce_or_lose( &the_ball ) == LOSE) {
            if (balls_left > 0) {
                balls_left--;
                mvaddch(the_ball.y_pos, the_ball.x_pos, BLANK);
                print_score();
                reset_clock();
                the_ball.y_pos = Y_INIT;            /* reinitialize */
                the_ball.x_pos = X_INIT;
                the_ball.y_delay = rand() % 10 + 1; /* generate random direction */
                the_ball.x_delay = rand() % 10 + 1;
            } else {
                end_game();
            }
        }
        move(LINES-1, COLS-1);                  /* park cursor  */
        refresh();
    }
    
    //TODO: clock is referencing the Epoch. Need to convert implementation to
    //one that represents time that has passed locally.
    time_t clock_time = check_clock();
    move(2,COLS - 30);
    addstr(ctime(&clock_time));
    move(LINES-1, COLS-1);
    refresh();

    signal(SIGALRM, ball_move);                 /* re-enable handler    */
}

/* bounce_or_lose: if ball hits walls, change its direction
 * @args: address to ppball
 * @rets: 1 if a bounce happened, 0 if not
 */
int bounce_or_lose(struct ppball *bp)
{
    int return_val = NOBOUNCE;

    if (bp->y_pos < the_court.top_edge + 2)
        bp->y_dir = 1 , return_val = BOUNCE;
    else if (bp->y_pos > the_court.bot_edge - 2)
        bp->y_dir = -1 , return_val = BOUNCE;

    if ( bp->x_pos < the_court.left_edge + 2)
        bp->x_dir = 1 , return_val = BOUNCE;
    else if ( bp->x_pos > the_court.right_edge - 2) {
        if (bp->y_pos >= the_paddle.pad_top
            && bp->y_pos <= the_paddle.pad_bot) {
            bp->x_dir = -1, return_val = BOUNCE;
        } else {
            return_val = LOSE;
        }
    }

    return return_val;
}
