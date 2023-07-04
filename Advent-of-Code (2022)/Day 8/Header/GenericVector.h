#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Vector {
    int size;
    int capacity;
    size_t elementSize;
    void* data;
    void* (*get)(struct Vector*, int);
} Vector;

Vector createVector(int capacity, size_t elementSize);

void push_back(Vector* vector, void* element);

void* getElement(Vector* vector, int index);

#endif