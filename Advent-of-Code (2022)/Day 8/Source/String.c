#include "../Header/String.h"

String createString(const char* initialData) {
    int length = strlen(initialData);
    String string = (String) {
        .data = (char*)malloc((length + 1) * sizeof(char)),
        .length = length,
        .appendString = appendString,
        .freeString = freeString,
    };
    strcpy(string.data, initialData);
    return string;
}

String char_to_string(char* c) {
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


void freeString(String* string) {
    free(string->data);
    string->data = NULL;
    string->length = 0;
}