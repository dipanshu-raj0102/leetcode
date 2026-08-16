int strStr(char * haystack, char * needle) {
    
    if (needle[0] == '\0') return 0;

    int i = 0; 
    int j = 0; 

   
    while (haystack[i] != '\0') {
        if (haystack[i] == needle[j]) {
      
            i++;
            j++;
            
            
            if (needle[j] == '\0') {
                return i - j;
            }
        } else {
          
            i = i - j + 1;
            
            j = 0;
        }
    }

    return -1;
}
