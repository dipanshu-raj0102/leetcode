#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int *x = *(int **)a;
    int *y = *(int **)b;
    return x[0] - y[0];
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int maxBuilding(int n, int** restrictions, int restrictionsSize, int* restrictionsColSize)
{
    int m = restrictionsSize;


    int **arr = malloc((m + 2) * sizeof(int *));

    for (int i = 0; i < m + 2; i++)
        arr[i] = malloc(2 * sizeof(int));


    arr[0][0] = 1;
    arr[0][1] = 0;

    for (int i = 0; i < m; i++)
    {
        arr[i + 1][0] = restrictions[i][0];
        arr[i + 1][1] = restrictions[i][1];
    }

    arr[m + 1][0] = n;
    arr[m + 1][1] = n - 1;

    m += 2;

 
    qsort(arr, m, sizeof(int *), cmp);

 
    for (int i = 1; i < m; i++)
    {
        int dist = arr[i][0] - arr[i - 1][0];
        arr[i][1] = min(arr[i][1], arr[i - 1][1] + dist);
    }


    for (int i = m - 2; i >= 0; i--)
    {
        int dist = arr[i + 1][0] - arr[i][0];
        arr[i][1] = min(arr[i][1], arr[i + 1][1] + dist);
    }

    int ans = 0;

    for (int i = 1; i < m; i++)
    {
        int x1 = arr[i - 1][0];
        int h1 = arr[i - 1][1];

        int x2 = arr[i][0];
        int h2 = arr[i][1];

        int dist = x2 - x1;

        int peak = (h1 + h2 + dist) / 2;

        ans = max(ans, peak);
    }

    for (int i = 0; i < m; i++)
        free(arr[i]);
    free(arr);

    return ans;
}