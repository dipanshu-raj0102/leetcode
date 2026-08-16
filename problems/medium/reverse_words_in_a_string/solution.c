#include <stdlib.h>
#include <string.h>

char* reverseWords(char* s) {
    int len = strlen(s);
    
 
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) return NULL;
    
    int write = 0;
    int i = len - 1;
    
    while (i >= 0) {
        while (i >= 0 && s[i] == ' ') {
            i--;
        }
        
        if (i < 0) break;
        
        int right = i; 
        

        while (i >= 0 && s[i] != ' ') {
            i--;
        }
        int left = i + 1; 
        

        if (write > 0) {
            result[write++] = ' ';
        }
        

        for (int j = left; j <= right; j++) {
            result[write++] = s[j];
        }
    }
    

    result[write] = '\0';
    
    return result;
}
