#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
} LinkedList;


LinkedList createLinkedList();
Node* getNodeAt(LinkedList* list, int index);
void appendNode(LinkedList* linkedList, Node* node);
void popNode(LinkedList* list);
void printLinkedList(LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif