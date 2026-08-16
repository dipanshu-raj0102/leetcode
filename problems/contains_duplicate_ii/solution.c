
typedef struct node{
  int n;
  int index;
  struct node *next;
}node;

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {

  node **hashtable = calloc(numsSize, sizeof(**hashtable));

  for (int i = 0; i < numsSize; i++)
  {
    int index = nums[i] % numsSize;
    if (index < 0) index += numsSize;

    if (hashtable[index] == NULL)
    {
      node *n = malloc(sizeof *n);
      n -> n = nums[i];
      n -> index = i;
      n -> next = NULL;
      hashtable[index] = n;
    }
    else {
      node *tmp = hashtable[index];
      bool found = false;
      while(tmp)
      {
        if (tmp -> n == nums[i])
        {
          found = true;
          if ((abs(tmp -> index - i)) <= k)
          {
            return true;
          }
          else {
            tmp -> index = i;
            break;
          }
        }
        tmp = tmp -> next;
      }
      if (!found)
      {
        tmp = hashtable[index];
        node *n = malloc(sizeof *n);
        n -> n = nums[i];
        n -> index = i;
        n -> next = tmp;
        hashtable[index] = n;
      }
    }
  }

  return false;
    
}