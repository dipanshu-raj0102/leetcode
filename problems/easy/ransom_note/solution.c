bool canConstruct(char* ransomNote, char* magazine) {
  int Count[26] = {0};

  int i = 0;
  while(ransomNote[i] != '\0')
  {
    Count[ransomNote[i] - 'a']--;
    i++;
  }
  i = 0;
  while(magazine[i] != '\0')
  {
    Count[magazine[i] - 'a']++;
    i++;
  }

  i = 0;
  while(i < 26)
  {
    if (Count[i] < 0) return false;
    i++;
  }
  return true;
}