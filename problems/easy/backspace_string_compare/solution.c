bool backspaceCompare(char* s, char* t) {

    char backs[strlen(s) + 1];
    char backt[strlen(t) + 1];

    int i = 0;
    int j = 0;

    while (s[i] != '\0')
    {
        if (s[i] == '#')
        {
            if (j > 0)
                j--;
        }
        else
        {
            backs[j++] = s[i];
        }
        i++;
    }
    backs[j] = '\0';

    i = 0;
    j = 0;

    while (t[i] != '\0')
    {
        if (t[i] == '#')
        {
            if (j > 0)
                j--;
        }
        else
        {
            backt[j++] = t[i];
        }
        i++;
    }
    backt[j] = '\0';

    return strcmp(backs, backt) == 0;
}