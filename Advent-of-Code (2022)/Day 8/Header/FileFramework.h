#ifndef FILE_FRAMEWORK_H
#define FILE_FRAMEWORK_H

#include <stdbool.h>
#include "Assert_Message.h"
#include <stdio.h>
#include "../CKit/include/core_string.h"

typedef struct FileFramework {
  FILE* file;
  bool reachedEOF;
  const char* fileName;
  void (*openFile)(struct FileFramework*);
  String (*getNextLine)(struct FileFramework*);
  char (*getNextChar)(struct FileFramework*);
  void (*closeFile)(struct FileFramework*);

} FileFramework;

FileFramework createFileFramework(const char* fileName);

#endif