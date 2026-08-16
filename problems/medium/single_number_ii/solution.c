int singleNumber(int* nums, int numsSize) {
    int number = 0;

    for (int i = 0; i < 32; i++) {
        int count = 0;

        for (int j = 0; j < numsSize; j++) {
            if (nums[j] & (1U << i))
                count++;
        }

        if (count % 3)
            number |= (1U << i);
    }

    return number;
}