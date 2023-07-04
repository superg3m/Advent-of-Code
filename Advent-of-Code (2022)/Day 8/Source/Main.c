#include "../Header/Main.h"

int main() {

    //printf("Hello World!\n");
    Node node1 = createNode(1, true);
    Node node2 = createNode(6, false);
    Node node3 = createNode(4, false);
    Node node4 = createNode(99, true);

    LinkedList list = createLinkedList();

    appendNode(&list, &node1);
    appendNode(&list, &node2);
    appendNode(&list, &node3);
    appendNode(&list, &node4);

    printLinkedList(&list);

    printf("\n");

    Vector vector = createVector(5, sizeof(Node));

    push_back(&vector, &node4);
    Node* returnNode = (Node*)vector.get(&vector, 0);
    appendNode(&list, returnNode);
    printLinkedList(&list);
    return 0;
}