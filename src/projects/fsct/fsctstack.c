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

    head->fullpath = NULL;
    head->dirpath = NULL;
    head->filename = NULL;
    head->next = NULL;
}
   
void add_dir(char* fullpath, char* path, char* file) 
{
    treenode_t* cur = head;
    while (cur->next != NULL) 
        cur = cur->next;

    cur->next = malloc(sizeof(treenode_t));

    cur->next->fullpath = malloc(strlen(fullpath)+1);
    cur->next->dirpath = malloc(strlen(path)+1);
    cur->next->filename = malloc(strlen(file)+1);
    strcpy(cur->next->fullpath, fullpath);
    strcpy(cur->next->dirpath, path);
    strcpy(cur->next->filename, file);
    cur->next->next = NULL;
}

treenode_t* pop_dir() 
{
    treenode_t* tmp;
    tmp = malloc(sizeof(treenode_t));

    if (head->next == NULL) {
        tmp->fullpath = head->fullpath;
        tmp->dirpath = head->dirpath;
        tmp->filename = head->filename;
        free(head);
        return tmp;
    }
    
    treenode_t* cur = head;

    while (cur->next->next != NULL) {
        cur = cur->next;
    }
    tmp->fullpath = cur->next->fullpath;
    tmp->dirpath = cur->next->dirpath;
    tmp->filename = cur->next->filename;
    free(cur->next);
    cur->next = NULL;
    return tmp;
}    

void print_dir() 
{
    treenode_t* cur = head->next;
    while (cur->next != NULL) {
        cur = cur->next;
    }
}
        

