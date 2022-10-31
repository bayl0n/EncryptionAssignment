#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "vars.h"

/*******************************************************************************
 * NODE STRUCT
*******************************************************************************/
typedef struct Node {
    char text[MAX_BUFFER_SIZE];
    struct Node *next;
} Node_t;

void add(Node_t** head, const char* data);
void clearList(Node_t** head);
void displayList(Node_t* current);
void reverse(Node_t **);
void printReverse(Node_t *);
void deleteByPosition(Node_t** head, const int position);

#endif
