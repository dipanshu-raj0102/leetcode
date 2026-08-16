bool isAnagram(char* s, char* t) {
  int len_s = 0;
  int len_t = 0;

  while(s[len_s] != '\0') len_s++;
  while(t[len_t] != '\0') len_t++;

  if (len_s != len_t) return false;
  int freq[26] = {0};

  for (int i = 0; i < len_s; i++)
  {
    freq[s[i] - 'a']++;
  }
  for (int i = 0; i < len_s; i++)
  {
    if (freq[t[i] - 'a'] == 0)
    {
      return false;
    }
    else
    {
      freq[t[i] - 'a']--;
    }
    
  }

  return true;
}