#include "str.h"
int my_strcmp(const char* str1, const char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}
unsigned int my_strlen(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}