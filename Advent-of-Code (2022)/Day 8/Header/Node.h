#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// edges + sizeof(node_t) * 3
#define MAX_EDGES 4

typedef struct Node {
  int height;
  bool isVisable;
  struct Node* adjacentNodes[4];
  struct Node* nextNodeAddress;
} Node;

Node createNode(int height, bool isVisable);

#endif