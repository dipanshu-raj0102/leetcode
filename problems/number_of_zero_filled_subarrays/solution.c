
long long zeroFilledSubarray(int* nums, int numsSize) {
  
  long long streak = 0;
  long long output = 0;
  
  for (int i = 0; i < numsSize; i++)
  {
    if (nums[i] == 0)
    {
      streak++;
      output += streak;
    }
    else
    {
      streak = 0;
    }
  }
  return output;
}