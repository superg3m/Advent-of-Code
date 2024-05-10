#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Assert_Message.h"
#include "Node.h"

typedef struct LinkedList {
  int size;
  Node* head;
  Node* tail;
  void (*appendNode)(struct LinkedList*, Node*);
  Node* (*getNodeAt)(struct LinkedList*, int);
  void (*popNode)(struct LinkedList*);
  void (*printLinkedList)(struct LinkedList*);
  void (*freeLinkedList)(struct LinkedList*);
} LinkedList;

LinkedList createLinkedList();
static void appendNode(LinkedList* linkedList, Node* node);
static Node* getNodeAt(LinkedList* list, int index);
static void popNode(LinkedList* list);
static void printLinkedList(LinkedList* list);
static void freeLinkedList(LinkedList* list);

#endif