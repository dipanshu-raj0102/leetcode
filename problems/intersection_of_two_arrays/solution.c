/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {

  char intarr[1001] = {0};

  for (int i = 0; i < nums1Size; i++)
  {
    if(!intarr[nums1[i]]) intarr[nums1[i]] |= 1;
  }

  int count = 0;
  for (int i = 0; i < nums2Size; i++)
  {
    if (!(intarr[nums2[i]] & 2))
    {
      intarr[nums2[i]] |= 2;
      if ((intarr[nums2[i]] & 1) && (intarr[nums2[i]] & 2)) count++;
    }
  }

  *returnSize = count;

  int *returnarr = malloc(sizeof *returnarr * count);

  int j = 0;
  for (int i = 0; i < 1001; i++)
  {
    if ((intarr[i] & 1) && (intarr[i] & 2)) returnarr[j++] = i;
  }

  return returnarr;
}