#include "../Header/Main.h"

int main() {

    //printf("Hello World!\n");
    Node node1 = createNode(1, true);
    Node node2 = createNode(6, false);
    Node node3 = createNode(4, false);
    Node node4 = createNode(99, true);

    LinkedList list = createLinkedList();

    list.appendNode(&list, &node1);
    list.appendNode(&list, &node2);
    list.appendNode(&list, &node3);
    list.appendNode(&list, &node4);

    list.printLinkedList(&list);

    printf("\n");

    Vector vector = createVector(5, sizeof(Node));

    vector.push_back(&vector, &node4);
    vector.push_back(&vector, &node2);

    Node* returnNode1 = (Node*)vector.get(&vector, 0);
    Node* returnNode2 = (Node*)vector.get(&vector, 1);
    
    list.appendNode(&list, returnNode2);
    list.appendNode(&list, returnNode1);
    list.printLinkedList(&list);
    return 0;
}