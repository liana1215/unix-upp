#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fsctstack.h"

treenode_t* head;

void init_stack() 
{
    head = malloc(sizeof(treenode_t));
    if (head == NULL) 
        exit(1);

    head->dirpath = NULL;
    head->next = NULL;
}
   
void add_dir(char* path) 
{
    treenode_t* cur = head;
    while (cur->next != NULL) 
        cur = cur->next;

    cur->next = malloc(sizeof(treenode_t));

    cur->next->dirpath = malloc(strlen(path)+1);
    strcpy(cur->next->dirpath,path);
    cur->next->next = NULL;
}

char* pop_dir() 
{
    treenode_t* cur = head;
    treenode_t* tmp = NULL;
    char* retpath;

    while (cur->next != NULL) {
        tmp = cur;
        cur = cur->next;
    }
    
    retpath = cur->dirpath;
    
    cur = tmp;
    free(tmp->dirpath);
    free(tmp);
    cur->next = NULL;

    return retpath;
}    

void print_dir() 
{
    treenode_t* cur = head->next;
    while (cur->next != NULL) {
        printf("%s\n", cur->dirpath);
        cur = cur->next;
    }
    printf("%s\n", cur->dirpath);
}
        

