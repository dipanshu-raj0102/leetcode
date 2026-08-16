
char* substr(char *str1, char *str2)
{
  if(str2[0] == '\0') return str1;

  for (int i = 0; str1[i] != '\0'; i++)
  {
    int j = 0;

    while (str2[j] != '\0' && str1[i + j] == str2[j])
    {
      j++;
    }

    if (str2[j] == '\0') return &str1[i];

  }
  return NULL;
}

bool rotateString(char* s, char* goal) {
  int len_s = 0;
  int len_goal = 0;

  while (s[len_s] != '\0') len_s++;
  while (goal[len_goal] != '\0') len_goal++;

  if (len_goal != len_s) return false;
  
  char *sconcat = (char *)malloc(2 * len_s + 1);

  int i = 0;
  int j = 0;

  while (j < (len_s * 2))
  {
    sconcat[j++] = s[i];
    i = (i + 1) % len_s;
  }
  
  sconcat[j] = '\0';
  
  bool is_rotation = (substr(sconcat, goal) != NULL);

  free(sconcat);

  return is_rotation;
}