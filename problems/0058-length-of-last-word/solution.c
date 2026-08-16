int lengthOfLastWord(char* s) {
   int i = 0;

   while(s[i] != '\0')
   {
    i++;
   }

   i--;
   int count = 0;
   while(i >= 0 && s[i] == ' ')
   {
    i--;
   }
   while(i >= 0 && s[i] != ' ')
   {
    i--;
    count++;
   }
   return count;
}