#include <Windows.h>
#include <stdio.h>

#include "Color.h"
#include "LinkedList.h"
#include "Node.h"
#include "../CKit/CKit.h"

void setColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

void calculateAdjacentNodes(Node* currentNode, Node** parentVector, int i,
                            int j) {
  int rowLength = vector_size(*parentVector);
  int columnLength = vector_size(parentVector[0]);

  Node* northNode = NULL;
  Node* eastNode = NULL;
  Node* southNode = NULL;
  Node* westNode = NULL;

  if (i - 1 >= 0) {
    // printf("northNode INDEX: %d\n", row - 1);
    Node* rowVector = parentVector[i - 1];
    northNode = &rowVector[j];
  }

  if (j + 1 < columnLength) {
    // printf("eastNode INDEX: %d\n", column + 1);
    Node* rowVector = parentVector[i];
    eastNode = &rowVector[j + 1];
  }

  if (i + 1 < rowLength) {
    // printf("southNode INDEX: %d\n", row + 1);
    Node* rowVector = parentVector[i + 1];
    southNode = &rowVector[j];
  }

  if (j - 1 >= 0) {
    // printf("westNode INDEX: %d\n", column - 1);
    Node* rowVector = parentVector[i];
    westNode = &rowVector[j - 1];
  }
  /*
  printf("Current Node: %d[%d][%d]\n", currentNode->height, i, j);
  if (northNode != NULL) {
      printf("North Node: %d\n", northNode->height);
  } else {
      printf("North Node: NULL\n");
  }

  if (eastNode != NULL) {
      printf("East Node: %d\n", eastNode->height);
  } else {
      printf("East Node: NULL\n");
  }

  if (southNode != NULL) {
      printf("South Node: %d\n", southNode->height);
  } else {
      printf("South Node: NULL\n");
  }

  if (westNode != NULL) {
      printf("West Node: %d\n", westNode->height);
  } else {
      printf("West Node: NULL\n");
  }
  printf("\n");
  */
  currentNode->adjacentNodes[0] = northNode;
  currentNode->adjacentNodes[1] = eastNode;
  currentNode->adjacentNodes[2] = southNode;
  currentNode->adjacentNodes[3] = westNode;
}

void calculateVisibility(Node** parentVector, int rowLength,
                         int columnLength) {
  int count = 0;
  for (int i = 0; i < rowLength; i++) {
    Node* rowVector = parentVector[i];
    for (int j = 0; j < columnLength; j++) {
      Node* currentNode = &rowVector[j];
      calculateAdjacentNodes(currentNode, parentVector, i, j);

      currentNode->isVisable = false;  // Assume the current node is not visible

      for (int k = 0; k < 4; k++) {
        if (currentNode->adjacentNodes[k] != NULL) {
          if (currentNode->height < currentNode->adjacentNodes[k]->height) {
            currentNode->isVisable = false;
            // printf("Current Node Height: %d | isVisable = %s |
            // Index:
            // [%d][%d] | currentNode->adjacentNodes[%d]->height:
            // %d\n", currentNode->height, currentNode->isVisable ?
            // "True" : "False", i, j, k,
            // currentNode->adjacentNodes[k]->height);
            break;
          } else if (currentNode->height >=
                     currentNode->adjacentNodes[k]->height) {
            currentNode->isVisable = true;
          }
        }
      }
      for (int k = 0; k < 4; k++) {
        if (currentNode->adjacentNodes[k] == NULL) {
          currentNode->isVisable = true;
          count++;
        }
      }

      // printf("FINAL | Current Node Height: %d | isVisable = %s | Index:
      // [%d][%d]\n", currentNode->height, currentNode->isVisable ? "True"
      // : "False", i, j);
      if (currentNode->isVisable) {
      }
    }
    // printf("\n");
  }
  printf("Count: %d\n", count);
}

// RULES
// 1. If the current node is the highest node in the row, it is visible
// 2. If the current node is the lowest node in the row, it is not visable
// 3. If the current node is the highest node in the column, it is visible
// 4. If the current node is the lowest node in the column, it is not visable
// 5. If the current node is surrounded by higher nodes, it is not visable
// 6. If the current node is surrounded by lower nodes I need to do recursion to
// check the nodes that are surrounding the current node if the recusion reaches
// the edge of the map, the current node is visable otherwise it is not visable
// 7. After performing rule 6 save the direction in which the node is visable do
// this in an array of bools North, East, South, West

void checkerAnimation(Node** parentVector, int rowLength, int columnLength) {
  int row = 0;
  int column = 0;

  int counter = 0;
  int totalNodes = rowLength * columnLength;

  printf("\033[?25l");  // Hide cursor

  while (counter < totalNodes) {
    Sleep(50);
    system("cls");  // Clear console screen once before printing
    for (int i = 0; i < rowLength; i++) {
      Node* currentVector = parentVector[i];

      for (int j = 0; j < columnLength; j++) {
        Node* currentNode = &currentVector[j];

        if (i == row && j == column) {
          // setColor(currentNode->isVisable ? FOREGROUND_GREEN :
          // FOREGROUND_RED);  // Green or Red text color
          setColor(BACKGROUND_BLUE);  // Blue text on white background
        } else if ((i == row + 1 && j == column) ||
                   (i == row && j == column + 1) ||
                   (i == row - 1 && j == column) ||
                   (i == row && j == column - 1)) {
          // setColor(currentNode->isVisable ? FOREGROUND_GREEN :
          // FOREGROUND_RED);
          setColor(BACKGROUND_BLUE | BACKGROUND_RED |
                   BACKGROUND_GREEN);  // Yellow text on white background
        } else {
          setColor(currentNode->isVisable
                       ? FOREGROUND_GREEN
                       : FOREGROUND_RED);  // Green or Red text color
        }

        printf("%d ", currentNode->height);
      }
      printf("\n");
    }

    setColor(FOREGROUND_RED | FOREGROUND_GREEN |
             FOREGROUND_BLUE);  // Reset text color to white

    if (column == columnLength - 1) {
      column = 0;
      row++;
    } else {
      column++;
    }
    counter++;
  }
  printf("\033[?25h");  // Show cursor
}
