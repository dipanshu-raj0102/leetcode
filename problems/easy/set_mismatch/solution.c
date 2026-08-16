/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    *returnSize = 2;
    int *ans = malloc(2 * sizeof(int));

    int duplicate = -1;
    int missing = -1;

    for (int i = 0; i < numsSize; i++) {
        int idx = abs(nums[i]) - 1;

        if (nums[idx] < 0) {
            duplicate = abs(nums[i]);
        } else {
            nums[idx] = -nums[idx];
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            missing = i + 1;
            break;
        }
    }

    ans[0] = duplicate;
    ans[1] = missing;

    return ans;
}
