#include "../Header/FileFramework.h"

#define internal static

internal void openFile(FileFramework* fileFramework) {
  fileFramework->file = fopen(fileFramework->fileName, "r");
  assert_msg(fileFramework->file != NULL, "FILE IS NULL, CHECK INITIAL FILE NAME");
}

internal String getNextLine(FileFramework* fileFramework) {
  String line = ckit_str_create("");
  char c;
  do {
    c = fgetc(fileFramework->file);
    if (c != '\n' && c != EOF) {
      ckit_str_append_char(line, c);
    }
    if (c == EOF) {
      fileFramework->reachedEOF = true;
    }
  } while (c != '\n' && c != EOF);
  return line;
}

internal char getNextChar(FileFramework* fileFramework) {
  return fgetc(fileFramework->file);
}

internal void closeFile(FileFramework* fileFramework) { 
    fclose(fileFramework->file); 
}

FileFramework createFileFramework(const char* fileName) {
  FileFramework fileFramework;
  fileFramework.file = NULL;
  fileFramework.reachedEOF = false;
  fileFramework.fileName = fileName;
  fileFramework.openFile = openFile;
  fileFramework.getNextLine = getNextLine;
  fileFramework.getNextChar = getNextChar;
  fileFramework.closeFile = closeFile;
  return fileFramework;
}
