 typedef struct dict {
    char c;
    char *s;
} dict;

bool compstr(char *s1, char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return false;
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

void freeTable(dict *table[])
{
    for (int i = 0; i < 26; i++) {
        if (table[i]) {
            free(table[i]->s);
            free(table[i]);
        }
    }
}

bool wordPattern(char *pattern, char *s)
{
    dict *table[26] = {0};

    int i = 0;
    int j = 0;

    while (pattern[i] != '\0') {

        if (s[j] == '\0') {
            freeTable(table);
            return false;
        }

        int start = j;
        int len = 0;

        while (s[j] != ' ' && s[j] != '\0') {
            len++;
            j++;
        }

        char *word = malloc(len + 1);

        for (int k = 0; k < len; k++)
            word[k] = s[start + k];

        word[len] = '\0';

        int index = pattern[i] - 'a';

        if (table[index] == NULL) {

            /* Check reverse mapping */
            for (int t = 0; t < 26; t++) {
                if (table[t] && compstr(table[t]->s, word)) {
                    free(word);
                    freeTable(table);
                    return false;
                }
            }

            dict *node = malloc(sizeof(dict));
            node->c = pattern[i];
            node->s = word;
            table[index] = node;

        } else {

            if (!compstr(table[index]->s, word)) {
                free(word);
                freeTable(table);
                return false;
            }

            free(word);
        }

        if (s[j] == ' ')
            j++;

        i++;
    }

    /* Extra words remaining */
    if (s[j] != '\0') {
        freeTable(table);
        return false;
    }

    freeTable(table);
    return true;
}