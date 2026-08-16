

char * mergeAlternately(char * word1, char * word2){

  int len1 = strlen(word1);
  int len2 = strlen(word2);

  int i = 0;
  int j = 0;
  int k = 0;

  char *retstring = malloc(sizeof(char) * (len1 + len2 + 1));


  while (word1[i] != '\0' && word2[j] != '\0')
  {
    retstring[2 * i] = word1[i];
    i++;
    k++;
    retstring[2 * j + 1] = word2[j];
    j++;
    k++;
  }

  if (i < len1)
  {
    while(word1[i] != '\0')
    {
      retstring[k] = word1[i++];
      k++;
    }
  }

  if (j < len2)
  {
    while(word2[j] != '\0')
    {
      retstring[k] = word2[j++];
      k++;
    }
  }
  retstring[k] = '\0';

  return retstring;

}