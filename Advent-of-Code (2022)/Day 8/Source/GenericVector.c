#include "../Header/GenericVector.h"

Vector createVector(int capacity, size_t elementSize) {
  Vector vector = (Vector){
      .size = 0,
      .capacity = capacity,
      .elementSize = elementSize,
      .data = malloc(capacity * elementSize),
      .get = get,
      .push_back = push_back,
      .pop = pop,
  };

  assert(vector.data != NULL);

  return vector;
}

void push_back(Vector* vector, void* element) {
  assert_msg(element != NULL, "Element being pushed back is NULL");

  vector->size++;
  if (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->data =
        realloc(vector->data, vector->capacity * vector->elementSize);
  }
  char* destination =
      (char*)vector->data + (vector->size - 1) * vector->elementSize;
  char* source = (char*)element;

  for (int i = 0; i < vector->elementSize; i++) {
    destination[i] = source[i];
    for (int j = 0; j < 8; j++) {
      int bit = (destination[i] >> j) & 1;
      // printf("%d ", bit);
    }
    // printf("= %d\n" , destination[i]);
  }
}

void* get(Vector* vector, int index) {
  assert(vector->data != NULL);

  assert_msg((index) >= 0, "Error: Index out of bounds: (below zero)");

  assert_msg(index < vector->size,
             "Error: Index out of bounds (exceeds vector size)");

  void* destination = ((char*)vector->data + index * vector->elementSize);

  assert(destination != NULL);

  return destination;
}

void* pop(Vector* vector) {
  assert_msg(vector->data != NULL, "Error: Vector is empty");
  assert_msg(vector->size > 0, "Error: Vector is empty");

  void* element =
      (char*)vector->data + (vector->size - 1) * vector->elementSize;
  vector->size--;

  // Shrink the data if capacity is 3 times the size
  if (vector->capacity > 3 * vector->size) {
    vector->capacity /= 2;
    vector->data =
        realloc(vector->data, vector->capacity * vector->elementSize);
  }

  return element;
}

void free_vector(struct Vector* vector) {
  free(vector->data);
  vector->data = NULL;
}

void test_vector_operations() {
  // Test types
  int intArray[] = {1, 2, 3, 4, 5};
  bool boolArray[] = {true, false, true, true, false};
  char charArray[] = {'a', 'b', 'c', 'd', 'e'};
  char* stringArray[] = {"Hello", "World", "!", "OpenAI", "GPT-3"};

  // Create vector of int
  Vector intVector = createVector(5, sizeof(int));
  for (int i = 0; i < 5; i++) {
    push_back(&intVector, &intArray[i]);
  }

  // Create vector of bool
  Vector boolVector = createVector(5, sizeof(bool));
  for (int i = 0; i < 5; i++) {
    push_back(&boolVector, &boolArray[i]);
  }

  // Create vector of char
  Vector charVector = createVector(5, sizeof(char));
  for (int i = 0; i < 5; i++) {
    push_back(&charVector, &charArray[i]);
  }

  // Create vector of strings
  Vector stringVector = createVector(5, sizeof(char*));
  for (int i = 0; i < 5; i++) {
    push_back(&stringVector, &stringArray[i]);
  }

  // Test get

  for (int i = 0; i < intVector.size; i++) {
    int* element = (int*)get(&intVector, i);
    assert_msg(*element == intArray[i], "Error: Incorrect element value");
  }

  for (int i = 0; i < boolVector.size; i++) {
    bool* element = (bool*)get(&boolVector, i);
    assert_msg(*element == boolArray[i], "Error: Incorrect element value");
  }

  for (int i = 0; i < charVector.size; i++) {
    char* element = (char*)get(&charVector, i);
    assert_msg(*element == charArray[i], "Error: Incorrect element value");
  }

  for (int i = 0; i < stringVector.size; i++) {
    char** element = (char**)get(&stringVector, i);
    assert_msg(strcmp(*element, stringArray[i]) == 0,
               "Error: Incorrect element value");
  }

  // Test pop
  for (int i = 0; i < intVector.size; i++) {
    int* element = (int*)get(&intVector, i);
  }

  void* poppedElement = pop(&intVector);
  int* poppedInt = (int*)poppedElement;

  for (int i = 0; i < intVector.size; i++) {
    int* element = (int*)get(&intVector, i);
  }

  assert_msg(*poppedInt == intArray[intVector.size],
             "Error: Incorrect popped element value");

  // Test free
  free_vector(&intVector);
  free_vector(&boolVector);
  free_vector(&charVector);
  free_vector(&stringVector);

  // Assert that the data is NULL
  assert_msg(intVector.data == NULL, "Error: Vector data is not NULL");
  assert_msg(boolVector.data == NULL, "Error: Vector data is not NULL");
  assert_msg(charVector.data == NULL, "Error: Vector data is not NULL");
  assert_msg(stringVector.data == NULL, "Error: Vector data is not NULL");

  printf(
      "\x1b[32m"
      "All vector tests passed!"
      "\n"
      "\x1b[0m");  // Green checkmark
}