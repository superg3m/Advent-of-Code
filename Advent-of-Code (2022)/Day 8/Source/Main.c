#include "../Header/Main.h"

int main() {
  ckit_init();

  FileSystem fileFramework = file_system_create("../../Day8.txt");
  file_open(&fileFramework);

  String* stringVector = NULLPTR;

  while (!fileFramework.reachedEOF) {
    String line = file_get_next_line(&fileFramework);
    ckit_vector_push(stringVector, line);
  }

  Node** parentVector = ckit_vector_reserve(ckit_vector_count(stringVector), Node*);
  for (u32 i = 0; i < ckit_vector_count(stringVector); i++) {
    String element = stringVector[i];
    u64 element_length = ckit_str_length(element);
    Node* nodeVector = ckit_vector_reserve((u32)element_length, Node);
    for (u32 j = 0; j < element_length; j++) {
      Node node;

      int charNumber = (element[j] - '0');
      if (i == 0 || i == (ckit_vector_count(stringVector) - 1) || j == 0 ||
          j == element_length) {
        node = createNode(charNumber, false);
      } else {
        node = createNode(charNumber, false);
      }
      ckit_vector_push(nodeVector, node);
    }
    ckit_vector_push(parentVector, nodeVector);
  }
  
  calculateVisibility(parentVector, ckit_vector_count(parentVector), ckit_vector_count(parentVector[0]));
  checkerAnimation(parentVector, ckit_vector_count(parentVector), ckit_vector_count(parentVector[0]));
  ckit_vector_free(stringVector);

  for (u32 i = 0; i < ckit_vector_count(parentVector); i++) {
    ckit_vector_free(parentVector[i]);
  }
  ckit_vector_free(parentVector);

  file_close(&fileFramework);

  ckit_cleanup(TRUE);
  return 0;
}