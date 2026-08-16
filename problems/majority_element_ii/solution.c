/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize) {

    int candidate1 = 0;
    int candidate2 = 0;

    int count1 = 0;
    int count2 = 0;


    for ( int i = 0; i < numsSize; i++)
    {
        if (nums[i] == candidate1)
        {
            count1++;
        }
        else if (nums[i] == candidate2)
        {
            count2++;
        }
        else if (count1 == 0)
        {
            candidate1 = nums[i];
            count1 = 1;
        }
        else if(count2 == 0)
        {
            candidate2 = nums[i];
            count2 = 1;
        }
        else
        {
            count1--;
            count2--;
        }
    }
    count1 = count2 = 0;

    int lim = numsSize / 3;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] == candidate1)
        {
            count1++;
        }
        else if (nums[i] == candidate2)
        {
            count2++;
        }
    }

    if(count1 > lim && count2 > lim)
    {
        *returnSize = 2;

        int *element = malloc(sizeof *element * (*returnSize));
        element[0] = candidate1;
        element[1] = candidate2;
        return element;
    }
    else if ( count1 > lim)
    {
        *returnSize = 1;
        
        int *element = malloc(sizeof *element * (*returnSize));
        element[0] = candidate1;
        return element;
    }
    else if (count2 > lim)
    {
        *returnSize = 1;

        int *element = malloc(sizeof *element * (*returnSize));
        element[0] = candidate2;
        return element;
    }
    
    *returnSize = 0;
    return NULL;
}