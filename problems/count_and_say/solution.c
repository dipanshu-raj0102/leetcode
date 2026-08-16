char* countAndSay(int n) {
   
  char *ans = malloc(sizeof *ans * 2);
  ans[0] = '1';
  ans[1] = '\0';

  if ( n == 1) return ans;

  int length = 1;


  for(int i = 2; i <= n; i++)
  {
    char *tmp = malloc(sizeof(*tmp) * (2 * length + 1));
    int t = 0;
    int count = 0;
    int tmpl = 0;
    char s = ans[0];

    while(ans[t] != '\0')
    {
      if (ans[t] == s)
      {
        count++;
      }
      else{
        tmp[tmpl++] = count + '0';
        tmp[tmpl++] = s;
        s = ans[t];
        count = 1;
      }
      t++;
    }
    tmp[tmpl++] = count + '0';
    tmp[tmpl++] = s;
    tmp[tmpl] = '\0';
    free(ans);
    ans = tmp;
    length = tmpl;
  }
  return ans;



}