#include "../Header/Node.h"

Node createNode(int height, bool isVisable) {
  Node node = (Node){
      .height = height,
      .isVisable = isVisable,
      .adjacentNodes = {NULL, NULL, NULL, NULL},
      .nextNodeAddress = NULL,
  };
  return node;
}