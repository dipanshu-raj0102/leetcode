
int maxNumberOfBalloons(char* text) {
  
  int count[26] = {0};

  int i = 0;
  while(text[i] != '\0')
  {
    char c = text[i];
    if ( c == 'b' || c == 'a' || c == 'l' || c == 'o' || c == 'n')
    {
      count[c - 'a']++;
    }
    i++;
  }

  int min = INT_MAX;

  for (int i = 0; i < 26; i++)
  {
    if (i == ('b' - 'a') || i == ('a' - 'a') || i == ('l' - 'a') || i == ('o' - 'a') || i == ('n' - 'a'))
    {
      if (i == ('l' - 'a') || i == ('o' - 'a'))
      {
        count[i] = count[i] / 2;
      }
      if (min > count[i]) min = count[i];
    }
  }
  return min;

}