/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    
    int *count = calloc(numsSize + 1, sizeof(int));
    
    for (int i = 0; i < numsSize; i++)
    {
        count[nums[i]]++;
    }
    
    int missing = 0;
    for (int i = 1; i < numsSize + 1; i++)
    {
        if (count[i] == 0 && i != 0) missing++;
    }
    *returnSize = missing;
    
    int *areturn = malloc(sizeof(int) * missing);
    
    int r = 0;
    for (int i = 1; i < numsSize + 1; i++)
    {
        if (count[i] == 0) areturn[r++] = i;
    }
    return areturn;
}