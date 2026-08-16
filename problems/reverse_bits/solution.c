int reverseBits(int n) {
  
  uint32_t ans = 0;
  for (int i = 0; i < 32; i++)
  {
    uint32_t x = n & 1;
    n = n >> 1;
    
    ans = ans << 1;
    ans = ans | x;
  }
  return ans;
}