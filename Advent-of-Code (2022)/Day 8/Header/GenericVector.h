#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

#include <stdio.h>
#include <string.h>

#include <cstring>

#include "Assert_Message.h"

typedef struct Vector {
  int size;
  int capacity;
  size_t elementSize;
  void* data;
  void* (*get)(struct Vector*, int);
  void (*push_back)(struct Vector*, void*);
  void* (*pop)(struct Vector*);
} Vector;

Vector createVector(int capacity, size_t elementSize);

void test_vector_operations();

void free_vector(struct Vector* vector);

#endif