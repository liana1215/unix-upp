#ifndef FSCT_STACK_H
#define FSCT_STACK_H


struct node {
    char* name;
    struct node* next;
};

struct treenode {
    char* fullpath;
    char* dirpath;
    char* filename;
    struct treenode* next;
};

typedef struct node node_t;
typedef struct treenode treenode_t;

void init_node();
void add_node(char*);
char* find_node(char*);
void clear_node();


void init_stack();
void add_dir(char*, char*, char*);
treenode_t* pop_dir();
void print_dir();

#endif
