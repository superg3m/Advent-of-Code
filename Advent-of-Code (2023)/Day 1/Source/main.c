#include <stdio.h>

#include "../../C_Kit/string.h"

int main()
{
    String testString = string_create("abc");
    printf("LENGTH: %u\n", testString.length);
    printf("Capacity: %u\n", testString.capacity);

    string_append_c_str(&testString, " FSFSDFSsfsdfsdFSDF");

    printf("LENGTH: %u\n", testString.length);
    printf("Capacity: %u\n", testString.capacity);

    printf("THE STRING: %s\n", testString.data);

    string_append_c_str(&testString, "AHDSD");
}