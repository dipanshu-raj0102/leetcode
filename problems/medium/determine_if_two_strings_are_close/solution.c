
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

bool closeStrings(char* word1, char* word2) {

  int len1 = strlen(word1);
  int len2 = strlen(word2);

  if (len1 != len2) return false;

  int arr1[26] = {0};
  int arr2[26] = {0};

  for ( int i = 0; i < len1; i++)
  {
    arr1[word1[i] - 'a']++;
    arr2[word2[i] - 'a']++;
  }

  for (int i = 0; i < 26; i++)
  {
    if ((arr1[i] != 0 && arr2[i] == 0) || (arr1[i] == 0 && arr2[i] != 0)) return false;
  }

  selectionSort(arr1, 26);
  selectionSort(arr2, 26);

  for (int i = 0; i < 26; i++)
  {
    if (arr1[i] != arr2[i])
        return false;
  }

return true;

}