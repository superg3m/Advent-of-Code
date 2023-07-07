#include "../Header/Main.h"


int main() {
    
    test_vector_operations();
    Sleep(1000);
    FileFramework fileFramework = createFileFramework("../Day8.txt");
    fileFramework.openFile(&fileFramework);
    

    Vector stringVector = createVector(5, sizeof(String));

    while(!fileFramework.reachedEOF) {
        String line = fileFramework.getNextLine(&fileFramework);
        stringVector.push_back(&stringVector, &line);
    }

    Vector parentVector = createVector(stringVector.size, sizeof(Vector));
    Vector nodeVector;
    for(int i = 0; i < stringVector.size; i++) {
        String* element = (String*)stringVector.get(&stringVector, i);
        nodeVector = createVector(element->length, sizeof(Node));
        for(int j = 0; j < element->length; j++) {
            Node node;
            
            int charNumber = (element->data[j] - '0');
            if(i == 0 || i == stringVector.size - 1  || j == 0 || j == element->length - 1) {
                node = createNode(charNumber, true);
            } else {
                node = createNode(charNumber, false);
            }
            nodeVector.push_back(&nodeVector, &node);
        }
        parentVector.push_back(&parentVector, &nodeVector);
    }

    checkNodeDirection(&parentVector, parentVector.size, ((Vector*)parentVector.get(&parentVector, 0))->size);   

    return 0;
}