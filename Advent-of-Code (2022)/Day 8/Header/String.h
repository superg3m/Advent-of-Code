#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char* data;
    int length;
    void (*appendString)(struct String*, const char*);
    void (*appendChar)(String*, const char);
    void (*freeString)(struct String*);
} String;


String createString(const char* initialData);

String char_to_string(const char* c);

void printString(const String* string);

static void appendString(String* string, const char* appendData);

static void appendChar(String* string, const char appendData);

static void freeString(String* string);

#endif
