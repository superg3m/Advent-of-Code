#include "../Header/Main.h"

int main() {
  CKit_init();

  FileFramework fileFramework = createFileFramework("../Day8.txt");
  fileFramework.openFile(&fileFramework);

  String* stringVector = vector_create(String);

  while (!fileFramework.reachedEOF) {
    String line = fileFramework.getNextLine(&fileFramework);
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

  memory_tag_output(LOG_LEVEL_INFO);

  vector_free(stringVector);
  vector_free(parentVector);
  string_arena_free();
  memory_arena_vector_free();

  memory_tag_output(LOG_LEVEL_WARN);

  return 0;
}