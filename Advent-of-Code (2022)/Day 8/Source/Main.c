#include "../Header/Main.h"

int main() {

  FileSystem fileFramework = file_system_create("../Day8.txt");
  file_open(&fileFramework);

  String* stringVector = NULLPTR;

  while (!fileFramework.reachedEOF) {
    String line = file_get_next_line(&fileFramework);
    ckit_vector_push(stringVector, line);
  }

  Node** parentVector = ckit_vector_reserve(ckit_vector_count(stringVector), Node*);
  for (int i = 0; i < ckit_vector_count(stringVector); i++) {
    String element = stringVector[i];
    Node* nodeVector = ckit_vector_reserve(ckit_cstr_length(element), Node);
    for (int j = 0; j < ckit_cstr_length(element); j++) {
      Node node;

      int charNumber = (element[j] - '0');
      if (i == 0 || i == ckit_vector_count(stringVector) - 1 || j == 0 ||
          j == ckit_cstr_length(element)) {
        node = createNode(charNumber, false);
      } else {
        node = createNode(charNumber, false);
      }
      ckit_vector_push(nodeVector, node);
    }
    ckit_vector_push(parentVector, nodeVector);
  }
  calculateVisibility(parentVector, ckit_vector_count(parentVector),
                      ckit_vector_count(parentVector[0]));
  checkerAnimation(parentVector, ckit_vector_count(parentVector),
                   ckit_vector_count(parentVector[0]));

  for (int i = 0; i < ckit_vector_count(stringVector); i++) {
    ckit_str_free(stringVector[i]);
  }
  ckit_vector_free(stringVector);

  for (int i = 0; i < ckit_vector_count(parentVector); i++) {
    ckit_vector_free(parentVector[i]);
  }
  ckit_vector_free(parentVector);

  ckit_cleanup();
  return 0;
}