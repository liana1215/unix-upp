#ifndef FSCT_STACK_H
#define FSCT_STACK_H

struct treenode {
    char* dirpath;
    struct treenode* next;
};

typedef struct treenode treenode_t;

void init_stack();
void add_dir(char*);
char* pop_dir();
void print_dir();

#endif
