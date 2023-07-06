#include "../Header/Main.h"

int main() {
    
    FileFramework fileFramework = createFileFramework("../Day8.txt");
    fileFramework.openFile(&fileFramework);

    Vector stringVector = createVector(5, sizeof(String));

    while(!fileFramework.reachedEOF) {
        String line = fileFramework.getNextLine(&fileFramework);
        stringVector.push_back(&stringVector, &line);
    }

    for(int i = 0; i < stringVector.size; i++) {
        String* element = (String*)stringVector.get(&stringVector, i);
        printString(element);
        printf("\n");
    }

    return 0;
}