int numIdenticalPairs(int* nums, int numsSize) {
  int count[101] = {0};
  for (int i = 0; i < numsSize; i++)
  {
    count[nums[i]]++;
  }

  int goodpair = 0;
  for (int i = 0; i < 101; i++)
  {
    if (count[i] > 1) goodpair = goodpair + (count[i] * (count[i] - 1)) / 2;
  }
  return goodpair;

}