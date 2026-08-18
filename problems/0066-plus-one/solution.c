int* plusOne(int* digits, int digitsSize, int* returnSize) {
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            *returnSize = digitsSize;
            int* result = (int*)malloc(digitsSize * sizeof(int));
            
            for (int j = 0; j < digitsSize; j++) {
                result[j] = digits[j];
            }
            
            result[i]++;
            for (int j = i + 1; j < digitsSize; j++) {
                result[j] = 0;
            }
            
            return result;
        }
    }

    // Handle edge case where all digits are 9 (e.g., [9, 9, 9] -> [1, 0, 0, 0])
    *returnSize = digitsSize + 1;
    int* result = (int*)calloc(*returnSize, sizeof(int));
    result[0] = 1;
    
    return result;
}