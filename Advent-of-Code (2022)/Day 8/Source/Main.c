#include "../Header/Main.h"

int main() {
  FileSystem fileFramework = file_system_create("../Day8.txt");
  file_open(&fileFramework);

  String* stringVector = vector_create(String);

  while (!fileFramework.reachedEOF) {
    String line = file_get_next_line(&fileFramework);
    vector_push(stringVector, line);
  }

  Node** parentVector = vector_reserve(vector_size(stringVector), Node*);
  for (int i = 0; i < vector_size(stringVector); i++) {
    String element = stringVector[i];
    Node* nodeVector = vector_reserve(string_length(element), Node);
    for (int j = 0; j < string_length(element); j++) {
      Node node;

      int charNumber = (element[j] - '0');
      if (i == 0 || i == vector_size(stringVector) - 1 || j == 0 ||
          j == string_length(element)) {
        node = createNode(charNumber, false);
      } else {
        node = createNode(charNumber, false);
      }
      vector_push(nodeVector, node);
    }
    vector_push(parentVector, nodeVector);
  }
  calculateVisibility(parentVector, vector_size(parentVector),
                      vector_size(parentVector[0]));
  checkerAnimation(parentVector, vector_size(parentVector),
                   vector_size(parentVector[0]));

  memory_output_allocations(LOG_LEVEL_INFO);

  for (int i = 0; i < vector_size(stringVector); i++) {
    string_free(stringVector[i]);
  }
  vector_free(stringVector);

  for (int i = 0; i < vector_size(parentVector); i++) {
    vector_free(parentVector[i]);
  }
  vector_free(parentVector);

  memory_output_allocations(LOG_LEVEL_WARN);

  return 0;
}