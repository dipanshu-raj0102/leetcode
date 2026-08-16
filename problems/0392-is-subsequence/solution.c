bool isSubsequence(char* s, char* t) {
    if (s[0] == '\0') return true;
   int i = 0;
   int j = 0;

   while(t[i] != '\0' && s[j] != '\0')
   {
    if (s[j] == t[i])
    {
        j++;
        if (s[j] == '\0') return true;
    }
    i++;
   } 
   return false;
}