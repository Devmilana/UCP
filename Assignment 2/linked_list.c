/*******************************************************************************************************************
  
 * linked_list.c

 * AUTHOR: PRASHANTHA FERNANDO
 
 * LAST EDITED: 22/10/23
 
 * DESCRIPTION: C file with functions to create a linkedlist with methods for node addition and removal
 
*******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

/* Initialises and allocates memory for a new linked list and returns its pointer */
LinkedList* initialiseLinkedList()
{
    /* Dynamically allocate memory for a new linked list */
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    /* Initialise head and tail pointers to NULL */
    list->head = NULL;
    list->tail = NULL;

    /* Initialise the count of nodes in the list to 0 */
    list->count = 0;

    /* Return the pointer to newly created linked list */
    return list;
}

/* Inserts a new node with the given value at the beginning of the linked list */
void insertFirst(LinkedList* list, void* inValue)
{
    /* Dynamically allocate memory for a new list node */
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); 
    ListNode* prevHead; 

    /* Assign the input value to the node and initialise its next and previous pointers */
    newNode->value = inValue;
    newNode->next = NULL;
    newNode->prev = NULL;

    /* Checks if list is empty */
    if(list->head == NULL)
    {
        /* New node becomes both the head and tail of the list */
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        /* Link new node to previous head */
        newNode->next = list->head;
        prevHead = newNode->next;
        prevHead->prev = newNode; 

        /* Update list's head to point to new node */
        list->head = newNode;        
    }

    list->count += 1;
}

/* Removes and returns the value of the first node from the linked list */
void* removeFirst(LinkedList* list)
{
    void* nodeValue; 
        
    ListNode* prevHead;
        
    /* Checks if list is empty */
    if(list->count == 0)
    {
        nodeValue = NULL;
    }
    /* Check if list has only one node */
    else if(list->count == 1)
    {
        nodeValue = (list->head)->value;
        prevHead = list->head;

        /* Set head and tail pointers to NULL */
        list->head = NULL;
        list->tail = NULL;
        free(prevHead);
    }
    else
    {
        /* Gets value of first node */
        nodeValue = (list->head)->value;
        prevHead = list->head;

        /* Update head pointer to next node and free the memory of removed node */
        list->head = (list->head)->next;
        list->head->prev = NULL;
        free(prevHead);
    }

    list->count -= 1;

    return nodeValue;
}

/* Frees all nodes of the linked list and the list itself */
void freeLinkedList(LinkedList* list, freeFunc freeValue)
{
    ListNode* currNode;  
    ListNode* nextNode;

    if(list->count > 0)
    {
        currNode = list->head;

        while(currNode != NULL)
        {
            nextNode = currNode->next;
            
            freeValue(currNode->value);
            free(currNode);

            currNode = nextNode;
        }
    }
    
    free(list);
}
