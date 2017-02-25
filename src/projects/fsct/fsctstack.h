#ifndef FSCT_STACK_H
#define FSCT_STACK_H

struct node {
    char* name;
    struct node* next;
};

typedef struct node node_t;

void init_node();
void add_node(char*);
char* find_node(char*);
void clear_node();

#endif
