#include "../Header/Node.h"

Node createNode(int height, bool isVisable) {
  Node node;
  
  node.height = height;
  node.isVisable = isVisable;
  node.adjacentNodes;
  for (int i = 0; i < 4; i++) {
    node.adjacentNodes[i] = NULL;
  }
  node.nextNodeAddress = NULL;
  return node;
}