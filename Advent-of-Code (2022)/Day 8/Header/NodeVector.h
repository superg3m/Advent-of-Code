#ifndef NODE_VECTOR_H
#define NODE_VECTOR_H

#include "Node.h"

typedef struct NodeVector {
    int size;
    int capacity;
    Node* data;
} NodeVector;

NodeVector createNodeVector(int capacity);

void pushNode(NodeVector* nodeVector, Node node);
 
void growVectorCapacity(NodeVector* nodeVector);

void shinkVectorCapacity(NodeVector* nodeVector);

void printNodeVector(NodeVector* nodeVector); 

#endif
