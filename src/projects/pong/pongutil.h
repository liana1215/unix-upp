/*
 * Declares utility functions related to single player pong.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#ifndef PONG_UTIL_H
#define PONG_UTIL_H

#include <time.h>

void print_score();
void end_game();
void init_clock();
time_t check_clock();
void reset_clock();

#endif
