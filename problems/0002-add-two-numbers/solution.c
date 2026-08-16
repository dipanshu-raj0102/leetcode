/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode *tail = &dummy;
    int carry = 0;
    
    while(l1 || l2 || carry)
    {
        if(l1)
        {
            carry += l1 -> val;
            l1 = l1 -> next;
        }
        if (l2)
        {
            carry += l2 -> val;
            l2 = l2 -> next;
        }
        tail -> next = malloc(sizeof(struct ListNode));
        tail = tail -> next;
        tail -> next = NULL;

        tail -> val = carry % 10;
        carry /= 10;
    }
    
    return dummy.next;
}