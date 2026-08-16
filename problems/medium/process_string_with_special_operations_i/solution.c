#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* processStr(const char* s) {

    size_t capacity = 1024; 
    size_t length = 0;
    
    char* result = (char*)malloc(capacity * sizeof(char));
    if (!result) return NULL;

    const char* ptr = s;

    while (*ptr != '\0') {
        switch (*ptr) {
            case '*':
                if (length > 0) {
                    length--;
                }
                break;

            case '#':
                if (length > 0) {
      
                    if (length * 2 >= capacity) {

                        while (length * 2 >= capacity) {
                            capacity *= 2;
                        }
                        char* temp = (char*)realloc(result, capacity * sizeof(char));
                        if (!temp) {
                            free(result);
                            return NULL; 
                        }
                        result = temp;
                    }
                    memcpy(result + length, result, length);
                    length *= 2;
                }
                break;

            case '%':
                if (length > 1) {

                    char* left = result;
                    char* right = result + length - 1;
                    while (left < right) {
                        char tmp = *left;
                        *left++ = *right;
                        *right-- = tmp;
                    }
                }
                break;

            default:
                if (length + 1 >= capacity) {
                    capacity *= 2;
                    char* temp = (char*)realloc(result, capacity * sizeof(char));
                    if (!temp) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                result[length++] = *ptr;
                break;
        }
        ptr++;
    }

    result = (char*)realloc(result, (length + 1) * sizeof(char));
    result[length] = '\0';
    
    return result;
}
