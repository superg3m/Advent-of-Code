#include "../Header/LinkedList.h"

LinkedList createLinkedList() 
{
    LinkedList newList;
    newList.size = 0;
    newList.head = NULL;
    newList.tail = NULL;
    return newList;
}

Node* getNodeAt(LinkedList* list, int index) 
{
    if (index < 0 || index >= list->size) {
        return NULL;
    }
        
    Node* currentNode = list->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->nextNodeAddress;
    }
    return currentNode;
}


void appendNode(LinkedList* linkedList, Node* node)
{
    if (linkedList->head == NULL) {
        linkedList->head = node;
        linkedList->tail = node;
    } 
    else {
        Node* currentNode = getNodeAt(linkedList, linkedList->size - 1);
        currentNode->nextNodeAddress = node;
        linkedList->tail = currentNode->nextNodeAddress;
    }
    linkedList->size++;
}

void popNode(LinkedList* list)
{
    Node* currentNode = getNodeAt(list, list->size - 2);
    currentNode->nextNodeAddress = NULL;
    list->tail = currentNode;
    list->size--;
    return;
}

void printLinkedList(LinkedList* list)
{
    printf("----------- LINKED LIST -----------\n");
    Node* currentNode = list->head;
    for(int i = 0; i < list->size; i++) {
        printf("#%d | Height: %d | isVisable: %s\n", i + 1, currentNode->height, currentNode->isVisable ? "True" : "False");
        currentNode = currentNode->nextNodeAddress;
    }
    return;
}

void freeLinkedList(LinkedList* list)
{
    // to be implemented

    return;
}
