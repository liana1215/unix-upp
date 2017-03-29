/*
 * Header file to declare structs and functions related to the court.
 * date: 3/29/2017
 * author: Tasuku Miura
 */
#ifndef COURT_H
#define COURT_H

#define VERT_SYMBOL '|'
#define HORI_SYMBOL '-'
#define COURT_PAD 5

struct ppcourt {
    int top_edge, bot_edge,
        left_edge, right_edge;
    char vert_char;     /*symbol to use for horizontal edge*/
    char hori_char;     /*symbol to use for vertical edge*/
};


void set_up();
void wrap_up();

#endif
