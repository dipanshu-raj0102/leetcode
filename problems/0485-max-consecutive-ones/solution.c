int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int currmax = 0;
    int globalmax = 0;
    while(numsSize--)
    {
        if ( nums[numsSize] == 1)
        {
            currmax = currmax + 1;
        
            if (globalmax < currmax)
            {
                globalmax = currmax;
            }   
        }

        else
        {
            currmax = 0;
        }
    } 
    return globalmax;
}