

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize){

    int *returnnums = malloc(sizeof(*returnnums) * numsSize);
    *returnSize = numsSize;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        returnnums[k++] = nums[i];
        returnnums[k++] = nums[n + i];
    }
    return returnnums;
}