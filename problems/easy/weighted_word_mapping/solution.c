#include <stdlib.h>
#include <string.h>

char* mapWordWeights(char** words, int wordsSize, int* weights, int weightsSize) {
    char* result = (char*)malloc((wordsSize + 1) * sizeof(char));
    
    if (result == NULL) {
        return NULL; 
    }
    
    for (int i = 0; i < wordsSize; i++) {
        
        long long total_weight = 0;
        for (int j = 0; words[i][j] != '\0'; j++) {
            int index = words[i][j] - 'a';
            total_weight += weights[index];
        }
        
        int mod_val = total_weight % 26;
        
        result[i] = 'z' - mod_val;
    }
    
    result[wordsSize] = '\0';
    
    return result;
}