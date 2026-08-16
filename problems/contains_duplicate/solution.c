typedef struct Node{
    int key;
    struct Node *next;
}Node;

typedef struct Table{
    int size;
    Node **table;
}Table;

Table *createhash(int size)
{
    Table *hashtable = malloc(sizeof *hashtable);
    hashtable-> size = size;
    hashtable-> table = calloc(size, sizeof(Node *));
    
    return hashtable;
}

bool containsDuplicate(int* nums, int numsSize) {
    
    Table* myhash = createhash(numsSize);
    
    for(int i = 0; i < numsSize; i++)
    {
        int index = nums[i] % numsSize;
        if (index < 0) index = -index;
        Node *tmp = myhash->table[index];
        if (tmp == NULL)
        {
            Node *n = malloc(sizeof *n);
            n -> key = nums[i];
            n -> next = NULL;
            myhash->table[index] = n;
        }
        else{
            Node *last = NULL;
            while(tmp)
            {
                if (tmp -> key == nums[i]) return true;
                last = tmp;
                tmp = tmp -> next;
            }
            
            Node *n =malloc(sizeof *n);
            n -> key = nums[i];
            n -> next = NULL;
            last -> next = n;
        }
    }
    return false;
    
}