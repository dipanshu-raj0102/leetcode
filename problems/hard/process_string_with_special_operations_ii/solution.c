#include <stdio.h>
#include <string.h>

char processStr(const char* s, long long k) {
    int n = strlen(s);
    long long m = 0;
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '*') {
            if (m > 0) m--;
        } else if (c == '#') {
            m <<= 1; 
        } else if (c != '%') {
            m++; 
        }

    }
    

    if (k < 0 || k >= m) {
        return '.';
    }
    

    for (int i = n - 1; i >= 0; i--) {
        char c = s[i];
        
        if (c == '*') {

            m++; 
        } 
        else if (c == '#') {
            m /= 2;

            if (k >= m) {
                k -= m;
            }
        } 
        else if (c == '%') {

            k = m - 1 - k;
        } 
        else {

            m--;

            if (k == m) {
                return c;
            }
        }
    }
    
    return '.';
}
