#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode
{
    void* value;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct
{
    ListNode* head;
    ListNode* tail;
    int count;
} LinkedList;

typedef void (*freeFunc)(void*);


LinkedList* initialiseLinkedList();
void insertFirst(LinkedList*, void*);
void* removeFirst(LinkedList*);
void freeLinkedList(LinkedList*, freeFunc);

#endif
