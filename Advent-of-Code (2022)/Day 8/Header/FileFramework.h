#ifndef FILE_FRAMEWORK_H
#define FILE_FRAMEWORK_H

#include "String.h"
#include "Assert_Message.h"
#include <stdbool.h>

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

static void openFile(FileFramework* fileFramework);

String getNextLine(FileFramework* fileFramework);

static char getNextChar(FileFramework* fileFramework);

static void closeFile(FileFramework* fileFramework);

#endif