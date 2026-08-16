/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {

  int intarr[1001] = {0};
  int maxSize = nums1Size < nums2Size ? nums1Size : nums2Size;

  int *returnarr = malloc(sizeof *returnarr * maxSize);


  for (int i = 0; i < nums1Size; i++)
  {
    intarr[nums1[i]]++;
  }

  int count = 0;
  for (int i = 0; i < nums2Size; i++)
  {
    if (intarr[nums2[i]] > 0)
    {
      intarr[nums2[i]]--;
      returnarr[count++] = nums2[i];
    }
  }

  *returnSize = count;

  return returnarr;
}