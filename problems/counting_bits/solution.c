/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* countBits(int n, int* returnSize) {
    
  *returnSize = n + 1;
  int *count = malloc(sizeof *count * *returnSize);

  count[0] = 0;
  for ( int i = 1; i <= n; i++)
  {
    count[i] = count[i >> 1] + (i & 1);
  }
  return count;
}