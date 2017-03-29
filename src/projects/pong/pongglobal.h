/*
 * Declares the global variables to be used in single player pong.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include "ball.h"
#include "paddle.h"
#include "court.h"


extern int balls_left;
extern struct ppcourt the_court;
extern struct pppaddle the_paddle;
extern struct ppball the_ball;

#endif
