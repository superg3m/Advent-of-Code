#include <Windows.h>
#include <stdio.h>
#include <string.h>

#include "Node.h"
#include "NodeVector.h"
#include "GenericVector.h"
#include "FileFramework.h"
#include "Color.h"
#include "LinkedList.h"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void checkNodeDirection(Vector* parentVector, int rowLength, int columnLength) {
    int row = 0;
    int column = 0;

    int counter = 0;
    int totalNodes = rowLength * columnLength;

    printf("\033[?25l");  // Hide cursor

    while (counter < totalNodes) {
        Sleep(100);
        system("cls");  // Clear console screen once before printing
        for (int i = 0; i < rowLength; i++) {
            Vector* currentVector = (Vector*)parentVector->get(parentVector, i);

            for (int j = 0; j < columnLength; j++) {
                Node* currentNode = (Node*)currentVector->get(currentVector, j);

                if (i == row && j == column) {
                    setColor(BACKGROUND_BLUE);  // Blue text on white background
                } else if ((i == row + 1 && j == column) || (i == row && j == column + 1) ||
                           (i == row - 1 && j == column) || (i == row && j == column - 1)) {
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_GREEN);  // Yellow text on white background
                } else {
                    setColor(currentNode->isVisable ? FOREGROUND_GREEN : FOREGROUND_RED);  // Green or Red text color
                }

                printf("%d ", currentNode->height);
            }

            printf("\n");
        }

        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset text color

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
