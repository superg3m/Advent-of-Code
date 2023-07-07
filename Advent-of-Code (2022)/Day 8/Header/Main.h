// C includes
#include <unistd.h>

// My includes
#include "Node.h"
#include "NodeVector.h"
#include "GenericVector.h"
#include "FileFramework.h"
#include "Color.h"
//#include "AdjacencyMatrix.h"
//#include "AdjacencyList.h"
#include "LinkedList.h"

void checkNodeDirection(Vector* parentVector, int rowLength, int columnLength) {
    int row = 0;
    int column = 0;

    int counter = 0;
    while (counter < 25) {
        usleep(1000000);
        printf("\033[H\033[2J");
        printf("\033[?25l");

        // Print the grid
        for (int i = 0; i < rowLength; i++) {
            Vector* currentVector = (Vector*)parentVector->get(parentVector, i);
            for (int j = 0; j < columnLength; j++) {
                Node* currentNode = (Node*)currentVector->get(currentVector, j);

                if (i == row && j == column) {
                    printf("%s%d\033[0m", COLOR_YELLOW, currentNode->height);
                } else if ((i == row + 1 && j == column) || (i == row && j == column + 1) ||
                           (i == row - 1 && j == column) || (i == row && j == column - 1)) {
                    printf("%s%d\033[0m", COLOR_BLUE, currentNode->height);
                } else {
                    printf("%s%d\033[0m", currentNode->isVisable ? COLOR_GREEN : COLOR_RED, currentNode->height);
                }
            }
            printf("\n");
        }

        if (column == columnLength - 1) {
            column = 0;
            row++;
        } else {
            column++;
        }
        counter++;
    }
}
