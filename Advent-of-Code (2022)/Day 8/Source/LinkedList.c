#include "../Header/LinkedList.h"

LinkedList createLinkedList() 
{
    LinkedList newList = (LinkedList) {
        .size            = 0,
        .head            = NULL,
        .tail            = NULL,
        .appendNode      = appendNode,
        .getNodeAt       = getNodeAt,
        .popNode         = popNode,
        .printLinkedList = printLinkedList,
        .freeLinkedList  = freeLinkedList
    };

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

    assert_msg(currentNode != NULL, "LinkedList return node is NULL");

    return currentNode;
}


void appendNode(LinkedList* linkedList, Node* node)
{
    assert_msg(node != NULL, "Appended node is NULL");
    if (linkedList->head == NULL) {
        linkedList->head = node;
        linkedList->tail = node;
    } 
    else {
        Node* currentNode = linkedList->getNodeAt(linkedList, linkedList->size - 1);
        currentNode->nextNodeAddress = node;
        linkedList->tail = currentNode->nextNodeAddress;
    }
    linkedList->size++;
}

void popNode(LinkedList* linkedList)
{
    Node* currentNode = linkedList->getNodeAt(linkedList, linkedList->size - 2);
    currentNode->nextNodeAddress = NULL;
    linkedList->tail = currentNode;
    linkedList->size--;
    return;
}

void printLinkedList(LinkedList* linkedList)
{
    printf("----------- LINKED LIST -----------\n");
    Node* currentNode = linkedList->head;
    for(int i = 0; i < linkedList->size; i++) {
        printf("#%d | Height: %d | isVisable: %s\n", i + 1, currentNode->height, currentNode->isVisable ? "True" : "False");
        currentNode = currentNode->nextNodeAddress;
    }
    return;
}

void freeLinkedList(LinkedList* linkedList)
{
    // to be implemented

    return;
}
