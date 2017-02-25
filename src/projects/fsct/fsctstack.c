#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fsctstack.h"

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
            free(name_tmp);
            free(node_tmp);
            return cur->name; 
        }
        cur = cur->next;
        free(name_tmp);
        free(node_tmp);
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
        tmp->next = NULL;
    }
}
