/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    
  int res = nums[0];
  for ( int i = 1; i < numsSize; i++)
  {
    res = res ^ nums[i];
  }

  unsigned int setbit = ((unsigned int)res) & (-(unsigned int)res);

  int grp0 = 0;
  int grp1 = 0;

  for ( int i = 0; i < numsSize; i++)
  {
    if ((nums[i] & setbit) == 0)
    {
      grp0 = grp0 ^ nums[i];
    }
       else {
      grp1 = grp1 ^ nums[i];
    }
  }
  
  *returnSize = 2;
  int *ans = malloc(sizeof(int) * 2);
  ans[0] = grp0;
  ans[1] = grp1;
  return ans;
}