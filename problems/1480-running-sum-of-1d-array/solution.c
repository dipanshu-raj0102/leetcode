/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    
  int *retarr = malloc(sizeof *retarr * numsSize);
  retarr[0] = nums[0];

  for (int i = 1; i < numsSize; i++)
  {
    retarr[i] = nums[i] + retarr[i - 1];
  }
  *returnSize = numsSize;
  return retarr;
}