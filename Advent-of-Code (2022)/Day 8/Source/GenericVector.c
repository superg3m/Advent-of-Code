#include "../Header/GenericVector.h"

Vector createVector(int capacity, size_t elementSize) {
    Vector vector;
    vector.capacity = capacity;
    vector.size = 0;
    vector.data = malloc(capacity * elementSize);
    vector.push_back = push_back;
    vector.get = get;
    vector.elementSize = elementSize;
    return vector;
}

void push_back(Vector* vector, void* element) {
    vector->size++;
    if (vector->size > vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * vector->elementSize);
    }
    char* destination = (char*)vector->data + (vector->size - 1) * vector->elementSize;
    char* source = (char*)element;

    for(int i = 0; i < vector->elementSize; i++) {
        destination[i] = source[i];
        for(int j = 0; j < 8; j++) {
           int bit = (destination[i] >> j) & 1;
           //printf("%d ", bit);
        }
        //printf("= %d\n" , destination[i]);
    }
}

void* get(Vector* vector, int index) {
    void* destination = ((char*)vector->data + index * vector->elementSize);
    return destination;
}