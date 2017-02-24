#ifndef FSCT_STACK_H
#define FSCT_STACK_H

struct treenode {
    char* fullpath;
    char* dirpath;
    char* filename;
    struct treenode* next;
};

typedef struct treenode treenode_t;


void init_stack();
void add_dir(char*, char*, char*);
treenode_t* pop_dir();
void print_dir();

#endif
