void rotate(int* nums, int numsSize, int k) {

    k = k % numsSize;
    if ( k == 0) return;

    int tmp = 0;
    for(int i = 0; i < numsSize/2; i++)
    {
        tmp = nums[numsSize - i - 1];
        nums[numsSize - i -1] = nums[i];
        nums[i] = tmp;
    }
    
    for ( int i = 0; i < k/2; i++)
    {
        tmp = nums[k - 1 - i];
        nums[k - i - 1] = nums[i];
        nums[i] = tmp;
    }
    for ( int i = k; i < (numsSize + k)/2; i++)
    {
        tmp = nums[numsSize - i - 1 + k];
        nums[numsSize - i + k -1] = nums[i];
        nums[i] = tmp;

    }
}