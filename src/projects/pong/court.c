/*
 * Definition of functions related to the court object.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#include "court.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include "alarmlib.h"
#include "pongglobal.h"
#include "pongutil.h"


/*
 * Set up the court, and initialize related objects to play the game of single
 * player pong.
 */
void set_up()
{
    srand(getpid());


    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_count = the_ball.y_delay = rand()%10+1;
    the_ball.x_count = the_ball.x_delay = rand()%10+1;
    the_ball.y_dir = 1 ;
    the_ball.x_dir = 1;
    the_ball.symbol = BALL_SYMBOL ;

    initscr();                  /* Turn on curses */
    noecho();                   /* Turn off echo  */
    cbreak();                   /* Turn off buffering */

    signal(SIGINT, SIG_IGN);    /* Ignore SIGINT */
    mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);

    int row = LINES - COURT_PAD;
    int col = COLS - COURT_PAD;
    the_court.top_edge = COURT_PAD;
    the_court.left_edge = COURT_PAD;
    the_court.bot_edge = row;
    the_court.right_edge = col;
    the_court.vert_char = VERT_SYMBOL;
    the_court.hori_char = HORI_SYMBOL;

    
    int r, c;                   
    for (r = COURT_PAD; r < row; r++) { /* Draw vertical edge */
        mvaddch(r, COURT_PAD, the_court.vert_char);
    }
                                    
    for (c = COURT_PAD; c < col; c++) { /* Draw horizontal edge */
        mvaddch(COURT_PAD, c, the_court.hori_char);
        mvaddch(row, c, the_court.hori_char);
    }

    print_score();
    paddle_init();
    init_clock();
    refresh();

  
    signal(SIGALRM, ball_move);
    set_ticker( 1000 / TICKS_PER_SEC ); /* Send millisecs per tick */

}

/*
 * Stops ticker and curses.
 */
void wrap_up()
{
    set_ticker( 0 );
    endwin();                   /* put back to normal   */
}

