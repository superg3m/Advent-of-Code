#ifndef FILE_FRAMEWORK_H
#define FILE_FRAMEWORK_H

#include <stdbool.h>

#include "Assert_Message.h"
#include "String.h"

typedef struct FileFramework {
  FILE* file;
  bool reachedEOF;
  const char* fileName;
  void (*openFile)(FileFramework*);
  String (*getNextLine)(FileFramework*);
  char (*getNextChar)(FileFramework*);
  void (*closeFile)(FileFramework*);

} FileFramework;

FileFramework createFileFramework(const char* fileName);

#endif