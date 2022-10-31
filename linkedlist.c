#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/*******************************************************************************
 * add
 * ----------------
 * Adds a node to the linked list
 * - input: head node of the linked list
 * - output: void
*******************************************************************************/
void add(Node_t** head, const char* data) {
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    strcpy(newNode->text, data);

    /* Insert the item */
    newNode->next = (*head);
    /* Move head to first node */
    (*head) = newNode;
}

/*******************************************************************************
 * deleteByPosition
 * ----------------
 * Delete a node to the linked list
 * - input: head node of the linked list, position to be delete
 * - output: void
*******************************************************************************/
void deleteByPosition(Node_t** head, const int position) {
    Node_t* current = *head;

    /* If deleting from the first record */
    if(position == 1) {
        *head = (*head)->next;
        return;
    }

    /* Any position after first */
    int i;
    for(i = 2; current != NULL && i < position; i++) {
        current = current->next;
    }

    if(current == NULL || current->next == NULL) {
        printf("\n\nRecord not found!\n\n");
        return;
    }

    Node_t* next = current->next->next;
    free(current->next);
    current->next = next;
}

/*******************************************************************************
 * clearList
 * ----------------
 * Clears linked list
 * - input: head node of the linked list
 * - output: void
*******************************************************************************/
void clearList(Node_t** head) {
    Node_t* current = *head;
    Node_t* next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    /* Clear the head */
    *head = NULL;
    printf("\n\nList cleared!\n\n");
}

/*******************************************************************************
 * display
 * ----------------
 * Displays the linked list to the console
 * - input: head node of the linked list
 * - output: void
*******************************************************************************/
void displayList(Node_t* current) {
    if(current == NULL) {
        printf("\n\nNo patient records to view!\n\n");
        return;
    }

    char* token;
    int count = 1;
    while(current->next != NULL) {
        printf("\n------------\nRecord #%d\n------------\n", count);
        int detailCount = 0;
        char* temp = malloc(sizeof(char) * strlen(current->text));

        strcpy(temp, current->text);

        token = strtok(temp, ",");

        while(token) {
            switch(detailCount) {
                case 0:
                    printf("Doctor: %s\n", token);
                    break;
                case 1:
                    printf("Patient: %s\n", token);
                    break;
                case 2:
                    printf("Date of Birth: %s\n", token);
                    break;
                case 3:
                    printf("Phone Number: %s\n", token);
                    break;
                case 4:
                    printf("Email: %s\n", token);
                    break;
                case 5:
                    printf("Reason of Admission: %s\n", token);
                    break;
                default: break;
            }
            detailCount++;
            token = strtok(NULL, ",");
        }
        count++;
        current = current->next;
    }
    printf("\n");
}

/*******************************************************************************
 * reverse
 * ----------------
 * Reverses a linked list
 * - input: head node of the linked list
 * - output: void
*******************************************************************************/
void reverse(Node_t** head){
    Node_t* current = *head;
    Node_t* previous = NULL;
    Node_t* next = NULL;
    
    while(current != NULL){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
}

/*******************************************************************************
 * printReverse
 * ----------------
 * Prints the linked list without actually reversing it
 * - input: head node of the linked list
 * - output: void
*******************************************************************************/
void printReverse(Node_t* head){
    if(head == NULL)
    return;

    printReverse(head->next);

    printf("%s ->", head->text);
}

