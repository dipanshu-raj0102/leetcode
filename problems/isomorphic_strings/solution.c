bool isIsomorphic(char* s, char* t) {
  char mapArr[256] = {0};

  int i = 0;
  while (s[i] != '\0')
  {
    int index = (unsigned char)s[i] % 256;
    if (mapArr[index] != 0)
    {
      if (mapArr[index] != t[i]) return false;
    }
    else{
      mapArr[index] = t[i];
    }
    i++;
  }
  
  int count[256] = {0};

  for (i = 0; i < 256; i++)
  {
    count[mapArr[i]]++;
  }

  for (i = 1; i < 256; i++)
  {
    if (count[i] > 1) return false;
  }
  return true;
}