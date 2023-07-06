#include "../Header/GenericVector.h"

Vector createVector(int capacity, size_t elementSize) {
    
    Vector vector    = (Vector) {
        .size        = 0,
        .capacity    = capacity,
        .elementSize = elementSize,
        .data        = malloc(capacity * elementSize),
        .get         = get,
        .push_back   = push_back
    };

    assert(vector.data != NULL);

    return vector;
}

void push_back(Vector* vector, void* element) {

    assert_msg(element != NULL, "Element being pushed back is NULL");

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
    assert(vector->data != NULL);

    assert_msg((index) >= 0, "Error: Index out of bounds (below zero)");

    //assert(index > vector->size);
    assert_msg(index < vector->size, "Error: Index out of bounds (exceeds vector size)");

    void* destination = ((char*)vector->data + index * vector->elementSize);
    
    return destination;
}