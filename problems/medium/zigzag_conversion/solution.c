
char* convert(char* s, int numRows) {
    int len = strlen(s);

    if (numRows == 1 || len <= numRows) {
        char *ans = malloc(len + 1);
        strcpy(ans, s);
        return ans;
    }

    char **rows = malloc(numRows * sizeof(char*));

    for (int i = 0; i < numRows; i++) {
        rows[i] = malloc(len + 1);
        rows[i][0] = '\0';
    }

    int row = 0;
    bool down = true;

    for (int i = 0; i < len; i++) {
        int pos = strlen(rows[row]);
        rows[row][pos] = s[i];
        rows[row][pos + 1] = '\0';

        if (row == 0) {
            down = true;
        } else if (row == numRows - 1) {
            down = false;
        }

        row += down ? 1 : -1;
    }

    char *result = malloc(len + 1);
    int k = 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; rows[i][j] != '\0'; j++) {
            result[k++] = rows[i][j];
        }
        free(rows[i]);
    }

    result[k] = '\0';
    free(rows);

    return result;
}