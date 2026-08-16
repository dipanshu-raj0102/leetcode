bool isAdjacentDiffAtMostTwo(char* s) {

    if ( s == NULL || *s == '\0') return true;

    char *tmp = s;
    while (*(tmp + 1) != '\0')
    {
        if ((*tmp - *(tmp + 1)) > 2 || (*tmp - *(tmp + 1)) < -2)
        {
            return false;
        }
        tmp++;
    }
    
    return true;
}