long long maxTotalValue(int* nums, int numsSize, int k) {
    
  int max = INT_MIN;
  int min = INT_MAX;

  for ( int i = 0; i < numsSize; i++)
  {
    if (nums[i] > max)
    {
      max = nums[i];
    }
    if (nums[i] < min)
    {
      min = nums[i];
    }
  }
  
  return 1LL * k * (max - min);
}