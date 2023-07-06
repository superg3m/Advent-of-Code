#include "../Header/FileFramework.h"

FileFramework createFileFramework(const char* fileName) {
    FileFramework fileFramework = (FileFramework) {
        .file                   = NULL,
        .reachedEOF             = false,
        .fileName               = fileName,
        .openFile               = openFile,
        .getNextLine            = getNextLine,
        .getNextChar            = getNextChar,
        .closeFile              = closeFile,
    };
    return fileFramework;
}

void openFile(FileFramework* fileFramework) {
    fileFramework->file = fopen(fileFramework->fileName, "r");
    assert_msg(fileFramework->file != NULL, "FILE IS NULL, CHECK INITIAL FILE NAME");
}

String getNextLine(FileFramework* fileFramework) {
    String line = createString("");
    char c;
    do {
        c = fgetc(fileFramework->file);
        if (c != '\n' && c != EOF) {
            line.appendChar(&line, c);
        }
        if(c == EOF) {
            fileFramework->reachedEOF = true;
        }
    } while (c != '\n' && c != EOF);
    return line;
}

char getNextChar(FileFramework* fileFramework) {
    return fgetc(fileFramework->file);
}

void closeFile(FileFramework* fileFramework) {
    fclose(fileFramework->file);
}
