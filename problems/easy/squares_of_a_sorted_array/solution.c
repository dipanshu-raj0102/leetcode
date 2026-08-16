/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
  int positive = 0;
  while (positive < numsSize && nums[positive] < 0) positive++;

  int negative = positive - 1;

  int *returnArr = malloc(sizeof(int) * numsSize);
  int pos = 0;
  while(negative >= 0 && positive < numsSize)
  {
    if ((-nums[negative]) < nums[positive])
    {
      returnArr[pos++] = nums[negative] * nums[negative];
      negative--;
    }
    else {
      returnArr[pos++] = nums[positive] * nums[positive];
      positive++;
    }
  }
  if(negative >= 0)
  {
    while(negative >= 0)
    {
      returnArr[pos++] = nums[negative] * nums[negative];
      negative--;
    }
  }
  if (positive < numsSize)
  {
    while(positive < numsSize)
    {
      returnArr[pos++] = nums[positive] * nums[positive];
      positive++;
    }
  }
  
  *returnSize = pos;
  return returnArr;
}