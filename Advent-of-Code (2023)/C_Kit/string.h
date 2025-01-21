#ifndef CK_String_H
#define CK_String_H

#define internal static

#define INVALID_STRING_ALLOCATION                                                                                      \
    {                                                                                                                  \
        printf("ERR: Invalid String Allocation\nTERMINATING PROCESS");                                                 \
        *((int*)0) = 0;                                                                                                \
    }

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
    char* data;
    int length;
    int capacity;
} String;

internal void string_validate(String* str)
{
    if (str->data == NULL) {
        INVALID_STRING_ALLOCATION
    }
}

int c_string_length(char* c_str)
{
    int count = 0;
    while (c_str[count] != '\0') {
        count++;
    }
    return count;
}

String string_create(char* c_str)
{
    int length                = c_string_length(c_str);
    int length_with_null_char = length + 1;

    // clang-format off
    String ret = (String) {
        .data = malloc(sizeof(char) * (length_with_null_char)), 
        .length = length, 
        .capacity = length * 2
    };
    // clang-format on

    for (int i = 0; i < length_with_null_char; i++) {
        ret.data[i] = c_str[i];
    }

    return ret;
}

void string_set(String* str, char* c_str)
{
    string_validate(str);
    // ret.length   = c_string_length(c_str);
    // ret.capacity = ret.length * 2;
    // ret.data     = (char*)malloc(sizeof(char) * ret.capacity);
}

internal void string_grow(String* str, int newSize)
{
    str->capacity = newSize * 2;
    str->data     = realloc(str->data, str->capacity);
}

internal void string_shrink(String* str)
{
}

void string_free(String* str)
{
    string_validate(str);
    free(str->data);
    str->data = NULL;
}

void string_append_c_str(String* str, char* c_str)
{
    string_validate(str);
    int c_str_length = c_string_length(c_str);
    int newLength    = str->length + c_str_length;
    if (newLength + 1 > str->capacity) { // +1 for the null char
        string_grow(str, newLength + 1);
    }
    for (int i = 0; i < c_str_length; i++) {
        str->data[str->length + i] = c_str[i];
    }
    str->length = newLength;

    str->data[newLength] = '\0';
}

void string_append_char(String* str, char incomingChar)
{
    string_validate(str);
    if (str->length + 2 > str->capacity) { // str->length + 2 for the new char and the null char
        string_grow(str, str->length + 2);
    }
    str->data[str->length++] = incomingChar;
    str->data[str->length]   = '\0';
}

// NOTE(Jovanni): This function is not finished
// Date: January 18, 2024
void string_remove_white_space(String* str)
{
    string_validate(str);
    int index  = 0;
    char* temp = str->data;
    while (*temp != '\n') {
        if (*temp++ == ' ') {
            // TODO(Jovanni): I Need to move over all things to the left basically
            // Date: January 18, 2024
        }
    }
    if (str->length + 2 > str->capacity) { // str->length + 2 for the new char and the null char
        string_grow(str, str->length + 2);
    }
    str->data[str->length++] = incomingChar;
    str->data[str->length]   = '\0';
}

#endif