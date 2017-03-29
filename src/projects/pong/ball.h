/*
 * Definitions of parameters, and declaration of structs and methods describing
 * the ping pongball.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#ifndef BALL_H
#define BALL_H

#define BLANK       ' '
#define BALL_SYMBOL 'o'
#define X_INIT      10      /* starting col     */
#define Y_INIT      10      /* starting row     */
#define TICKS_PER_SEC   50  /* affects speed    */

#define X_DELAY     5
#define Y_DELAY     8

#define LOSE        2
#define BOUNCE      1
#define NOBOUNCE    0


struct ppball {
        int x_pos, x_dir,
            y_pos, y_dir,
            y_delay, y_count,
            x_delay, x_count;
        char    symbol ;
};


void ball_move(int);
int bounce_or_lose(struct ppball*);

#endif
