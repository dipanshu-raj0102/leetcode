int thirdMax(int* nums, int numsSize) {

 long max = LONG_MIN;
 long second = LONG_MIN;
 long third = LONG_MIN - 10;

 while(numsSize--)
 {
    if (nums[numsSize] > max)
    {
        third = second;
        second = max;
        max = nums[numsSize];
    }
    else if (nums[numsSize] > second && nums[numsSize] != max)
    {
        third = second;
        second = nums[numsSize];
    }
    else if (nums[numsSize] > third && nums[numsSize] != second && nums[numsSize] != max)
    {
        third = nums[numsSize];
    }
 }
 if (third == LONG_MIN)
 {
    return max;
 }
 return third; 
}