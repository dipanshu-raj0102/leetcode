int longestPalindrome(char* s) {
  if (s[0] == '\0') return 0;

  short int freq[52] = {0};

  short int i = 0;

  while(s[i] != '\0')
  {
    if (s[i] >= 65 && s[i] <= 90)
    {
      freq[s[i] - 'A']++;
    }
    else {
      freq[s[i] - 'a' + 26]++;
    }
    i++;
  }

  bool hasodd = false;
  short int length = 0;

  for ( int i = 0; i < 52; i++)
  {
    if (freq[i] % 2 == 0)
    {
      length = length + freq[i];
    }
    else{
      length = length + freq[i] - 1;
      hasodd = true;
    }
  }

  if (hasodd) length++;
  return length;
}