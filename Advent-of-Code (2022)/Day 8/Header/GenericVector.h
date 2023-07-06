#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

#include "Assert_Message.h"
#include <stdio.h>

typedef struct Vector {
    int size;
    int capacity;
    size_t elementSize;
    void* data;
    void* (*get)(struct Vector*, int);
    void (*push_back)(struct Vector*, void*);
} Vector;

Vector createVector(int capacity, size_t elementSize);

static void push_back(Vector* vector, void* element);

static void* get(Vector* vector, int index);

#endif