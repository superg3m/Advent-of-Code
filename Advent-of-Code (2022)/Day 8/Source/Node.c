#include "../Header/Node.h"

Node createNode(int height, bool isVisable) 
{
    Node newNode;
    newNode.height = height;
    newNode.isVisable = isVisable;
    newNode.nextNodeAddress = NULL;
    return newNode;
}