/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct Node
{
    int num;
    int ind;
    struct Node *next;
}Node;

typedef struct Table
{
    int size;
    Node **buckets;
}Table;

Table *ht_create(int size)
{
    if (size < 1) size = 1;
    Table *hashTable = malloc(sizeof(*hashTable));
    if (!hashTable) return NULL;
    hashTable -> size = size;
    hashTable -> buckets = calloc(size, sizeof(Node *));
    if (!hashTable -> buckets)
    {
        free(hashTable);
        return NULL;
    }
    return hashTable;
}
int get_index(Table *ht, int key)
{
    return ((key % ht -> size) + ht -> size) % ht -> size;
}
void ht_insert(Table *ht, int val, int idx) {
    int index = get_index(ht, val);
    Node *n = malloc(sizeof(Node));
    n->num = val;
    n->ind = idx;
    n->next = ht->buckets[index];
    ht->buckets[index] = n;       
}

int ht_search(Table *ht, int key)
{
    if (!ht) return -1;
    int index = get_index(ht, key);
    Node *tmp = ht -> buckets[index];
    while(tmp)
    {
        if (tmp -> num == key)
        {
            return tmp -> ind;
        }
        tmp = tmp -> next;
    }
    return -1;
}

void free_ht(Table *ht)
{
  if(!ht) return;
  Node *tmp = NULL;
  Node *to_dlt = NULL;
  for (int i = 0; i < ht -> size; i++)
  {
    tmp = ht -> buckets[i];
    while(tmp != NULL)
    {
      to_dlt = tmp;
      tmp = tmp -> next;
      free(to_dlt);
    }
  }
  free(ht -> buckets);
  free(ht);
  return;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int next_prime(int n) {
    if (n <= 2) return 2;
    int p = (n % 2 == 0) ? n + 1 : n;
    while (!is_prime(p)) {
        p += 2;
    }
    return p;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) 
{
    int optimalSize = next_prime(numsSize);
    Table *hashtable = ht_create(optimalSize);
    int *sol = malloc(sizeof(int) * 2);
    *returnSize = 2;
    for (int i = 0; i < numsSize; i++)
    {
        int key = target - *(nums + i);
        int ind = ht_search(hashtable, key);
        if (ind != (-1))
        {
            *(sol + 0) = ind;
            *(sol + 1) = i;
            free_ht(hashtable);
            return sol;
        }

        ht_insert(hashtable, *(nums + i), i);
    }
    free_ht(hashtable);
    *returnSize = 0;
    return NULL;
}