/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *reverse(struct ListNode *head)
{
  if (!head) return NULL;

  struct ListNode *tmp = head;
  struct ListNode *prev = NULL;
  struct ListNode *next = NULL;
  
  while (tmp )
  {
    next = tmp -> next;
    tmp -> next = prev;
    prev = tmp;
    tmp = next;
  }
  
  return prev;
}

struct ListNode *middle(struct ListNode *head)
{
  if (!head) return NULL;

  struct ListNode *slow = head;
  struct ListNode *fast = head;

  while(fast && fast -> next)
  {
    slow = slow -> next;
    fast = fast -> next -> next;
  }
  return slow;
}
int pairSum(struct ListNode* head) {
    
  struct ListNode * mid = reverse(middle(head));

  int ans = 0;

  while ( mid)
  {
    if ((head ->val + mid ->val) > ans)
    {
      ans = head -> val + mid -> val;
    }
    head = head -> next;
    mid = mid -> next;
  }
  return ans;
}