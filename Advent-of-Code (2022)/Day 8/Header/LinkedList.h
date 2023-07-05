#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
    void (*appendNode)(LinkedList*, Node*);
    Node* (*getNodeAt)(LinkedList*, int);
    void (*popNode)(LinkedList*);
    void (*printLinkedList)(LinkedList*);
    void (*freeLinkedList)(LinkedList*);
} LinkedList;


LinkedList createLinkedList();
static void appendNode(LinkedList* linkedList, Node* node);
static Node* getNodeAt(LinkedList* list, int index);
static void popNode(LinkedList* list);
static void printLinkedList(LinkedList* list);
static void freeLinkedList(LinkedList* list);

#endif