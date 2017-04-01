/*
 * Declares the global variables to be used in single player pong.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include <time.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"


extern int balls_left;      /* Number of balls left */
extern time_t wall_clock;   /* Clock to keep track of game */

extern struct ppcourt the_court;
extern struct pppaddle the_paddle;
extern struct ppball the_ball;

#endif
