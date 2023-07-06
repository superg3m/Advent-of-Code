#include "../Header/String.h"

String createString(const char* initialData) {
    int length = strlen(initialData);
    String string     = (String) {
        .data         = (char*)malloc((length + 1) * sizeof(char)),
        .length       = length,
        .appendString = appendString,
        .appendChar   = appendChar,
        .freeString   = freeString,
    };
    strcpy(string.data, initialData);
    return string;
}

String cstring_to_string(char* c) {
    String string = createString(c);
    return string;
}

void printString(const String* string) {
    printf("%s", string->data);
}

void appendString(String* string, const char* appendData) {
    size_t appendLength = strlen(appendData);
    string->data = (char*)realloc(string->data, (string->length + appendLength + 1) * sizeof(char));
    strcat(string->data, appendData);
    string->length += appendLength;
    string->data[string->length] = '\0';  // Null-terminate the string
}

void appendChar(String* string, const char appendData) {
    string->data = (char*)realloc(string->data, (string->length + 2) * sizeof(char));
    string->data[string->length] = appendData;
    string->data[string->length + 1] = '\0';  // Null-terminate the string
    string->length++;
}

void freeString(String* string) {
    free(string->data);
    string->data = NULL;
    string->length = 0;
}