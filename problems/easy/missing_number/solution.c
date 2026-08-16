int missingNumber(int* nums, int numsSize) {
    
  int ans = numsSize;

  for (int i = 0; i < numsSize; i++)
  {
    ans = ans ^ i;
    ans = ans ^ nums[i];
  }

  return ans;
}