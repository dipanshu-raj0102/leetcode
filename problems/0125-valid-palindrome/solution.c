bool isAlphaNumeric(char s)
{
    if ((s >= 48 && s <= 57) || (s >= 65 && s <= 90) || (s >= 97 && s <= 122)) return true;
    return false;
}

bool isCap(char s)
{
    if ((s >= 65 && s <= 90)) return true;
    return false;
}

char toSmall(char s)
{
    s = s + 32;
    return s;
}


bool isPalindrome(char* s) {
    if (s[0] == '\0') return true;

    int i = 0;

    while (s[i] != '\0')
    {
        i++;
    }

    i--;

    int j = 0;

    while ( j <= i)
    {
        if (isAlphaNumeric(s[j]) && isAlphaNumeric(s[i]))
        {
            if (isCap(s[j]))
            {
                s[j] = toSmall(s[j]);
            }
            if (isCap(s[i]))
            {
                s[i] = toSmall(s[i]);
            }
            if (s[i] != s[j]) 
            {
                return false;
            }
            j++;
            i--;
        }
        else if(!isAlphaNumeric(s[i]) && !isAlphaNumeric(s[j]))
        {
            j++;
            i--;
        }
        else if (!isAlphaNumeric(s[i]))
        {
            i--;
        }
        else if (!isAlphaNumeric(s[j]))
        {
            j++;
        }

    }
    return true;
}