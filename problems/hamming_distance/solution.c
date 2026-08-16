int hammingDistance(int x, int y) {
    
  int hamm_digit = x ^ y;

  int count = 0;

  while ( hamm_digit)
  {
    hamm_digit = hamm_digit & (hamm_digit - 1);
    count++;
  }
  return count;
}