#include "../Header/Node.h"

Node createNode(int height, bool isVisable) 
{
    Node node = (Node) {
        .height = height,
        .isVisable = isVisable,
        .edges = NULL,
        .nextNodeAddress = NULL,
    };
    return node;
}