
typedef struct Node{
  int key;
  int value;
  struct Node * next;
}Node;

typedef struct {
  int size_t;
  Node **table;
} MyHashMap;


MyHashMap* myHashMapCreate() {
  MyHashMap *obj = malloc(sizeof *obj);
  if (!obj) return NULL;

  obj -> size_t = 10001;
  obj -> table = calloc(obj -> size_t, sizeof(Node *));
  if (!obj -> table) 
  {
    free(obj);
    return NULL;
  }
  return obj;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
  int index = key % obj -> size_t;
  if (obj -> table[index] == NULL)
  {
    Node *n = malloc(sizeof *n);
    if (!n) return;
    n -> key = key;
    n -> value = value;
    n -> next = NULL;
    obj -> table[index] = n;
  }
  else {
    Node *tmp = obj -> table[index];
    while(tmp)
    {
      if(tmp -> key == key)
      {
        tmp -> value = value;
        return;
      }
      tmp = tmp -> next;
    }

    Node *n = malloc(sizeof *n);
    if (!n) return;
    n -> key = key;
    n -> value = value;
    tmp = obj -> table[index];
    n -> next = tmp;

    obj -> table[index] = n;
  }
}

int myHashMapGet(MyHashMap* obj, int key) {
  int index = key % obj -> size_t;
  Node *tmp = obj -> table[index];
  if(!tmp)
  {
    return -1;
  }
  else {
    while(tmp)
    {
      if (tmp -> key == key) return tmp -> value;
      tmp = tmp -> next;
    }
  }
  return -1;
}

void myHashMapRemove(MyHashMap* obj, int key) {
  int index = key % obj -> size_t;

  Node *tmp = obj -> table[index];

  if (!tmp)
  {
    return;
  }
  else {
    if (tmp -> key == key)
    {
      obj -> table[index] = tmp -> next;
      free(tmp);
    }
    else{
      Node *prev = tmp;
      while(tmp)
      {
        if (tmp -> key == key)
        {
          prev -> next = tmp -> next;
          free(tmp);
          return;
        }
        prev = tmp;
        tmp = tmp -> next;
      }
    }
  }
  return;
}

void myHashMapFree(MyHashMap* obj) {
  for (int i = 0; i < obj -> size_t; i++)
  {
    Node *tmp = obj -> table[i];
    if (!tmp)
    {
      continue;
    }
    else{
      Node *next = NULL;
      while(tmp)
      {
        next = tmp -> next;
        free(tmp);
        tmp = next;
      }
    }
  }
  free(obj);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/