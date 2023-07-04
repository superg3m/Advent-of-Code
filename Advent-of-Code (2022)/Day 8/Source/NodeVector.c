#include "../Header/NodeVector.h"


NodeVector createNodeVector(int capacity) 
{
    NodeVector nodeVector;
    nodeVector.size = 0;
    nodeVector.capacity = capacity;
    nodeVector.data = (Node*)malloc(nodeVector.capacity * sizeof(Node));
    return nodeVector;
}

void printNodeVector(NodeVector* nodeVector) 
{
    printf("----------- VECTOR -----------\n");
    for (int i = 0; i < nodeVector->size; i++) {
        printf("#%d | Height: %d | isVisable: %s\n", i+1, nodeVector->data[i].height, nodeVector->data[i].isVisable ? "True" : "False");
    }
}

void pushNode(NodeVector* nodeVector, Node node) 
{
    nodeVector->size++;
    if (nodeVector->size > nodeVector->capacity) {
        growVectorCapacity(nodeVector);
    } else if (nodeVector->capacity > (3 * nodeVector->size)) {
        shinkVectorCapacity(nodeVector);
    } 
    nodeVector->data[nodeVector->size - 1] = node;
}
 
void growVectorCapacity(NodeVector* nodeVector) 
{
    nodeVector->capacity *= 2;
    nodeVector->data = (Node*)realloc(nodeVector->data, nodeVector->capacity * sizeof(Node));
}

void shinkVectorCapacity(NodeVector* nodeVector) 
{
    nodeVector->capacity /= 2;
    nodeVector->data = (Node*)realloc(nodeVector->data, nodeVector->capacity * sizeof(Node));
}