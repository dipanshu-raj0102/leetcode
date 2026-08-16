int firstMissingPositive(int* nums, int numsSize) {

  int i = 0;

  while ( i < numsSize)
  {
    if (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] -1])
    {
      int tmp = nums[nums[i] - 1];
      nums[nums[i] -1] = nums[i];
      nums[i] = tmp;
    }
    else {
      i++;
    }
  }

  for ( int i = 0; i < numsSize; i++)
  {
    if (nums[i] != (i + 1)) return (i + 1);
  }
  return (numsSize + 1);
}