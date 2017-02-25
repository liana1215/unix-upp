#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fsctstack.h"

treenode_t* head;
node_t* nhead;

void init_node()
{
    nhead = malloc(sizeof(node_t));
    if (nhead == NULL)
        exit(1);
    
    nhead->name = NULL;
    nhead->next = NULL;
}

void add_node(char* name)
{
    node_t* cur = nhead;
    while(cur->next != NULL)
        cur = cur->next;

    cur->next = malloc(sizeof(node_t));
    cur->next->name = malloc(strlen(name)+1);
    strcpy(cur->next->name, name);
    cur->next->next = NULL;
}

char* maybe_convert(char* name) 
{
    int len = strlen(name) + 1;
    char ret[len];
    int i = 0;
    for (i = 0; i < len; i++) {
        if(isalpha(name[i])) {
            ret[i] = tolower(name[i]);
        } else {
            ret[i] = name[i];
        }
    }
    char* alllower = malloc(len);
    strcpy(alllower, ret);
    return alllower;
}

char* find_node(char* name)
{
    node_t* cur = nhead->next;
    while (cur->next != NULL) {
        char* name_tmp = maybe_convert(name);
        char* node_tmp = maybe_convert(cur->name);
        if(strcmp(node_tmp, name_tmp) == 0) {
            return cur->name; 
        }
        cur = cur->next;
    }
    return NULL;
}

void clear_node()
{
    node_t* tmp;
    while (nhead != NULL) {
        tmp = nhead;
        nhead = nhead->next;
        free(tmp);
    }
}
        

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
        head->fullpath = NULL;
        head->dirpath = NULL;
        head->filename = NULL;
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
        

