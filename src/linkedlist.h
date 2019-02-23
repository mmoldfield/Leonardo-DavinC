/*******************************************************************************
* AUTHOR: Matthew Oldfield
* FILE NAME: linkedlist
* PURPOSE: the methods in this file are responsible for the implementation of 
a linkedlist that stores nodes containing Command* (it is program specific, but
it wouldn't take too much work to modify this to make it generic)
* CREATED: 2018-10-15
*******************************************************************************/

#ifndef LINKEDLIST
#define LINKEDLIST

#include "universal.h"

#define FIRST_INDEX 0 /* first index of the list */

/* provide meaningful feedback to the user */
#define ERR_MAL_NULL "Failed to allocate memory"
#define ERR_EMPTY_LL "The linked list is empty"
#define ERR_NA_IND "Index requested does not exist"

/* simple struct for a singly-linked linked list node */
typedef struct Node
{
    Command* data;
    struct Node* next; /* pointer to the next node */
    struct Node* prev; /* pointer to previous node */
} Node;

/* simple struct for a linked list */
typedef struct LinkedList
{
    Node* head;
    Node* tail;
    int count;
} LinkedList;

/* Creates an empty LinkedList struct, with internal values set to 0 and NULL
to reflect the empty state. Method will return a linkedList struct - this could
possibly be NULL if the malloc fails, so remember to handle this accordingly */
LinkedList* makeList();

/* Inserts a value into the last position of the LinkedList. Method will
shuffle existing elements if required, and decrement count. Returns 1 if there
is a failure when trying to malloc node memory */
int insertLast(LinkedList* listPtr, Command* value);

/* Removes the first node from the linked list. Method will shuffle elements if
required and decrement count. */
Command* removeFirst(LinkedList* listPtr);

/* frees all memory stored associated with the linked list, including that of
the nodes within the linked list and their respective values */
void freeLinkedList(LinkedList* listPtr);

#endif
