/* See accompanying header file for documentation */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************/
LinkedList* makeList()
{
    LinkedList* list; /* pointer to the linked list */

    list = (LinkedList*)malloc(sizeof(LinkedList)); /* allocate memory */

    if (list != NULL) /* malloc was successful */
    {
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
    }
    else
    {
        printf("%s\n", ERR_MAL_NULL);  /* out of memory */
    }

    return list;
}

/******************************************************************************/
int insertLast(LinkedList* listPtr, Command* cmd)
{
    int returnVal;
    Node* newNode;

    returnVal = 0; /* assume everything goes to plan */

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode != NULL)
    {
        if (listPtr->count == 0) /* we are inserting first item */
        {
            listPtr->head = newNode;
            listPtr->tail = newNode;
            newNode->next = NULL; /* there are no other elements in list */
            newNode->prev = NULL; /* there are no other elements in list */
        }
        else
        {
            newNode->prev = listPtr->tail; /* shuffle tail down one spot */
            newNode->next = NULL; /* because it is the last item in list */
            listPtr->tail->next = newNode; /* point to our new node */
            listPtr->tail = newNode; /* newNode becomes the new head! */
        }

        newNode->data = cmd; /* needs to be done regardless of list size */
        listPtr->count++; /* incriment count */
    }
    else
    {
        returnVal = 1; /* out of memory */
    }

    return returnVal;
}

/******************************************************************************/
Command* removeFirst(LinkedList* listPtr)
{
    Command* copy; /* will be returned to calling function */

    if (listPtr->count == 0) /* the list is empty */
    {
        copy = NULL; /* nothing to return! */
    }
    else
    {
        copy = listPtr->head->data; /* to return to the calling function */

        if (listPtr->count == 1)
        {
            free(listPtr->head);
            listPtr->head = NULL;
            listPtr->tail = NULL;
        }
        else /* multiple items in list */
        {
            listPtr->head = listPtr->head->next;
            free(listPtr->head->prev);
            listPtr->head->prev = NULL;
        }

        listPtr->count--; /* decrement the count */
    }


    return copy;
}

/******************************************************************************/

void freeLinkedList(LinkedList* listPtr)
{
    Node* current;
    Node* next;

    current = listPtr->head;

    while (current != NULL)
    {
        next = current->next;
        free(current->data->value); /* free the void* inside value */
        free(current->data); /* free the data inside the node */
        free(current); /* free the actual node */
        current = next; /* iterate */
    }

    free(listPtr); /* now free the pointer to the list */
}
