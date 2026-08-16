bool increasingTriplet(int* nums, int numsSize) {
  int i = INT_MAX;
  int j = INT_MAX;

  for (int p = 0; p < numsSize; p++)
  {
    if (nums[p] <= i )
    {
          i = nums[p];
    }
    else if(nums[p] <= j)
      {
        j = nums[p];
      }
    else 
    {
      return true;
    }
  }
  return false;
    
}